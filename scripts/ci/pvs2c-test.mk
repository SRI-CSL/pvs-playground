ifndef PVS_LOCATION
$(error PVS_LOCATION is not set. Export PVS_LOCATION=/path/to/PVS)
endif

CC ?= cc
CFLAGS ?= -O2 -w -foptimize-sibling-calls -fPIC
CPPFLAGS += -I$(PVS_LOCATION)/lib/pvs2c/include -Iinclude
LDFLAGS += -L$(PVS_LOCATION)/lib/pvs2c/lib
LDLIBS += $(PVS_LOCATION)/lib/pvs2c/lib/libpvs-prelude.a -lgmp -lm

ifneq ($(PVS2C_DEMOS_ROOT),)
ifneq ($(wildcard $(PVS2C_DEMOS_ROOT)/pvs2c_compat.h),)
CPPFLAGS += -include $(PVS2C_DEMOS_ROOT)/pvs2c_compat.h
endif
endif

BINDIR := bin
SRCDIR := src

# Run this helper from the generated pvs2c directory.
-include include/*.mk

$(BINDIR) $(SRCDIR):
	mkdir -p $@

$(SRCDIR)/%.o: $(SRCDIR)/%.c | $(SRCDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
