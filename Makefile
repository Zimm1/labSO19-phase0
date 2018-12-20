# Cross toolchain variables
# If these are not in your path, you can make them absolute.
XT_PRG_PREFIX = mipsel-linux-gnu-
CC = $(XT_PRG_PREFIX)gcc
LD = $(XT_PRG_PREFIX)ld

# uMPS2-related paths

# Simplistic search for the umps2 install. prefix. If you have umps2
# installed on some weird location, set UMPS2_DIR_PREFIX by hand.
ifneq ($(wildcard /usr/bin/umps2),)
    UMPS2_DIR_PREFIX = /usr
else
    UMPS2_DIR_PREFIX = /usr/local
endif

UMPS2_DATA_DIR = $(UMPS2_DIR_PREFIX)/share/umps2
UMPS2_INCLUDE_DIR = $(UMPS2_DIR_PREFIX)/include/umps2

# Compiler options
CFLAGS_LANG = -ffreestanding -ansi
CFLAGS_MIPS = -mips1 -mabi=32 -mno-gpopt -G 0 -mno-abicalls -fno-pic -mfp32
CFLAGS = $(CFLAGS_LANG) $(CFLAGS_MIPS) -I$(UMPS2_INCLUDE_DIR) -Wall -O0

# Linker options
LDFLAGS = -G 0 -nostdlib -T $(UMPS2_DATA_DIR)/umpscore.ldscript

# Add the location of crt*.S to the search path
VPATH = $(UMPS2_DATA_DIR)

.PHONY : all clean

all : examples/network/kernel.core.umps examples/disk/kernel.core.umps

examples/network/kernel.core.umps : examples/network/kernel
	umps2-elf2umps -k $<

examples/network/kernel : examples/network/network_example.o libraries/network/network.o libraries/terminal/terminal.o utils/system/system_utils.o utils/print/print_utils.o utils/converter/converter_utils.o crtso.o libumps.o
	$(LD) -o $@ $^ $(LDFLAGS)

examples/disk/kernel.core.umps: examples/disk/kernel
	umps2-elf2umps -k $<

examples/disk/kernel : examples/disk/disk_test.o libraries/terminal/terminal.o libraries/disk/disk.o utils/system/system_utils.o  utils/converter/converter_utils.o crtso.o libumps.o
	$(LD) -o $@ $^ $(LDFLAGS)

clean :
	find . -name "*.o" -o -name "kernel" -o -name "kernel.*.umps" -type f|xargs rm -f

# Pattern rule for assembly modules

%.o : %.S
	$(CC) $(CFLAGS) -c -o $@ $<
