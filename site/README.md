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

## Crypto pages

The `crypto/` subtree uses a dark monospace theme and a terminal-style navigation header. Its folder pages show their immediate subfolders and files above the README. Write the crypto landing page in [crypto/README.md](../crypto/README.md), and use ordinary relative Markdown links to choose which topics and specs appear there.

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

`npm --prefix site run build` writes the static site to `site/dist/`. Push to `main` to deploy automatically. The [GitHub Pages workflow](../.github/workflows/pages.yml) can also be run manually. The URL is [sri-csl.github.io/pvs-playground](https://sri-csl.github.io/pvs-playground/). [GitHub Pages documentation](https://docs.github.com/en/pages/getting-started-with-github-pages/using-custom-workflows-with-github-pages)

## Run crypto examples

The runner executes the existing PVS `_TEST_` declarations as PVS2C-generated C compiled to WebAssembly. It appears on the crypto landing page, the relevant folders, and the example specifications. Each Run starts a fresh worker; Stop terminates it. A run passes only when every expected test prints `true`, with no missing, duplicate, or extra results.

Install Python 3.12+, PVS with its generated PVS2C Prelude, and [Emscripten 4.0.23](https://emscripten.org/docs/getting_started/downloads.html). Activate the SDK, then run:

~~~sh
PVS_BIN="$HOME/git/PVS/pvs" npm --prefix site run build:crypto
npm --prefix site run dev -- --port=8765
~~~

The first build downloads checksum-verified GMP 6.3.0 and compiles it for WebAssembly. Subsequent builds reuse that library. The application is typechecked and regenerated in a disposable context; source and proof files stay untouched. The build runs every compiled suite under Node before writing its manifest. This checks executable examples; it does not replay proofs.

Add a theory and label to [crypto-runners.json](crypto-runners.json) to expose another example suite. The build finds theories by filename and derives their page links from their repository location. No content copy is maintained. Use `--crypto-root` if discovery is ambiguous, or `--suite THEORY` for a smaller local build. `PVS_BIN`, `PVS2C_RUNTIME`, `--cache`, and `--output` override tool and build locations. `CRYPTO_WASM_DIR` tells Eleventy where to read a custom output directory.

[build_crypto.py](scripts/build_crypto.py) owns generation and compilation; [runner.js](src/assets/runner.js) owns the controls; [runner-worker.js](src/assets/runner-worker.js) loads the [modularized Emscripten module](https://emscripten.org/docs/compiling/Modularized-Output.html). Generated assets and caches are ignored by Git. Run `build:crypto` again after changing crypto specifications, then restart the preview. Ordinary Markdown prose and style edits only need the site build.

**Generated C** opens a highlighted code view in the browser. The implementation, header, test driver and included headers link to one another; compiled PVS specifications also have a direct C link. **Rebuild sources** on the C view provides the full generated C and PVS, runtime sources, exact GMP source and licenses, and a rebuild script. [pvs2c-compat.lisp](scripts/pvs2c-compat.lisp) handles two generator issues: resolving named types for nested array lambdas, and retaining theory parameters in scalar array update definitions. It is loaded only in the isolated generation process.

The Pages workflow prepares pinned PVS and Emscripten toolchains, builds and checks the runner, then builds the site. A failed runner build prevents publication. That workflow must be pushed to take effect; a local build does not deploy.
