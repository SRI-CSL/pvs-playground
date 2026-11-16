import { HtmlBasePlugin, RenderPlugin } from "@11ty/eleventy";
import { readFileSync } from "node:fs";
import { join } from "node:path";
import { discoverSources, resolveSource } from "./lib/catalog.js";
import { highlightPvs } from "./lib/pvs.js";

const repositoryRoot = import.meta.dirname + "/..";
const dataFile = new URL("src/_data/site.json", import.meta.url);
const defaults = JSON.parse(readFileSync(dataFile, "utf8"));
const repository = process.env.GITHUB_REPOSITORY || defaults.repository;
const pathPrefix = process.env.PAGES_BASE_PATH ?? "/" + repository.split("/").at(-1) + "/";

export default function (config) {
  const loadCatalog = () => discoverSources(repositoryRoot, import.meta.dirname);
  let catalog = loadCatalog();

  config.setInputDirectory("src");
  config.setOutputDirectory("dist");
  config.addPlugin(HtmlBasePlugin);
  config.addPlugin(RenderPlugin);
  config.addPassthroughCopy("src/assets");
  config.addPassthroughCopy({ "lib/pvs-LICENSE.txt": "assets/pvs-LICENSE.txt" });
  config.setChokidarConfig({ usePolling: true, interval: 350 });
  config.addWatchTarget("./notes/");
  for (const source of catalog.sources) config.addWatchTarget("../" + source.path);

  config.on("eleventy.beforeWatch", () => { catalog = loadCatalog(); });
  config.addGlobalData("catalog", () => catalog);
  config.setNunjucksEnvironmentOptions({ autoescape: true });
  config.amendLibrary("md", (markdown) => {
    markdown.set({
      highlight: (source, language) => language.toLowerCase() === "pvs" ? highlightPvs(source) : "",
    });
  });

  function readSource(file) {
    return readFileSync(join(repositoryRoot, file.path), "utf8").replace(/\r\n?/g, "\n");
  }

  config.addShortcode("pvs", (reference, start, end) => {
    const file = resolveSource(catalog.sources, reference);
    return highlightPvs(readSource(file), { label: file.path, start, end });
  });
  config.addShortcode("pvsSource", (file) => highlightPvs(readSource(file), {
    label: file.path,
    numbered: true,
  }));

  return { pathPrefix: pathPrefix || "/", markdownTemplateEngine: "njk" };
}
