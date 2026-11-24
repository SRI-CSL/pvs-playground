import { highlightPvs, pvsSections } from "./pvs.js";

function lineAnchors(section) {
  const anchors = [];
  for (let line = section.start; line <= section.end; line++) {
    anchors.push('<span class="source-anchor" id="L' + line + '" aria-hidden="true"></span>');
  }
  return anchors.join("");
}

export function renderLiteratePvs(source, { label, renderMarkdown }) {
  const sections = pvsSections(source);
  if (!sections.some((section) => section.kind === "prose")) {
    return highlightPvs(source, { label, numbered: true });
  }

  return '<div class="literate-pvs">' + sections.map((section) => {
    if (section.kind === "code") {
      if (!section.text.trim()) return '<div class="source-gap">' + lineAnchors(section) + "</div>";
      return highlightPvs(section.text, { label, numbered: true, firstLine: section.start });
    }

    return '<div class="prose pvs-prose">' + lineAnchors(section) + renderMarkdown(section.text) + "</div>";
  }).join("\n") + "</div>";
}
