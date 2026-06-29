# ==========================================
# 1. CONFIGURATION
# ==========================================
CC       := cc
PVS_HOME ?= $(HOME)/git/PVS
CFLAGS   := -w -O2 -foptimize-sibling-calls -fPIC -I$(PVS_HOME)/lib/pvs2c/include -I pvs2c/include
LDFLAGS  := -L$(PVS_HOME)/lib/pvs2c/lib
LDLIBS   := -lgmp -lpvs-prelude
BINDIR   := pvs2c/bin
LIBDIR   := pvs2c/lib
SRCDIR   := pvs2c/src

# ==========================================
# 2. INCLUDE DYNAMIC FRAGMENTS
# ==========================================
-include pvs2c/include/*.mk

# ==========================================
# 3. GENERIC RULES
# ==========================================
.PHONY: all clean

# Ensure build directories exist
$(BINDIR) $(LIBDIR):
	mkdir -p $@

# Standard C compilation -> output to BUILDDIR
$(SRCDIR)/%.o: %.c | $(SRCDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ==========================================
# 4. SMART CLEAN
# ==========================================
clean:
	@echo "--- Cleaning ---"
	rm -rf $(BUILDDIR) $(BINDIR) $(LIBDIR)
