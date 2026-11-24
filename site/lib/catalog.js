import { execFileSync } from "node:child_process";
import { lstatSync } from "node:fs";
import { join, posix, relative } from "node:path";

const collator = new Intl.Collator("en", { numeric: true });

export function encodePath(path) {
  return path.split("/").map(encodeURIComponent).join("/");
}

export function discoverRepository(root, siteRoot, github) {
  const sitePath = relative(root, siteRoot).split("\\").join("/");
  const paths = execFileSync("git", [
    "ls-files", "--cached", "--others", "--exclude-standard", "--deduplicate", "-z",
  ], { cwd: root, encoding: "utf8" }).split("\0").filter((path) =>
    path && path !== sitePath && !path.startsWith(sitePath + "/") &&
    !path.split("/").some((part) => part.startsWith(".") || part.endsWith("~"))
  );

  const directories = new Map();
  const files = new Map();
  function directory(path) {
    if (!directories.has(path)) {
      const parent = path === "." ? undefined : directory(posix.dirname(path));
      const entry = {
        path,
        name: posix.basename(path),
        theme: path.split("/")[0].toLowerCase() === "crypto" ? "crypto" : "",
        url: path === "." ? "/" : "/browse/" + encodePath(path) + "/",
        output: "browse/" + path + "/index.html",
        folders: [],
        files: [],
        breadcrumbs: parent ? [...parent.breadcrumbs, { name: posix.basename(path), url: "/browse/" + encodePath(path) + "/" }] : [],
      };
      directories.set(path, entry);
      if (parent) parent.folders.push(entry);
    }
    return directories.get(path);
  }

  const rootDirectory = directory(".");
  for (const path of paths) {
    const info = lstatSync(join(root, path), { throwIfNoEntry: false });
    if (info?.isDirectory()) {
      directory(posix.dirname(path)).folders.push({
        name: posix.basename(path),
        url: github.tree + encodePath(path),
      });
    }
    if (!info?.isFile()) continue;

    const folder = directory(posix.dirname(path));
    const name = posix.basename(path);
    const isPvs = name.toLowerCase().endsWith(".pvs");
    const isMarkdown = name.toLowerCase().endsWith(".md") || /^readme$/i.test(name);
    const file = {
      path,
      name,
      isPvs,
      isMarkdown,
      theme: folder.theme,
      url: isPvs || isMarkdown ? "/source/" + encodePath(path) + "/" : "/files/" + encodePath(path),
      rawUrl: "/files/" + encodePath(path),
      rawOutput: "files/" + path,
      output: "source/" + path + "/index.html",
      breadcrumbs: folder.breadcrumbs,
    };
    files.set(path, file);
    folder.files.push(file);
  }

  for (const folder of directories.values()) {
    folder.folders.sort((a, b) => collator.compare(a.name, b.name));
    folder.files.sort((a, b) => collator.compare(a.name, b.name));
    folder.readme = folder.files.find((file) => /^readme\.md$/i.test(file.name)) ??
      folder.files.find((file) => /^readme$/i.test(file.name));
  }
  for (const file of files.values()) {
    if (file.isPvs) file.prose = files.get(file.path.slice(0, -4) + ".md");
  }

  return {
    root: rootDirectory,
    directories: [...directories.values()].filter((folder) => folder.path !== "."),
    pages: [...files.values()].filter((file) => file.isPvs || file.isMarkdown),
    sources: [...files.values()].filter((file) => file.isPvs),
    files,
    folders: directories,
  };
}

export function repositoryLink(catalog, from, href, github, image = false) {
  if (!href || /^[#?]/.test(href) || /^[a-z][a-z\d+.-]*:|^\/\//i.test(href)) return href;
  const match = /^([^?#]*)(.*)$/.exec(href);
  const path = posix.normalize(posix.join(href.startsWith("/") ? "." : posix.dirname(from), decodeURIComponent(match[1])));
  const suffix = match[2];
  const file = catalog.files.get(path);
  const folder = catalog.folders.get(path.replace(/\/$/, "") || ".");
  if (folder) return folder.url + suffix;
  if (file) return (image ? file.rawUrl : file.url) + suffix;
  return (image ? github.raw : github.blob) + encodePath(path) + suffix;
}

export function resolveSource(sources, reference) {
  const exact = sources.find((source) => source.path === reference);
  if (exact) return exact;

  const matches = sources.filter((source) => source.name === reference);
  if (matches.length === 1) return matches[0];
  if (matches.length > 1) {
    throw new Error("Multiple PVS files are named " + reference + ". Use a repository-relative path.");
  }
  throw new Error("PVS source not found: " + reference + ". Check the name.");
}
