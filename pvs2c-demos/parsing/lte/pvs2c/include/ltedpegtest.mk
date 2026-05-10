# Auto-generated fragment for ltedpegtest
OBJS_ltedpegtest := $(SRCDIR)/ltedpegtest.o $(SRCDIR)/ltedpegtest_c.o $(SRCDIR)/arrayCount_c.o $(SRCDIR)/stringutils_c.o $(SRCDIR)/dpeg_c.o $(SRCDIR)/ltedpeg_c.o  
pvs2c/bin/ltedpegtest: $(OBJS_ltedpegtest) | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: ltedpegtest
ltedpegtest: pvs2c/bin/ltedpegtest

.PHONY: run_ltedpegtest
run_ltedpegtest: ltedpegtest
	./pvs2c/bin/ltedpegtest
