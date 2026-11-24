import { HtmlBasePlugin, IdAttributePlugin } from "@11ty/eleventy";
import MarkdownIt from "markdown-it";
import { execFileSync } from "node:child_process";
import { copyFileSync, mkdirSync, readFileSync, rmSync } from "node:fs";
import { dirname, join, relative } from "node:path";
import { discoverRepository, encodePath, repositoryLink, resolveSource } from "./lib/catalog.js";
import { highlightPvs } from "./lib/pvs.js";
import { renderLiteratePvs } from "./lib/literate.js";

const repositoryRoot = execFileSync("git", ["rev-parse", "--show-toplevel"], {
  cwd: import.meta.dirname,
  encoding: "utf8",
}).trim();
const watchRoot = relative(import.meta.dirname, repositoryRoot).split("\\").join("/");
const dataFile = new URL("src/_data/site.json", import.meta.url);
const defaults = JSON.parse(readFileSync(dataFile, "utf8"));
const repository = process.env.GITHUB_REPOSITORY || defaults.repository;
const pathPrefix = process.env.PAGES_BASE_PATH ?? "/" + repository.split("/").at(-1) + "/";
const ref = process.env.GITHUB_SHA || execFileSync("git", ["rev-parse", "HEAD"], {
  cwd: repositoryRoot,
  encoding: "utf8",
}).trim();
const github = {
  blob: "https://github.com/" + repository + "/blob/" + encodePath(ref) + "/",
  raw: "https://raw.githubusercontent.com/" + repository + "/" + encodePath(ref) + "/",
  tree: "https://github.com/" + repository + "/tree/" + encodePath(ref) + "/",
};

export default function (config) {
  const loadCatalog = () => discoverRepository(repositoryRoot, import.meta.dirname, github);
  let catalog = loadCatalog();
  const markdown = createMarkdown(true);
  const commentMarkdown = createMarkdown(false);

  config.setInputDirectory("src");
  config.setOutputDirectory("dist");
  config.addPlugin(HtmlBasePlugin);
  config.addPlugin(IdAttributePlugin);
  config.addPassthroughCopy("src/assets");
  config.addPassthroughCopy({ "lib/pvs-LICENSE.txt": "assets/pvs-LICENSE.txt" });
  config.setChokidarConfig({ usePolling: true, interval: 350 });
  config.addWatchTarget(watchRoot + "/");
  config.watchIgnores.add(watchRoot + "/.git/**");
  const ignored = execFileSync("git", [
    "ls-files", "--others", "--ignored", "--exclude-standard", "--directory", "-z",
  ], { cwd: repositoryRoot, encoding: "utf8" }).split("\0").filter(Boolean);
  for (const path of ignored) config.watchIgnores.add(watchRoot + "/" + path + (path.endsWith("/") ? "**" : ""));

  config.on("eleventy.before", ({ directories, outputMode }) => {
    catalog = loadCatalog();
    if (outputMode !== "fs") return;
    for (const name of ["browse", "source", "files"]) {
      rmSync(join(directories.output, name), { recursive: true, force: true });
    }
    for (const file of catalog.files.values()) {
      const destination = join(directories.output, file.rawOutput);
      mkdirSync(dirname(destination), { recursive: true });
      copyFileSync(join(repositoryRoot, file.path), destination);
    }
  });
  config.addGlobalData("catalog", () => catalog);
  config.addGlobalData("cryptoFolder", () => catalog.root.folders.find((folder) => folder.name.toLowerCase() === "crypto"));
  config.setNunjucksEnvironmentOptions({ autoescape: true });
  function createMarkdown(html) {
    const renderer = new MarkdownIt({
      html,
      highlight: (source, language) => language.toLowerCase() === "pvs" ? highlightPvs(source) : "",
    });
    for (const [rule, attribute] of [["link_open", "href"], ["image", "src"]]) {
      const original = renderer.renderer.rules[rule];
      renderer.renderer.rules[rule] = (tokens, index, options, env, output) => {
        const token = tokens[index];
        if (env.repositoryPath) {
          token.attrSet(attribute, repositoryLink(catalog, env.repositoryPath, token.attrGet(attribute), github, rule === "image"));
        }
        return original ? original(tokens, index, options, env, output) : output.renderToken(tokens, index, options);
      };
    }
    return renderer;
  }
  config.setLibrary("md", markdown);

  function readSource(file) {
    return readFileSync(join(repositoryRoot, file.path), "utf8").replace(/\r\n?/g, "\n");
  }

  config.addShortcode("repositoryProse", (file) => markdown.render(readSource(file), { repositoryPath: file.path }));
  config.addShortcode("pvs", (reference, start, end) => {
    const file = resolveSource(catalog.sources, reference);
    return highlightPvs(readSource(file), { label: file.path, start, end });
  });
  config.addShortcode("pvsSource", (file) => renderLiteratePvs(readSource(file), {
    label: file.path,
    renderMarkdown: (text) => commentMarkdown.render(text, { repositoryPath: file.path }),
  }));

  return { pathPrefix: pathPrefix || "/", markdownTemplateEngine: "njk" };
}
