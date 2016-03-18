CXX = g++
LN = g++
RM = @rm
ECHO = @echo

CXXFLAGS = -O3 -Wall -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wextra -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef
LNFLAGS = 
COMPILEFLAG = -c
INCFLAG = -I
LIBFLAG = -L
OUTPUT = -o
RMFLAGS = -rf

DEFINITIONS = -DNDEBUG -DMAP

BUILDDIR = bin
SRCDIR = src
SRC = 
MAIN = src/Mere.cpp src/Simulateur.cpp src/BarriereEBPP.cpp
OBJ = $(SRC:%.cpp=$(BUILDDIR)/%.o)

LIBS = -lncurses -ltcl -ltp
LIBPATH = lib/#;/share/public/tp/tp-multitache
INCPATH = include/#;/share/public/tp/tp-multitache

BIN = $(BUILDDIR)/tp-pc_1
MK_D = @mkdir -p $(@D)
MK_MODULE = $(CXX) $(CXXFLAGS) $(COMPILEFLAG) $< $(OUTPUT) $@ $(INCFLAG) $(INCPATH) $(DEFINITIONS) $(LIBFLAG) $(LIBPATH) $(LIBS)

ALL = all
CLEAN = clean

.PHONY: $(ALL) $(CLEAN)

$(ALL): $(BIN)

$(CLEAN):
	$(RM) $(RMFLAGS) $(BUILD) *.o

$(BIN): $(OBJ) $(MAIN)
	$(MK_D)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT) $@ $(INCFLAG) $(INCPATH) $(DEFINITIONS) $(LIBFLAG) $(LIBPATH) $(LIBS)

$(BUILD)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(MK_D)
	$(MK_MODULE)
