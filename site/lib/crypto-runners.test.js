import assert from "node:assert/strict";
import test from "node:test";
import { checkResults } from "../src/assets/runner-results.js";
import { runnersFor } from "./crypto-runners.js";

test("generated test mains need every expected true result, even with exit zero", () => {
  const expected = ["suite.a ==> true", "suite.b ==> true"];
  assert.equal(checkResults([...expected].reverse(), expected, 0), true);
  for (const lines of [[], expected.slice(0, 1), [expected[0], expected[0]],
    [expected[0], "suite.b ==> false"], [...expected, "runtime error"]]) {
    assert.equal(checkResults(lines, expected, 0), false);
  }
  assert.equal(checkResults(expected, expected, 1), false);
  assert.equal(checkResults([], [], 0), false);
});

test("runners follow repository folders and source files without matching sibling prefixes", () => {
  const suite = { source: "crypto/a/spec.pvs", folder: "crypto/a" };
  const manifest = { suites: [suite] };
  assert.deepEqual(runnersFor(manifest, "crypto"), [suite]);
  assert.deepEqual(runnersFor(manifest, "crypto/a"), [suite]);
  assert.deepEqual(runnersFor(manifest, suite.source, true), [suite]);
  assert.deepEqual(runnersFor(manifest, "crypto/ab"), []);
  assert.deepEqual(runnersFor(manifest, "crypto/a/other.pvs", true), []);
  assert.deepEqual(runnersFor(null, "crypto"), []);
});
