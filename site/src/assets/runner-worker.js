// Each run has a fresh Wasm instance; terminating this worker also frees its memory.
import { checkResults } from "./runner-results.js";
import { runNist } from "./nist-runner.js";
import { checkDriver, setDriverInput, loadChecked } from "./driver-runner.js";

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
      const result = await runNist({ sets, createModule: async (options, set) => {
        const factory = set.module ? (await import(new URL(set.module, data.module))).default : createModule;
        return factory(options);
      },
        loadFile: async (file) => {
          const bytes = await loadChecked(file, base);
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
    if (data.driver) setDriverInput(module, data.fixture ? await loadChecked(data.fixture, data.module) : undefined);
    self.postMessage({ type: "running" });
    const code = module._run_example(data.index);
    const passed = (data.driver ? checkDriver : checkResults)(lines, data.expected, code);
    self.postMessage({ type: "done", passed, count: data.expected.length, code, driver: data.driver });
  } catch (error) {
    self.postMessage({ type: "error", message: error.message || String(error) });
  }
};
