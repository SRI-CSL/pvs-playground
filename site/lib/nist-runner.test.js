import assert from "node:assert/strict";
import test from "node:test";
import { evaluateVector, runNist } from "../src/assets/nist-runner.js";

test("NIST comparisons use independently supplied expected outputs", () => {
  const calls = [];
  const module = { ccall: (...args) => { calls.push(args); return "abcd"; } };
  const vector = { id: "COUNT 0", input: "aes 1 0011 2233", expected: "abcd" };
  assert.equal(evaluateVector(module, vector).passed, true);
  assert.equal(evaluateVector(module, { ...vector, expected: "abce" }).passed, false);
  assert.deepEqual(calls[0], ["nist_eval", "string", ["string"], [vector.input]]);
  assert.equal(calls[0].at(-1).includes(vector.expected), false);
});

test("NIST runs report failed case identities and reject missing cases", async () => {
  const events = [];
  const sets = [{ label: "NIST fixture", count: 2, files: [{ name: "test.rsp", count: 2 }] }];
  const options = { sets, createModule: () => ({ ccall: () => "aa" }),
    loadFile: () => [{ id: "COUNT 0", input: "first", expected: "aa" }, { id: "COUNT 1", input: "second", expected: "bb" }],
    report: (event) => events.push(event) };
  assert.deepEqual(await runNist(options), { passed: 1, failed: 1, total: 2 });
  assert.ok(events.some((event) => event.line?.includes("test.rsp / COUNT 1\nExpected: bb\nActual:   aa")));
  await assert.rejects(runNist({ ...options, loadFile: () => [] }), /case count differs/);
  await assert.rejects(runNist({ ...options, sets: [] }), /No NIST vectors/);
});
