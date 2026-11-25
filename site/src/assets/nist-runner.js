export function evaluateVector(module, vector) {
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
      const module = await createModule();
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
