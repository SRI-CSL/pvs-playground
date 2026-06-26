#!/usr/bin/env node

const fs = require("fs");
const { TextDecoder } = require("util");

function usage() {
  console.error("usage: node_utf8_bench.js cases.json replace iterations trials");
  process.exit(2);
}

if (process.argv.length !== 6) {
  usage();
}

const [, , casesPath, mode, iterationsText, trialsText] = process.argv;
if (mode !== "replace") {
  console.error("node benchmark currently supports replacement mode only");
  process.exit(2);
}

const iterations = Number(iterationsText);
const trials = Number(trialsText);
if (!Number.isInteger(iterations) || iterations <= 0 ||
    !Number.isInteger(trials) || trials <= 0) {
  usage();
}

const cases = JSON.parse(fs.readFileSync(casesPath, "utf8"));
const decoder = new TextDecoder("utf-8", { fatal: false });
let sink = 0;

function fromHex(hex) {
  return Buffer.from(hex, "hex");
}

function sanitize(input) {
  return Buffer.from(decoder.decode(input), "utf8");
}

function median(values) {
  values.sort((a, b) => a - b);
  return values[Math.floor(values.length / 2)];
}

function timeCase(input) {
  const warmups = Math.min(iterations, 64);
  for (let i = 0; i < warmups; i++) {
    sink += sanitize(input).length;
  }

  const samples = [];
  for (let trial = 0; trial < trials; trial++) {
    const start = process.hrtime.bigint();
    for (let i = 0; i < iterations; i++) {
      sink += sanitize(input).length;
    }
    const end = process.hrtime.bigint();
    samples.push(Number(end - start) / iterations);
  }
  return median(samples);
}

console.log("implementation,mode,case,valid,input_bytes,expected_bytes,ns_per_op,ok");
for (const tc of cases) {
  const input = fromHex(tc.input_hex);
  const expected = fromHex(tc.replace_hex);
  const actual = sanitize(input);
  const ok = actual.equals(expected);
  const nsPerOp = timeCase(input);
  console.log([
    `Node ${process.version} TextDecoder`,
    mode,
    tc.number,
    tc.valid ? "1" : "0",
    input.length,
    expected.length,
    nsPerOp.toFixed(2),
    ok ? "yes" : "no",
  ].join(","));
}

if (sink === Number.MAX_SAFE_INTEGER) {
  console.error(`unreachable sink value: ${sink}`);
}
