import { readFileSync } from "node:fs";
import { dirname, resolve } from "node:path";
import { pathToFileURL } from "node:url";
import { checkResults } from "../src/assets/runner-results.js";

const manifestPath = resolve(process.argv[2]);
const manifest = JSON.parse(readFileSync(manifestPath, "utf8"));
const { default: createModule } = await import(pathToFileURL(resolve(dirname(manifestPath), manifest.module)));
for (const suite of manifest.suites) {
  const lines = [];
  const module = await createModule({ print: (line) => lines.push(line), printErr: (line) => lines.push(line) });
  const result = module._run_example(suite.index);
  if (!checkResults(lines, suite.expected, result)) {
    throw new Error(`${suite.theory} failed (${result}):\n${lines.join("\n")}`);
  }
  console.log(`${suite.theory}: ${lines.length} passed`);
}
