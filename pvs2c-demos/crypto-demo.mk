PVS_LOCATION ?= $(HOME)/git/PVS
PVS := $(PVS_LOCATION)/pvs

CC ?= cc
CFLAGS ?= -O2 -w -foptimize-sibling-calls -fPIC
CPPFLAGS += -I$(PVS_LOCATION)/lib/pvs2c/include -Ipvs2c/include -include ../pvs2c_compat.h
LDFLAGS += -L$(PVS_LOCATION)/lib/pvs2c/lib
LDLIBS += $(PVS_LOCATION)/lib/pvs2c/lib/libpvs-prelude.a -lgmp -lm

BUILD_DIR := build
BINDIR := pvs2c/bin
SRCDIR := pvs2c/src
BIN := $(BUILD_DIR)/$(DEMO)-driver
TYPECHECK_LOG := $(BUILD_DIR)/typecheck.log
PVS2C_LOG := $(BUILD_DIR)/pvs2c.log
PVS2C_STAMP := $(BUILD_DIR)/pvs2c.stamp
GENERATED_HEADER := pvs2c/include/$(MAIN_THEORY)_c.h
GENERATED_MK := pvs2c/include/$(MAIN_THEORY).mk
GENERATED_TEST_BIN := $(BINDIR)/$(MAIN_THEORY)
PVS_SOURCES := $(wildcard *.pvs)
MAKE_DEPS := Makefile ../crypto-demo.mk
GENERATED_LIB_OBJS = $(filter-out $(SRCDIR)/$(MAIN_THEORY).o,$(OBJS_$(MAIN_THEORY)))

PVS_TYPECHECK_EXPR := (progn (setq *suppress-output* t) (tc "$(TC_THEORY)" t))
PVS2C_EXPR := (progn (setq *suppress-output* t) (pvs2c-theory "$(MAIN_THEORY)" t))

ifneq ($(filter clean,$(MAKECMDGOALS)),clean)
-include $(GENERATED_MK)
endif

.PHONY: all run typecheck pvs2c clean

all: $(BIN)

run: $(GENERATED_TEST_BIN) $(BIN)
	@./$(GENERATED_TEST_BIN)
	@./$(BIN)

typecheck: $(TYPECHECK_LOG)

pvs2c: $(GENERATED_HEADER)

$(BUILD_DIR) $(BINDIR):
	@mkdir -p $@

$(TYPECHECK_LOG): $(PVS_SOURCES) $(MAKE_DEPS) | $(BUILD_DIR)
	@echo "[$(DEMO)] Typechecking $(TC_THEORY)"
	@$(PVS) -raw -E '$(PVS_TYPECHECK_EXPR)' > $@
	@if grep -q "^In file " $@; then cat $@; exit 1; fi

$(PVS2C_STAMP): $(PVS_SOURCES) $(MAKE_DEPS) $(TYPECHECK_LOG) | $(BUILD_DIR)
	@echo "[$(DEMO)] Generating C for $(MAIN_THEORY)"
	@$(PVS) -raw -E '$(PVS2C_EXPR)' > $(PVS2C_LOG)
	@if grep -q "^In file " $(PVS2C_LOG); then cat $(PVS2C_LOG); exit 1; fi
	@test -f $(GENERATED_HEADER)
	@test -f $(GENERATED_MK)
	@touch $@

$(GENERATED_HEADER) $(GENERATED_MK): $(PVS2C_STAMP)
	@:

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(GENERATED_HEADER)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN): driver.c $(GENERATED_TEST_BIN) $(MAKE_DEPS) ../pvs2c_compat.h | $(BUILD_DIR)
	@echo "[$(DEMO)] Building driver"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(GENERATED_LIB_OBJS) driver.c -o $@ $(LDLIBS)

clean:
	@rm -rf $(BUILD_DIR) pvs2c Makefile.bak
