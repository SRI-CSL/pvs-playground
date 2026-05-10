.PHONY: run-aes run-hmac run-sha256 run-utf8_decoder run-crypto ci-pvs2c-tests ci clean-aes clean-hmac clean-sha256 clean-utf8_decoder clean

run-aes:
	$(MAKE) -C aes run

run-hmac:
	$(MAKE) -C hmac run

run-sha256:
	$(MAKE) -C sha256 run

run-utf8_decoder:
	$(MAKE) -C utf8_decoder run

run-crypto: run-aes run-hmac run-sha256

ci-pvs2c-tests:
	python3 ../scripts/ci/run_pvs2c_tests.py --repo-root .. --demo-root pvs2c-demos

ci:
	python3 ../scripts/ci/run_pvs2c_tests.py --repo-root .. --demo-root pvs2c-demos
	$(MAKE) run-crypto
	$(MAKE) run-utf8_decoder

clean-aes:
	$(MAKE) -C aes clean

clean-hmac:
	$(MAKE) -C hmac clean

clean-sha256:
	$(MAKE) -C sha256 clean

clean-utf8_decoder:
	$(MAKE) -C utf8_decoder clean

clean: clean-aes clean-hmac clean-sha256 clean-utf8_decoder
