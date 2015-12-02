#!/usr/bin/env bash

CXX = g++
LN = g++
RM = @rm
ECHO = @echo

CXXFLAGS = -O3 -std=gnu++11 -Wall -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused
LNFLAGS =
COMPILEFLAG = -c
INCFLAG = -I
OUTPUT = -o
RMFLAGS = -rf

DFLAGS = -DCOLORS

S = src
B = build
SRC = ConfigReader.cpp Document.cpp DotFileWriter.cpp HistoryManager.cpp Logger.cpp LogReader.cpp
OBJ = $(SRC:%.cpp=$(B)/%.o)
MAIN = $(S)/main.cpp

LIBS =
LIBPATH =
INCPATH = include/

BIN = $(B)/tp-oo_3
MK_D = @mkdir -p $(@D)

ALL = all
CLEAN = clean

.PHONY: $(ALL) $(CLEAN)

$(ALL): $(BIN)

$(BIN): $(OBJ) $(MAIN)
	$(MK_D)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT) $@ $(INCFLAG)$(INCPATH) $(DFLAGS)

$(B)/%.o: $(S)/%.cpp $(S)/%.h
	$(MK_D)
	$(CXX) $(CXXFLAGS) $(COMPILEFLAG) $< $(OUTPUT) $@ $(INCFLAG)$(INCPATH) $(DFLAGS)
	
$(CLEAN):
	$(RM) $(RMFLAGS) $(B)
