# PVS Playground website

## Local preview

With Git and Node.js 22 or newer, run from the repository root:

~~~sh
npm --prefix site ci
npm --prefix site run dev
~~~

Open the URL printed by Eleventy. The list is generated from the repository's Git-indexed `.pvs` files. Restart the preview after adding or moving a PVS file.

## Add prose to an example

Create `site/notes/nqueens.md` to put Markdown above `nqueens.pvs`. Use the filename without `.pvs` when it is unique. For duplicate filenames, mirror the path from the repository root inside `site/notes/`. For example, `site/notes/pvs2c-demos/sha256/bytevectors.md` belongs to `pvs2c-demos/sha256/bytevectors.pvs`. A path-specific note takes precedence over a filename-only note.

Use a fenced `pvs` block for inline examples. Embed lines from a repository file with this shortcode:

~~~markdown
{% pvs "nqueens.pvs", 64, 73 %}
~~~

[site.css](src/assets/site.css) controls the layout and colors. The [highlighter](lib/pvs.js) adapts the [PVS Emacs Font Lock rules](https://github.com/SRI-CSL/PVS/blob/c777cf3ee02677aa552f33e2bd1cb5bd0d2f19e9/emacs/pvs-mode.el) under the [upstream BSD license](lib/pvs-LICENSE.txt).

## GitHub Pages

`npm --prefix site run build` writes the static site to `site/dist/`. To publish, push to the default branch, set **Settings → Pages → Source** to **GitHub Actions**, then run the [GitHub Pages workflow](../.github/workflows/pages.yml) manually. The expected URL is [sri-csl.github.io/pvs-playground](https://sri-csl.github.io/pvs-playground/). [GitHub Pages documentation](https://docs.github.com/en/pages/getting-started-with-github-pages/using-custom-workflows-with-github-pages)

## Future PVS2C browser demos

Compile the generated C, runtime dependencies, and a wrapper with Emscripten. Put the [modularized JS and its .wasm file](https://emscripten.org/docs/compiling/Modularized-Output.html) under `site/src/assets/demos/` and resolve the Wasm relative to the module so it works under the Pages subpath.
