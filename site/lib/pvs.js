// Font Lock rules adapted from SRI-CSL/PVS emacs/pvs-mode.el (BSD-3-Clause).
// See pvs-LICENSE.txt and the attribution in ../README.md.
const keywords = `
  and andthen array as assuming assumption auto_rewrite auto_rewrite+ auto_rewrite-
  axiom begin but by cases challenge claim closure codatatype coinductive cond
  conjecture containing conversion conversion+ conversion- corollary datatype
  else elsif end endassuming endcases endcond endif endtable exists exporting
  fact false forall formula from function has_type if iff implies importing in
  inductive judgement lambda law lemma let library macro measure nonempty_type
  not o obligation of or orelse postulate proposition recursive sublemma
  subtypes subtype_of table then theorem theory true type type+ var when where
  with xor
`.trim().split(/\s+/);

const operators = [
  "#", "##", "$", "$$", "&", "&&", "*", "**", "+", "++", "-", "/", "//", "/=",
  "/\\", "::", ":=", "<", "<-", "<<", "<<=", "<=", "<=>", "<>", "<|", "=",
  "==", "==>", "=>", ">", ">=", ">>", ">>=", "@", "@@", "[]", "\\/", "^", "^^",
  "|-", "|->", "|=", "|>", "~",
];

function alternatives(tokens) {
  return [...tokens].sort((a, b) => b.length - a.length)
    .map((token) => token.replace(/[.*+?^$(){}|[\]\\]/g, "\\$&")).join("|");
}

const identifier = "[\\p{L}\\p{N}\\p{M}_?]";
const rules = {
  comment: "%[^\\r\\n\\f]*",
  string: '"(?:\\\\[\\s\\S]|[^"\\\\])*(?:"|$)',
  keyword: "(?<!" + identifier + ")(?:" + alternatives(keywords) + ")(?!" + identifier + ")",
  record: alternatives(["(#", "#)", "[#", "#]"]),
  // Reserve the function arrow for the type face.
  operator: "(?:-(?!>)|" + alternatives(operators.filter((token) => token !== "-")) + ")",
  table: alternatives(["[|", "|]", "|[", "]|", "||"]),
  paren: alternatives(["(:", ":)", "(|", "|)", "[:", ":]", "(", ")"]),
  set: alternatives(["{", "}", "|"]),
  type: alternatives(["[", "]", "->"]),
};
const tokens = new RegExp(Object.entries(rules).map(([kind, rule]) => "(?<" + kind + ">" + rule + ")").join("|"), "giu");

export function pvsSections(source) {
  const prose = new Map();
  for (const match of source.matchAll(tokens)) {
    const comment = match.groups.comment;
    if (!comment || !/^%\|(?:[ \t]|$)/.test(comment)) continue;
    const lineStart = source.lastIndexOf("\n", match.index - 1) + 1;
    if (!/^[ \t]*$/.test(source.slice(lineStart, match.index))) continue;
    if (source[match.index + comment.length] === "\f") continue;
    prose.set(lineStart, comment.replace(/^%\| ?/, ""));
  }

  const sections = [];
  const lines = source.match(/[^\n]*\n|[^\n]+$/g) ?? [];
  let offset = 0;
  for (const [index, line] of lines.entries()) {
    const documentation = prose.get(offset);
    const kind = documentation === undefined ? "code" : "prose";
    const text = documentation === undefined ? line : documentation + (line.endsWith("\n") ? "\n" : "");
    if (sections.at(-1)?.kind !== kind) {
      sections.push({ kind, start: index + 1, end: index + 1, lines: [] });
    }
    const section = sections.at(-1);
    section.lines.push(text);
    section.end = index + 1;
    offset += line.length;
  }
  return sections.map(({ lines, ...section }) => ({ ...section, text: lines.join("") }));
}

export function escapeHtml(text) {
  return String(text).replaceAll("&", "&amp;").replaceAll("<", "&lt;").replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;").replaceAll("'", "&#39;");
}

function highlightLines(source) {
  const lines = [""];
  function append(text, kind) {
    const parts = text.split("\n");
    for (const [index, part] of parts.entries()) {
      if (index > 0) lines.push("");
      if (!part) continue;
      const escaped = escapeHtml(part);
      lines[lines.length - 1] += kind ? '<span class="pvs-' + kind + '">' + escaped + "</span>" : escaped;
    }
  }

  let offset = 0;
  for (const match of source.matchAll(tokens)) {
    append(source.slice(offset, match.index));
    const kind = Object.keys(match.groups).find((name) => match.groups[name] !== undefined);
    append(match[0], kind);
    offset = match.index + match[0].length;
  }
  append(source.slice(offset));
  if (source.endsWith("\n")) lines.pop();
  return lines;
}

export function highlightPvs(source, { label = "PVS code", start = 1, end, numbered = false, firstLine = 1 } = {}) {
  const lines = highlightLines(source);
  const last = end ?? lines.length;
  if (!Number.isInteger(start) || !Number.isInteger(last) || start < 1 || last < start || last > lines.length) {
    throw new Error("Invalid line range " + start + "–" + last + " for " + label + ".");
  }

  const selected = lines.slice(start - 1, last).map((line, index) => {
    if (!numbered) return line;
    const number = firstLine + start + index - 1;
    return '<span class="code-line" id="L' + number + '"><span class="line-number" aria-hidden="true" data-line="' +
      number + '"></span>' + line + "</span>";
  }).join("\n");
  const newline = last < lines.length || source.endsWith("\n") ? "\n" : "";
  return '<pre tabindex="0" aria-label="' + escapeHtml(label) + '"><code class="language-pvs">' +
    selected + newline + "</code></pre>";
}
