# Auto-generated fragment for dpeg
OBJS_dpeg := $(SRCDIR)/dpeg.o $(SRCDIR)/dpeg_c.o $(SRCDIR)/stringutils_c.o  
pvs2c/bin/dpeg: $(OBJS_dpeg) | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: dpeg
dpeg: pvs2c/bin/dpeg

.PHONY: run_dpeg
run_dpeg: dpeg
	./pvs2c/bin/dpeg
