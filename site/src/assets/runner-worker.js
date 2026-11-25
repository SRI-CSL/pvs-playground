// Each run has a fresh Wasm instance; terminating this worker also frees its memory.
import { checkResults } from "./runner-results.js";

self.onmessage = async ({ data }) => {
  try {
    const { default: createModule } = await import(data.module);
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
