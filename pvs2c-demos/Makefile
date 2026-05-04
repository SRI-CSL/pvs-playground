.PHONY: run-aes run-hmac run-sha256 clean-aes clean-hmac clean-sha256 clean

run-aes:
	$(MAKE) -C aes run

run-hmac:
	$(MAKE) -C hmac run

run-sha256:
	$(MAKE) -C sha256 run

clean-aes:
	$(MAKE) -C aes clean

clean-hmac:
	$(MAKE) -C hmac clean

clean-sha256:
	$(MAKE) -C sha256 clean

clean: clean-aes clean-hmac clean-sha256
