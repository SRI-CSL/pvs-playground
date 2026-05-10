# Auto-generated fragment for stringutils
OBJS_stringutils := $(SRCDIR)/stringutils.o $(SRCDIR)/stringutils_c.o  
pvs2c/bin/stringutils: $(OBJS_stringutils) | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: stringutils
stringutils: pvs2c/bin/stringutils

.PHONY: run_stringutils
run_stringutils: stringutils
	./pvs2c/bin/stringutils
