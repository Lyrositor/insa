CXX = g++
LN = g++
RM = @rm
ECHO = @echo

CXXFLAGS = -Wall
LNFLAGS =
COMPILEFLAG = -c
OUTPUT = -o
RMFLAGS = -f

DIR = src
INT = CollectionEntiers.h
SRC = $(INT:.h=.cpp)
OBJ = $(INT:.h=.o)
MAIN = $(DIR)/main.cpp

LIBS =
LIBPATH =
INCPATH =

BIN = tp-oo_1

ALL = all
CLEAN = clean

.PHONY: $(ALL) $(CLEAN)

$(ALL): $(BIN)

$(BIN): $(OBJ) $(MAIN)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT) $@

CollectionEntiers.o: $(DIR)/CollectionEntiers.h $(DIR)/CollectionEntiers.cpp
	$(CXX) $(CXXFLAGS) $(COMPILEFLAG) $(DIR)/CollectionEntiers.cpp

$(CLEAN):
	$(RM) $(RMFLAGS) $(OBJ) $(BIN) $(BIN).exe