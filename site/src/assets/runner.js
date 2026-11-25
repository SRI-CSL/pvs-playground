for (const panel of document.querySelectorAll(".crypto-runner")) {
  const select = panel.querySelector(".runner-suite");
  const run = panel.querySelector(".runner-run");
  const nist = panel.querySelector(".runner-nist");
  const stop = panel.querySelector(".runner-stop");
  const status = panel.querySelector(".runner-status");
  const output = panel.querySelector(".runner-output");
  const source = panel.querySelector(".runner-source");
  const generated = panel.querySelector(".runner-c");
  let worker;
  let timer;
  let characters = 0;
  const finish = (message) => {
    worker?.terminate();
    worker = undefined;
    clearTimeout(timer);
    run.disabled = false;
    nist.disabled = false;
    select.disabled = false;
    stop.hidden = true;
    panel.removeAttribute("aria-busy");
    status.textContent = message;
  };
  select.addEventListener("change", () => {
    const option = select.selectedOptions[0];
    if (source) source.href = option.dataset.source;
    if (generated) generated.href = option.dataset.c;
    nist.hidden = JSON.parse(option.dataset.nist || "[]").length === 0;
    for (const details of panel.querySelectorAll(".runner-nist-details")) details.hidden = details.dataset.suite !== option.value;
    status.textContent = "";
    output.hidden = true;
  });
  stop.addEventListener("click", () => finish("Stopped"));
  function start(mode) {
    output.textContent = "";
    output.hidden = false;
    characters = 0;
    run.disabled = true;
    nist.disabled = true;
    select.disabled = true;
    stop.hidden = false;
    panel.setAttribute("aria-busy", "true");
    status.textContent = "Loading…";
    try {
      worker = new Worker(new URL("./runner-worker.js", import.meta.url), { type: "module" });
      worker.onmessage = ({ data }) => {
        if (data.type === "running") status.textContent = "Running…";
        if (data.type === "progress") status.textContent = `${data.passed + data.failed} / ${data.total} checked${data.failed ? ` · ${data.failed} failed` : ""}`;
        if (data.type === "output") {
          characters += data.line.length;
          if (characters > 100000) return finish("Output limit exceeded");
          output.textContent += data.line + "\n";
        }
        if (data.type === "done") finish(data.passed ? `${data.count} passed` : data.mode === "nist" ? `${data.failed} failed / ${data.count} checked` : `Failed (exit ${data.code})`);
        if (data.type === "error") {
          output.textContent += data.message + "\n";
          finish("Could not run. Try again.");
        }
      };
      worker.onerror = (event) => {
        output.textContent += (event.message || "Could not load the runner.") + "\n";
        finish("Could not run. Try again.");
      };
      const option = select.selectedOptions[0];
      worker.postMessage({ module: new URL(panel.dataset.module, location.href).href,
        index: Number(option.value), expected: JSON.parse(option.dataset.expected),
        mode, nist: JSON.parse(option.dataset.nist || "[]") });
      if (mode !== "nist") timer = setTimeout(() => finish("Timed out after 120 seconds"), 120000);
    } catch (error) {
      output.textContent = error.message;
      finish("Could not run. Try again.");
    }
  }
  run.addEventListener("click", () => start("examples"));
  nist.addEventListener("click", () => start("nist"));
  window.addEventListener("pagehide", () => { worker?.terminate(); clearTimeout(timer); });
}
