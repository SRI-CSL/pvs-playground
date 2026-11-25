import { readFileSync } from "node:fs";
import { dirname, resolve } from "node:path";
import { pathToFileURL } from "node:url";
import { checkResults } from "../src/assets/runner-results.js";
import { runNist } from "../src/assets/nist-runner.js";
import { createHash } from "node:crypto";
import { checkDriver, setDriverInput } from "../src/assets/driver-runner.js";

const manifestPath = resolve(process.argv[2]);
const manifest = JSON.parse(readFileSync(manifestPath, "utf8"));
async function createModule(options, suite = {}) {
  const { default: factory } = await import(pathToFileURL(resolve(dirname(manifestPath), suite.module ?? manifest.module)));
  return factory(options);
}
function bytes(file, folder = "") {
  const data = readFileSync(resolve(dirname(manifestPath), folder, file.path));
  if (createHash("sha256").update(data).digest("hex") !== file.sha256) throw new Error("Runner data checksum differs");
  return data;
}
for (const suite of manifest.suites) {
  const lines = [];
  const module = await createModule({ print: (line) => lines.push(line), printErr: (line) => lines.push(line) }, suite);
  if (suite.driver) setDriverInput(module, suite.fixture ? bytes(suite.fixture) : undefined);
  const result = module._run_example(suite.index);
  if (!(suite.driver ? checkDriver : checkResults)(lines, suite.expected, result)) {
    throw new Error(`${suite.theory} failed (${result}):\n${lines.join("\n")}`);
  }
  console.log(`${suite.theory}: ${suite.driver ? "checks passed" : `${suite.expected.length} passed`}`);
}
if (Object.keys(manifest.nist ?? {}).length) await runNist({ sets: Object.values(manifest.nist), createModule,
  loadFile: (file) => {
    return JSON.parse(bytes(file, "nist"));
  },
  report: (event) => {
    if (event.type === "output") console.log(event.line);
    if (event.type === "progress" && event.failed) throw new Error(`NIST mismatch in ${event.file}`);
    if (event.type === "progress" && event.file.endsWith(".json")) console.log(`NIST progress: ${event.passed} / ${event.total} (${event.file})`);
  },
}).then(({ passed, failed, total }) => {
  if (failed || passed !== total) throw new Error("Incomplete NIST results");
  console.log(`NIST: ${passed} of ${total} passed`);
});
