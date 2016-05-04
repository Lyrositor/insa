CXX = msp430-gcc
LN = msp430-gcc
RM = @rm
ECHO = @echo

CXXFLAGS = -mmcu=msp430fg4618 -Wall -Werror -O1
LNFLAGS = -mmcu=msp430fg4618 -mdisable-watchdog
COMPILEFLAG = -c
OUTPUT = -o
RMFLAGS = -rf

DEFINITIONS =

BUILDDIR = bin
SRCDIR = src
SRC = lcd.c
MAIN = src/tp3.s
OBJ = $(SRC:%.cpp=$(BUILDDIR)/%.o)

LIBS =
LIBPATH =
INCPATH =

BIN = $(BUILDDIR)/tp3
MK_D = @mkdir -p $(@D)
MK_MODULE = $(CXX) $(CXXFLAGS) $(COMPILEFLAG) $< $(OUTPUT) $@ $(INCPATH) $(DEFINITIONS) $(LIBPATH) $(LIBS)

ALL = all
CLEAN = clean

.PHONY: $(ALL) $(CLEAN)

$(ALL): $(BIN)

$(CLEAN):
	$(RM) $(RMFLAGS) $(BIN) $(BUILDDIR)/*.o

$(BIN): $(OBJ) $(MAIN)
	$(MK_D)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT) $@ $(INCPATH) $(DEFINITIONS) $(LIBPATH) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h $(SRCDIR)/Config.h
	$(MK_D)
	$(MK_MODULE)
