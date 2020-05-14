# Name of the stuff to build
LIBNAME=      bin/lib/libdcl.a
TESTNAME=     bin/test

# Where to find source code
LIBSRCFLDRS=  src/dcl
TESTSRCFLDRS= src/test
LIBHDRFLDRS=  headers

# Compiler options
# gcc -> Use the gnu c compiler
# -g -> Debugable
# -O2 -> Optimizations including tail recursion
# -Wall -> Show all warnings while compiling
# LDFLAGS -> Include my library in the test application compiling
CC=            gcc
CFLAGS=        -g -O2 -Wall

# Actual files in folders (used folders to simplify makefile)
LIBSRC=        $(foreach folder,$(LIBSRCFLDRS),$(wildcard $(folder)/*.c))
TESTSRC=       $(foreach folder,$(TESTSRCFLDRS),$(wildcard $(folder)/*.c))
HFILES=        $(foreach folder,$(LIBHDRFLDRS),$(wildcard $(folder)/*.h))
LIBINC=        $(addprefix -I,$(LIBHDRFLDRS))
TESTINC=       -Ilib/include
LIBOBJ=        $(shell echo $(foreach file,$(LIBSRC),$(addprefix obj/,$(notdir $(subst .c,.o,$(file))))))

# Generate object files to put into library
.PHONY : all
all : lib $(TESTNAME)

.PHONY : test
test : $(TESTNAME)
$(TESTNAME) : $(LIBNAME) $(TESTSRC)
	$(CC) $(CFLAGS) -Ibin/headers -Lbin/lib $(TESTINC) -o $(TESTNAME) $(TESTSRC) -ldcl

.PHONY : lib
lib : $(LIBNAME)
$(LIBNAME) : $(HFILES) $(LIBSRC)
	mkdir -p bin
	mkdir -p obj
	mkdir -p bin/lib
	mkdir -p bin/headers

	$(foreach file,$(LIBSRC), $(CC) $(CFLAGS) $(LIBINC) -c $(file) -o $(addprefix obj/,$(notdir $(subst .c,.o,$(file))));)

	ar rvs $(LIBNAME) $(LIBOBJ)
	$(foreach file,$(HFILES),cp $(file) $(subst $(dir $(file)),bin/headers/,$(file));)

.PHONY : clean
clean :
	rm -rf bin/
	rm -rf obj/
	