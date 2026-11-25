// Each run has a fresh Wasm instance; terminating this worker also frees its memory.
import { checkResults } from "./runner-results.js";
import { runNist } from "./nist-runner.js";

self.onmessage = async ({ data }) => {
  try {
    const { default: createModule } = await import(data.module);
    if (data.mode === "nist") {
      const base = new URL("./nist/", data.module);
      const response = await fetch(new URL("manifest.json", base));
      if (!response.ok) throw new Error(`NIST manifest: HTTP ${response.status}`);
      const manifest = await response.json();
      const sets = data.nist.map((id) => {
        if (!manifest.sets[id]) throw new Error(`Unknown NIST set: ${id}`);
        return manifest.sets[id];
      });
      self.postMessage({ type: "running" });
      const result = await runNist({ sets, createModule,
        loadFile: async (file) => {
          const response = await fetch(new URL(file.path, base));
          if (!response.ok) throw new Error(`NIST vectors: HTTP ${response.status}`);
          const bytes = await response.arrayBuffer();
          const digest = [...new Uint8Array(await crypto.subtle.digest("SHA-256", bytes))].map((n) => n.toString(16).padStart(2, "0")).join("");
          if (digest !== file.sha256) throw new Error(`NIST data checksum differs: ${file.name}`);
          return JSON.parse(new TextDecoder().decode(bytes));
        },
        report: (event) => self.postMessage(event),
      });
      self.postMessage({ type: "done", passed: result.failed === 0 && result.passed === result.total,
        count: result.total, failed: result.failed, mode: "nist", code: result.failed ? 1 : 0 });
      return;
    }
    const lines = [];
    const print = (line) => {
      lines.push(line);
      self.postMessage({ type: "output", line });
    };
    const module = await createModule({ print, printErr: print });
    self.postMessage({ type: "running" });
    const code = module._run_example(data.index);
    const passed = checkResults(lines, data.expected, code);
    self.postMessage({ type: "done", passed, count: data.expected.length, code });
  } catch (error) {
    self.postMessage({ type: "error", message: error.message || String(error) });
  }
};
