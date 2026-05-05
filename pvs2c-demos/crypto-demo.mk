NO_PVS_GOALS := clean clean-% nist-vectors
NO_GENERATED_MK_GOALS := clean clean-% typecheck pvs2c nist-vectors

NEEDS_PVS := $(if $(MAKECMDGOALS),$(filter-out $(NO_PVS_GOALS),$(MAKECMDGOALS)),all)
INCLUDE_GENERATED_MK := $(if $(MAKECMDGOALS),$(filter-out $(NO_GENERATED_MK_GOALS),$(MAKECMDGOALS)),all)

ifneq ($(NEEDS_PVS),)
ifndef PVS_LOCATION
$(error PVS_LOCATION is not set. Export PVS_LOCATION=/path/to/PVS, where /path/to/PVS is your PVS home checkout)
endif
endif

PVS := $(PVS_LOCATION)/pvs

CC ?= cc
CURL ?= curl
UNZIP ?= unzip
CFLAGS ?= -O2 -w -foptimize-sibling-calls -fPIC
CPPFLAGS += -I$(PVS_LOCATION)/lib/pvs2c/include -Ipvs2c/include -include ../pvs2c_compat.h
LDFLAGS += -L$(PVS_LOCATION)/lib/pvs2c/lib
LDLIBS += $(PVS_LOCATION)/lib/pvs2c/lib/libpvs-prelude.a -lgmp -lm

BUILD_DIR := build
BINDIR := pvs2c/bin
SRCDIR := pvs2c/src
BIN := $(BUILD_DIR)/$(DEMO)-driver
TYPECHECK_LOG := $(BUILD_DIR)/typecheck.log
TYPECHECK_STATUS := $(BUILD_DIR)/typecheck.status
PVS2C_LOG := $(BUILD_DIR)/pvs2c.log
PVS2C_STAMP := $(BUILD_DIR)/pvs2c.stamp
GENERATED_HEADER := pvs2c/include/$(MAIN_THEORY)_c.h
GENERATED_MK := pvs2c/include/$(MAIN_THEORY).mk
GENERATED_TEST_BIN := $(BINDIR)/$(MAIN_THEORY)
NIST_VECTOR_DIR ?= test-vectors/nist
NIST_ZIP := $(BUILD_DIR)/nist-vectors.zip
PVS_SOURCES := $(wildcard *.pvs)
MAKE_DEPS := Makefile ../crypto-demo.mk
GENERATED_LIB_OBJS = $(filter-out $(SRCDIR)/$(MAIN_THEORY).o,$(OBJS_$(MAIN_THEORY)))

# Stream typecheck progress, but keep PVS2C quiet; both transcripts are logged.
PVS_TYPECHECK_EXPR := (progn (setq *suppress-output* nil) (tc "$(TC_THEORY)" t) (finish-output) (uiop:quit))
PVS2C_EXPR := (progn (setq *suppress-output* t) (pvs2c-theory "$(MAIN_THEORY)" t) (finish-output) (uiop:quit))

ifneq ($(INCLUDE_GENERATED_MK),)
-include $(GENERATED_MK)
endif

.PHONY: all run typecheck pvs2c nist-vectors clean

all: $(BIN)

run: nist-vectors $(GENERATED_TEST_BIN) $(BIN)
	@./$(GENERATED_TEST_BIN)
	@./$(BIN)

typecheck: $(TYPECHECK_LOG)

pvs2c: $(GENERATED_HEADER)

$(BUILD_DIR) $(BINDIR):
	@mkdir -p $@

nist-vectors: | $(BUILD_DIR)
	@if [ -n "$(NIST_ZIP_URL)" ]; then \
	  mkdir -p $(NIST_VECTOR_DIR); \
	  missing=0; \
	  for f in $(NIST_VECTOR_FILES); do \
	    if [ ! -f "$(NIST_VECTOR_DIR)/$$f" ]; then missing=1; fi; \
	  done; \
	  if [ $$missing -eq 1 ]; then \
	    echo "[$(DEMO)] Fetching NIST CAVP vectors: $(NIST_SUITE_NAME)"; \
	    $(CURL) -L -o $(NIST_ZIP) "$(NIST_ZIP_URL)"; \
	    $(UNZIP) -oq -j $(NIST_ZIP) $(NIST_ZIP_MEMBERS) -d $(NIST_VECTOR_DIR); \
	  fi; \
	fi

$(TYPECHECK_LOG): $(PVS_SOURCES) $(MAKE_DEPS) | $(BUILD_DIR)
	@echo "[$(DEMO)] Typechecking $(TC_THEORY)"
	@echo "[$(DEMO)]   PVS: $(PVS)"
	@echo "[$(DEMO)]   log: $@"
	@rm -f $(TYPECHECK_STATUS)
	@{ $(PVS) -raw -E '$(PVS_TYPECHECK_EXPR)' < /dev/null 2>&1; echo $$? > $(TYPECHECK_STATUS); } | tee $@
	@status=$$(cat $(TYPECHECK_STATUS)); \
	rm -f $(TYPECHECK_STATUS); \
	if [ "$$status" -ne 0 ]; then \
	  echo "[$(DEMO)] Typecheck command failed; see $@"; \
	  exit $$status; \
	fi
	@if grep -q "^In file " $@; then \
	  echo "[$(DEMO)] Typecheck reported errors; see $@"; \
	  exit 1; \
	fi
	@echo "[$(DEMO)] Typecheck complete"

$(PVS2C_STAMP): $(PVS_SOURCES) $(MAKE_DEPS) $(TYPECHECK_LOG) | $(BUILD_DIR)
	@echo "[$(DEMO)] Generating C for $(MAIN_THEORY)"
	@echo "[$(DEMO)]   PVS: $(PVS)"
	@echo "[$(DEMO)]   log: $(PVS2C_LOG)"
	@if ! $(PVS) -raw -E '$(PVS2C_EXPR)' < /dev/null > $(PVS2C_LOG) 2>&1; then \
	  echo "[$(DEMO)] PVS2C command failed; see $(PVS2C_LOG)"; \
	  cat $(PVS2C_LOG); \
	  exit 1; \
	fi
	@if grep -q "^In file " $(PVS2C_LOG); then \
	  echo "[$(DEMO)] PVS2C reported errors; see $(PVS2C_LOG)"; \
	  cat $(PVS2C_LOG); \
	  exit 1; \
	fi
	@test -f $(GENERATED_HEADER)
	@test -f $(GENERATED_MK)
	@touch $@
	@echo "[$(DEMO)] Generated $(GENERATED_HEADER)"

$(GENERATED_HEADER) $(GENERATED_MK): $(PVS2C_STAMP)
	@:

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(GENERATED_HEADER)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN): driver.c $(GENERATED_TEST_BIN) $(MAKE_DEPS) ../pvs2c_compat.h ../cavp_driver.h | $(BUILD_DIR)
	@echo "[$(DEMO)] Building driver"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(GENERATED_LIB_OBJS) driver.c -o $@ $(LDLIBS)

clean:
	@rm -rf $(BUILD_DIR) pvs2c Makefile.bak $(NIST_VECTOR_DIR)
