# PVS Playground website

## Local preview

With Git and Node.js 22 or newer, run from the repository root:

~~~sh
npm --prefix site ci
npm --prefix site run dev
~~~

Open the URL printed by Eleventy. The landing page lists the repository's top-level folders. Each folder opens its immediate subfolders and files.

## Edit content in the repository

Write folder prose in its existing `README.md` or `README`. It appears below the folder's file list. For prose above a PVS spec, place a Markdown file with the same stem beside it, such as `NQueens/nqueens.md` beside `NQueens/nqueens.pvs`.

The site reads these files directly. Moving a folder together with its contents moves its pages and prose. Relative Markdown links and images resolve from the Markdown file's directory. Use a fenced `pvs` block to highlight PVS in prose.

## Render prose from PVS comments

Prefix a whole comment line with `%|` followed by a space to write Markdown directly in a PVS file:

~~~pvs
%| ## Counter
%|
%| The state is a **natural number**.
counter: TYPE = nat

%| Each step increments the counter.
step(n: counter): counter = n + 1
~~~

PVS treats these lines as ordinary comments. The website interleaves their rendered Markdown with syntax-highlighted code. Use a bare `%|` for a blank Markdown line. Headings, emphasis, lists, tables, images, links, and fenced code blocks are supported. Indentation after the first space is preserved.

Relative links and images resolve from the PVS file's directory. Line numbers and `#L42` links refer to the original file, including comment lines. The **Raw source** link opens the complete original file. Ordinary comments and ProofLite commands keep their code display.

Discovery uses Git's tracked files and nonignored local files. The preview reloads after edits and additions. Each build discovers the current structure and removes old generated pages. Commit new files to include them in the GitHub Pages build. Hidden paths, editor backups, and the site's own implementation directory are excluded. Git submodules link to their GitHub entries.

PVS specs and Markdown have generated pages. Other files are served directly. Generated output is in `site/dist/`.

[site.css](src/assets/site.css) controls the layout and colors. The [highlighter](lib/pvs.js) adapts the [PVS Emacs Font Lock rules](https://github.com/SRI-CSL/PVS/blob/c777cf3ee02677aa552f33e2bd1cb5bd0d2f19e9/emacs/pvs-mode.el) under the [upstream BSD license](lib/pvs-LICENSE.txt).

## GitHub Pages

`npm --prefix site run build` writes the static site to `site/dist/`. To publish, push to the default branch, then run the [GitHub Pages workflow](../.github/workflows/pages.yml) manually. The URL is [sri-csl.github.io/pvs-playground](https://sri-csl.github.io/pvs-playground/). [GitHub Pages documentation](https://docs.github.com/en/pages/getting-started-with-github-pages/using-custom-workflows-with-github-pages)

## Future PVS2C browser demos

Compile the generated C, runtime dependencies, and a wrapper with Emscripten. Put the [modularized JS and its .wasm file](https://emscripten.org/docs/compiling/Modularized-Output.html) beside the demo's source files. The build serves those files from the repository, and a script in the demo's Markdown can load the module using that generated file URL.
