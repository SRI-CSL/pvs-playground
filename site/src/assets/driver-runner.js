export function setDriverInput(module, bytes = new Uint8Array()) {
  module.FS.writeFile("/runner-input", bytes);
}

export function checkDriver(lines, expected, code) {
  return code === 0 && expected.length > 0 && expected.every((marker) => lines.includes(marker));
}

export function decodeVector(data) {
  return Uint8Array.from(atob(data), (char) => char.charCodeAt(0));
}

export async function loadChecked(file, base) {
  const response = await fetch(new URL(file.path, base));
  if (!response.ok) throw new Error(`Runner data: HTTP ${response.status}`);
  const bytes = new Uint8Array(await response.arrayBuffer());
  const digest = [...new Uint8Array(await crypto.subtle.digest("SHA-256", bytes))].map((n) => n.toString(16).padStart(2, "0")).join("");
  if (digest !== file.sha256) throw new Error(`Runner data checksum differs: ${file.path}`);
  return bytes;
}
