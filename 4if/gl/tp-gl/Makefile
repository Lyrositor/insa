CXX = clang++
LN = clang++
RM = @rm
ECHO = @echo

CXXFLAGS = -O3 -Wall -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wextra -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -std=gnu++11
LNFLAGS =
COMPILEFLAG = -c
INCFLAG = -I
OUTPUT = -o
RMFLAGS = -rf

DEFINITIONS = -DNDEBUG

BUILD = bin
SRC = src/lexer.cpp src/parser.cpp src/states.cpp src/tokens.cpp
OBJ = $(SRC:%.cpp=$(BUILD)/%.o)
MAIN = src/main.cpp

LIBS =
LIBPATH =
INCPATH =

BIN = $(BUILD)/tp-gl
MK_D = @mkdir -p $(@D)
MK_MODULE = $(CXX) $(CXXFLAGS) $(COMPILEFLAG) $< $(OUTPUT) $@ $(INCPATH) $(DEFINITIONS) $(LIBS)

ALL = all
CLEAN = clean

.PHONY: $(ALL) $(CLEAN)

$(ALL): $(BIN)

$(CLEAN):
	$(RM) $(RMFLAGS) $(BUILD) *.o

$(BIN): $(OBJ) $(MAIN)
	$(MK_D)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT) $@ $(INCPATH) $(DEFINITIONS) $(LIBS)

$(BUILD)/src/lexer.o: src/lexer.cpp src/lexer.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/parser.o: src/parser.cpp src/parser.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/states.o: src/states.cpp src/states.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/tokens.o: src/tokens.cpp src/tokens.h
	$(MK_D)
	$(MK_MODULE)
