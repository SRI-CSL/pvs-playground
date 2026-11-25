import { existsSync, readFileSync } from "node:fs";
import { join, posix } from "node:path";
import { createHash } from "node:crypto";
import hljs from "highlight.js/lib/core";
import c from "highlight.js/lib/languages/c";

hljs.registerLanguage("c", c);

export function highlightC(text) {
  return hljs.highlight(text, { language: "c" }).value;
}

export function loadCryptoRunners(directory, catalog, required = false, repositoryRoot) {
  const path = join(directory, "manifest.json");
  if (!existsSync(path)) {
    if (required) throw new Error("Build the crypto runner first: npm run build:crypto");
    return null;
  }
  const manifest = JSON.parse(readFileSync(path, "utf8"));
  if (repositoryRoot) {
    for (const [source, hash] of Object.entries(manifest.inputs ?? {})) {
      const path = join(repositoryRoot, source);
      if (!existsSync(path) || createHash("sha256").update(readFileSync(path)).digest("hex") !== hash) {
        throw new Error(`Crypto sources changed; run npm run build:crypto (${source})`);
      }
    }
  }
  for (const name of [manifest.module, manifest.module.replace(/\.mjs$/, ".wasm"), "sources.zip"]) {
    if (!existsSync(join(directory, name))) throw new Error(`Missing crypto runner asset: ${name}`);
  }
  for (const suite of manifest.suites) {
    const file = catalog.files.get(suite.source);
    if (!file?.isPvs) throw new Error(`Rebuild the crypto runner for ${suite.source}`);
    suite.sourceUrl = file.url;
    suite.folder = posix.dirname(file.path);
    suite.nistSets = (suite.nist ?? []).map((id) => {
      const set = manifest.nist?.[id];
      if (!set) throw new Error(`Missing NIST vector set: ${id}`);
      return { ...set, excludedCount: Object.values(set.excluded).reduce((sum, count) => sum + count, 0) };
    });
    suite.nistCount = suite.nistSets.reduce((sum, set) => sum + set.count, 0);
  }
  const codePaths = JSON.parse(readFileSync(join(directory, "code.json"), "utf8"));
  const cryptoRoot = catalog.root.folders.find((folder) => folder.theme === "crypto");
  manifest.code = codePaths.map((path) => {
    const name = posix.basename(path);
    const theory = name.replace(/(?:_c)?\.[ch]$/, "");
    const pvs = catalog.sources.find((source) => source.name === theory + ".pvs");
    return { path, name, url: "/c/" + path + "/", output: "c/" + path + "/index.html",
      pvs, breadcrumbs: pvs?.breadcrumbs ?? cryptoRoot?.breadcrumbs ?? [],
      isHeader: name.endsWith(".h") };
  });
  const byName = new Map(manifest.code.map((file) => [file.name, file]));
  const link = ({ name, url }) => ({ name, url });
  for (const file of manifest.code) {
    const text = readFileSync(join(directory, "code", file.path), "utf8");
    const includes = [...text.matchAll(/^#include\s+"([^"]+)"/gm)].map((match) => byName.get(match[1])).filter(Boolean);
    const stem = file.name.replace(/(?:_c)?\.[ch]$/, "");
    const related = [stem + ".c", stem + "_c.c", stem + "_c.h"].map((name) => byName.get(name)).filter((other) => other && other !== file);
    file.links = [...new Set([...related, ...includes])].map(link);
  }
  for (const suite of manifest.suites) {
    suite.codeUrl = byName.get(suite.theory + "_c.c")?.url;
    if (!suite.codeUrl) throw new Error(`Missing generated C for ${suite.theory}`);
  }
  return manifest;
}

export function runnersFor(manifest, path, source = false) {
  return manifest?.suites.filter((suite) => source ? suite.source === path :
    suite.folder === path || suite.folder.startsWith(path + "/")) ?? [];
}
