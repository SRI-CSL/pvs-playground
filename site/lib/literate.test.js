import assert from "node:assert/strict";
import test from "node:test";
import MarkdownIt from "markdown-it";
import { renderLiteratePvs } from "./literate.js";
import { highlightPvs, pvsSections } from "./pvs.js";

const markdown = new MarkdownIt({
  highlight: (source, language) => language === "pvs" ? highlightPvs(source) : "",
});

function render(source) {
  return renderLiteratePvs(source, { label: "example.pvs", renderMarkdown: (text) => markdown.render(text) });
}

test("ordinary comments retain their original code rendering", () => {
  const source = "% A normal comment\nexample: THEORY\nBEGIN\nEND example\n";
  assert.equal(render(source), highlightPvs(source, { label: "example.pvs", numbered: true }));
});

test("Markdown is interleaved with code and every original line keeps its anchor", () => {
  const source = [
    "%| ## State",
    "%|",
    "%| The counter is **natural**.",
    "counter: TYPE = nat",
    "",
    "%| - Increment the counter.",
    "%| - Return its new value.",
    "step(n: counter): counter = n + 1",
  ].join("\n");
  const html = render(source);
  assert.match(html, /<h2>State<\/h2>/);
  assert.match(html, /<strong>natural<\/strong>/);
  assert.match(html, /<ul>/);
  assert.match(html, /class="pvs-keyword">TYPE/);
  assert.ok(html.indexOf("State</h2>") < html.indexOf('id="L4"'));
  assert.ok(html.indexOf('id="L4"') < html.indexOf("Increment the counter."));
  assert.deepEqual([...html.matchAll(/\bid="L(\d+)"/g)].map((match) => Number(match[1])), [1, 2, 3, 4, 5, 6, 7, 8]);
});

test("markers inside strings, inline comments, and ProofLite commands stay in code", () => {
  const source = [
    's: string = "first line',
    '%| This is inside a string.',
    'last line"',
    "n: nat = 1 %| An inline comment.",
    "%|- result: PROOF (grind) QED",
    "%|# An unmarked comment.",
  ].join("\n");
  assert.deepEqual(pvsSections(source), [{
    kind: "code",
    start: 1,
    end: 6,
    text: source,
  }]);
});

test("comment indentation supports lists, tables, and highlighted code fences", () => {
  const source = [
    "  %| - Outer",
    "  %|   - Inner",
    "  %|",
    "  %| | Name | Value |",
    "  %| | --- | --- |",
    "  %| | counter | 0 |",
    "  %|",
    "  %| ~~~pvs",
    "  %| answer: nat = 42",
    "  %| ~~~",
  ].join("\n") + "\n";
  const html = render(source);
  assert.match(html, /<li>Outer\n<ul>/);
  assert.match(html, /<table>/);
  assert.match(html, /<code class="language-pvs">answer/);
  assert.equal((html.match(/\bid="L\d+"/g) ?? []).length, 10);
});

test("blank separators create spacing and anchors without empty code panels", () => {
  const html = render("%| First paragraph.\n\n%| Second paragraph.");
  assert.doesNotMatch(html, /<pre/);
  assert.match(html, /class="source-gap"/);
  assert.equal((html.match(/\bid="L\d+"/g) ?? []).length, 3);
});

test("literal HTML in comments is rendered as text and formfeed cannot hide code", () => {
  assert.match(render("%| A <tag> in prose."), /A &lt;tag&gt; in prose/);
  const source = "%| Not a whole line.\fanswer: nat = 42";
  assert.equal(pvsSections(source)[0].kind, "code");
  assert.equal(render(""), highlightPvs("", { label: "example.pvs", numbered: true }));
});
