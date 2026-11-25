import assert from "node:assert/strict";
import test from "node:test";
import { checkDriver, setDriverInput } from "../src/assets/driver-runner.js";
import { evaluateVector, runNist } from "../src/assets/nist-runner.js";

test("native drivers require successful exit and their completion markers", () => {
  assert.equal(checkDriver(["done"], ["done"], 0), true);
  assert.equal(checkDriver(["done"], ["done"], 1), false);
  assert.equal(checkDriver([], ["done"], 0), false);
  assert.equal(checkDriver([], [], 0), false);
});

test("binary NIST frames reach stdin intact and failures are observed", () => {
  let input;
  const module = { FS: { writeFile(path, bytes) { assert.equal(path, "/runner-input"); input = bytes; } }, _run_example() { return input[0]; } };
  assert.equal(evaluateVector(module, { id: "1", data: "AAD/" }).passed, true);
  assert.deepEqual([...input], [0, 0, 255]);
  assert.equal(evaluateVector(module, { id: "2", data: "AQD/" }).passed, false);
  assert.equal(evaluateVector(module, { id: "empty", data: "" }).passed, false);
  setDriverInput(module);
  assert.equal(input.length, 0);
});

test("NIST datasets select their corresponding Wasm module", async () => {
  const selected = [];
  const sets = ["rsa", "mlkem"].map((id) => ({ id, module: id + ".mjs", count: 1, files: [{ name: id, count: 1 }] }));
  const result = await runNist({ sets, createModule: (options, set) => {
    selected.push(set.module); return { ccall: () => "true" };
  }, loadFile: () => [{ input: "verify", expected: "true" }] });
  assert.deepEqual(selected, ["rsa.mjs", "mlkem.mjs"]);
  assert.deepEqual(result, { passed: 2, failed: 0, total: 2 });
});
