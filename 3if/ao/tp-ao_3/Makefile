AS = msp430-as
C = msp430-gcc
LN = msp430-gcc
RM = @rm
ECHO = @echo

ASFLAGS = -mmcu=msp430fg4618
CFLAGS = -mmcu=msp430fg4618 -Wall -Werror -O1
LNFLAGS = -mmcu=msp430fg4618 -mdisable-watchdog
COMPILEFLAG = -c
OUTPUT = -o
RMFLAGS = -rf

DEFINITIONS =

BUILDDIR = bin
SRCDIR = src
SRC = lcd.c
MAIN = tp3.s
MAINOBJ = $(MAIN:%.s=$(BUILDDIR)/%.o)
OBJ = $(SRC:%.c=$(BUILDDIR)/%.o)

LIBS =
LIBPATH =
INCPATH =

BIN = $(BUILDDIR)/tp3.elf
MK_D = @mkdir -p $(@D)
MK_MODULE = $(C) $(CFLAGS) $(COMPILEFLAG) $< $(OUTPUT) $@ $(INCPATH) $(DEFINITIONS) $(LIBPATH) $(LIBS)

ALL = all
CLEAN = clean
INSTALL = install
RUN = run
DUMP = dump

.PHONY: $(ALL) $(CLEAN) $(INSTALL) $(RUN) $(DUMP)

$(ALL): $(BIN)

$(CLEAN):
	$(RM) $(RMFLAGS) $(BIN) $(BUILDDIR)/*.o

$(INSTALL): $(BIN)
	mspdebug -j -d /dev/ttyUSB0 uif <<< 'prog $(BIN)'
    
$(RUN): $(INSTALL)
	mspdebug -j -d /dev/ttyUSB0 uif <<< 'run'

$(DUMP): $(BIN)
	msp430-objdump -d $(BIN)

$(BIN): $(OBJ) $(MAINOBJ)
	$(MK_D)
	$(LN) $(LNFLAGS) $^ $(OUTPUT) $@ $(INCPATH) $(DEFINITIONS) $(LIBPATH) $(LIBS)

$(MAINOBJ): $(SRCDIR)/$(MAIN)
	$(AS) $(ASFLAGS) $^ $(OUTPUT) $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(MK_D)
	$(MK_MODULE)
