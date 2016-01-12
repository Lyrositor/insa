CXX = g++
LN = g++
RM = @rm
ECHO = @echo

CXXFLAGS = -O3 -Wall -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wextra -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -std=gnu++11
LNFLAGS = 
COMPILEFLAG = -c
INCFLAG = -I
OUTPUT = -o
RMFLAGS = -rf

DEFINITIONS = -DNDEBUG

BUILD = bin
SRC = 
OBJ = $(SRC:%.cpp=$(BUILD)/%.o)
MAIN = src/main.cpp

LIBS = 
LIBPATH =
INCPATH = include

BIN = $(BUILD)/tp-oo_4
MK_D = @mkdir -p $(@D)
MK_MODULE = $(CXX) $(CXXFLAGS) $(COMPILEFLAG) $< $(OUTPUT) $@ $(INCFLAG)$(INCPATH) $(DEFINITIONS) $(LIBS)

ALL = all
CLEAN = clean

.PHONY: $(ALL) $(CLEAN)

$(ALL): $(BIN)

$(CLEAN):
	$(RM) $(RMFLAGS) $(BUILD) *.o

$(BIN): $(OBJ) $(MAIN)
	$(MK_D)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT) $@ $(INCFLAG)$(INCPATH) $(DEFINITIONS) $(LIBS)
