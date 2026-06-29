PVS2C_TEST_RUNNER := python3 ../scripts/ci/run_pvs2c_tests.py --repo-root ..
PVS2C_TEST_ARGS := $(if $(PVS_HOME),--pvs-location $(PVS_HOME))

.PHONY: \
	run-aes run-hmac run-sha256 run-utf8_decoder \
	run-bytecode-wasm run-bytecode-sqlite_vdbe run-bytecode \
	run-parsing-ltedpeg run-parsing-ltedfa run-parsing \
	run-ltedpeg run-ltedfa run-sqlite_vdbe run-crypto run-all run-examples \
	ci-pvs2c-tests ci \
	clean-aes clean-hmac clean-sha256 clean-utf8_decoder \
	clean-bytecode-wasm clean-bytecode-sqlite_vdbe clean-bytecode \
	clean-parsing-ltedpeg clean-parsing-ltedfa clean-parsing clean

run-aes:
	$(MAKE) -C aes run

run-hmac:
	$(MAKE) -C hmac run

run-sha256:
	$(MAKE) -C sha256 run

run-utf8_decoder:
	$(MAKE) -C utf8_decoder run

run-bytecode-wasm:
	$(MAKE) -C bytecode/wasm run

run-bytecode-sqlite_vdbe:
	$(MAKE) -C bytecode/sqlite_vdbe run

run-bytecode: run-bytecode-wasm run-bytecode-sqlite_vdbe

run-parsing-ltedpeg:
	$(PVS2C_TEST_RUNNER) --demo-root pvs2c-demos/parsing/ltedpeg $(PVS2C_TEST_ARGS)

run-parsing-ltedfa:
	$(PVS2C_TEST_RUNNER) --demo-root pvs2c-demos/parsing/ltedfa $(PVS2C_TEST_ARGS)

run-parsing: run-parsing-ltedpeg run-parsing-ltedfa

run-ltedpeg: run-parsing-ltedpeg

run-ltedfa: run-parsing-ltedfa

run-sqlite_vdbe: run-bytecode-sqlite_vdbe

run-crypto: run-aes run-hmac run-sha256

run-all: run-crypto run-utf8_decoder run-bytecode run-parsing

run-examples: run-all

ci-pvs2c-tests:
	$(PVS2C_TEST_RUNNER) --demo-root pvs2c-demos $(PVS2C_TEST_ARGS)

ci:
	$(MAKE) ci-pvs2c-tests
	$(MAKE) run-crypto
	$(MAKE) run-utf8_decoder
	$(MAKE) run-bytecode

clean-aes:
	$(MAKE) -C aes clean

clean-hmac:
	$(MAKE) -C hmac clean

clean-sha256:
	$(MAKE) -C sha256 clean

clean-utf8_decoder:
	$(MAKE) -C utf8_decoder clean

clean-bytecode-wasm:
	$(MAKE) -C bytecode/wasm clean

clean-bytecode-sqlite_vdbe:
	$(MAKE) -C bytecode/sqlite_vdbe clean

clean-bytecode: clean-bytecode-wasm clean-bytecode-sqlite_vdbe

clean-parsing-ltedpeg:
	rm -rf parsing/ltedpeg/build parsing/ltedpeg/pvs2c parsing/ltedpeg/pvsbin parsing/ltedpeg/.pvscontext parsing/ltedpeg/Makefile.bak

clean-parsing-ltedfa:
	rm -rf parsing/ltedfa/build parsing/ltedfa/pvs2c parsing/ltedfa/pvsbin parsing/ltedfa/.pvscontext parsing/ltedfa/Makefile.bak

clean-parsing: clean-parsing-ltedpeg clean-parsing-ltedfa

clean: clean-aes clean-hmac clean-sha256 clean-utf8_decoder clean-bytecode clean-parsing
