import { execFileSync } from "node:child_process";
import { lstatSync } from "node:fs";
import { join, posix } from "node:path";

const collator = new Intl.Collator("en", { numeric: true });

function encodePath(path) {
  return path.split("/").map(encodeURIComponent).join("/");
}

export function discoverSources(root, siteRoot) {
  const paths = execFileSync("git", ["ls-files", "--cached", "--deduplicate", "-z", "--", "*.pvs"], {
    cwd: root,
    encoding: "utf8",
  }).split("\0").filter((path) => path && isFile(join(root, path)));
  const nameCounts = new Map();
  for (const path of paths) {
    const name = posix.basename(path);
    nameCounts.set(name, (nameCounts.get(name) ?? 0) + 1);
  }

  const groups = new Map();
  const sources = [];
  for (const path of paths) {
    const directory = posix.dirname(path);
    const name = posix.basename(path);
    const source = {
      path,
      name,
      url: "/source/" + encodePath(path) + "/",
      output: "source/" + path + "/index.html",
      indexLink: "/#" + encodeURIComponent(directory),
      note: findNote(siteRoot, path, name, nameCounts.get(name) === 1),
    };
    if (!groups.has(directory)) groups.set(directory, { directory, files: [] });
    groups.get(directory).files.push(source);
    sources.push(source);
  }

  const ordered = [...groups.values()].sort((a, b) => collator.compare(a.directory, b.directory));
  for (const group of ordered) {
    group.files.sort((a, b) => collator.compare(a.name, b.name));
  }
  return { sources, groups: ordered };
}

function isFile(path) {
  return lstatSync(path, { throwIfNoEntry: false })?.isFile();
}

function findNote(siteRoot, path, name, unique) {
  const exact = "notes/" + path.replace(/\.pvs$/, ".md");
  if (isFile(join(siteRoot, exact))) return exact;
  if (unique && path !== name) {
    const short = "notes/" + name.replace(/\.pvs$/, ".md");
    if (isFile(join(siteRoot, short))) return short;
  }
}

export function resolveSource(sources, reference) {
  const exact = sources.find((source) => source.path === reference);
  if (exact) return exact;

  const matches = sources.filter((source) => source.name === reference);
  if (matches.length === 1) return matches[0];
  if (matches.length > 1) {
    throw new Error("Multiple PVS files are named " + reference + ". Use a repository-relative path.");
  }
  throw new Error("PVS source not found: " + reference + ". Check the name and add the file to Git.");
}
