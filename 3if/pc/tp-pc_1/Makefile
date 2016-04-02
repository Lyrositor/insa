CXX = g++
LN = g++
RM = @rm
ECHO = @echo

CXXFLAGS = -O3 -Wall -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wextra -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef
LNFLAGS =
COMPILEFLAG = -c
OUTPUT = -o
RMFLAGS = -rf

DEFINITIONS = -DNDEBUG -DMAP

BUILDDIR = bin
SRCDIR = src
SRC = BarriereEntree.cpp BarriereSortie.cpp Config.cpp Simulateur.cpp Utils.cpp
MAIN = src/Mere.cpp
OBJ = $(SRC:%.cpp=$(BUILDDIR)/%.o)

LIBS = -ltp -lncurses -ltcl
LIBPATH = -Llib/ -L/shares/public/tp/tp-multitache
INCPATH = -Iinclude/ -I/shares/public/tp/tp-multitache

BIN = $(BUILDDIR)/Parking
MK_D = @mkdir -p $(@D)
MK_MODULE = $(CXX) $(CXXFLAGS) $(COMPILEFLAG) $< $(OUTPUT) $@ $(INCPATH) $(DEFINITIONS) $(LIBPATH) $(LIBS)

ALL = all
CLEAN = clean

.PHONY: $(ALL) $(CLEAN)

$(ALL): $(BIN)

$(CLEAN):
	$(RM) $(RMFLAGS) $(BUILD) *.o

$(BIN): $(OBJ) $(MAIN)
	$(MK_D)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT) $@ $(INCPATH) $(DEFINITIONS) $(LIBPATH) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h $(SRCDIR)/Config.h
	$(MK_D)
	$(MK_MODULE)
