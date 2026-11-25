export function checkResults(lines, expected, code) {
  const actual = new Set(lines);
  return code === 0 && lines.length === expected.length && actual.size === expected.length &&
    expected.length > 0 && expected.every((line) => actual.has(line));
}
