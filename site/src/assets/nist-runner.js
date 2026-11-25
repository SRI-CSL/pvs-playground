import { decodeVector, setDriverInput } from "./driver-runner.js";

export function evaluateVector(module, vector) {
  if (vector.data !== undefined) {
    try {
      if (module.runnerOutput) module.runnerOutput.length = 0;
      const bytes = decodeVector(vector.data);
      if (!bytes.length) throw new Error("Empty NIST vector");
      setDriverInput(module, bytes);
      const code = module._run_example(0);
      return { id: vector.id, actual: `exit ${code}` + (code && module.runnerOutput?.length ? "\n" + module.runnerOutput.join("\n") : ""), expected: "exit 0", passed: code === 0 };
    } catch (error) {
      return { id: vector.id, actual: error.message, expected: "exit 0", passed: false };
    }
  }
  const actual = module.ccall("nist_eval", "string", ["string"], [vector.input]);
  return { id: vector.id, actual, expected: vector.expected, passed: actual === vector.expected };
}

export async function runNist({ sets, createModule, loadFile, report = () => {} }) {
  let passed = 0;
  let failed = 0;
  const total = sets.reduce((sum, set) => sum + set.count, 0);
  if (!total) throw new Error("No NIST vectors are configured for this example.");
  for (const set of sets) {
    report({ type: "output", line: `${set.label}: ${set.count} cases` });
    for (const file of set.files) {
      const vectors = await loadFile(file);
      if (vectors.length !== file.count || !file.count) throw new Error(`NIST case count differs: ${file.name}`);
      // A new instance per response file releases memory and isolates file state.
      const lines = [];
      const module = await createModule({ print: (line) => lines.push(line), printErr: (line) => lines.push(line) }, set);
      module.runnerOutput = lines;
      let lastReport = 0;
      for (let index = 0; index < vectors.length; index++) {
        const result = evaluateVector(module, vectors[index]);
        if (result.passed) passed++;
        else {
          failed++;
          if (failed <= 20) report({ type: "output", line: `${file.name} / ${result.id}\nExpected: ${result.expected}\nActual:   ${result.actual}` });
        }
        const now = Date.now();
        if (!result.passed || now - lastReport >= 100 || index === vectors.length - 1) {
          report({ type: "progress", passed, failed, total, file: file.name });
          lastReport = now;
        }
      }
      report({ type: "output", line: `${file.name}: ${file.count} cases checked` });
    }
  }
  return { passed, failed, total };
}
