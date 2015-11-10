#!/usr/bin/env bash

CXX = g++
LN = g++
RM = @rm
ECHO = @echo

CXXFLAGS = -O3 -Wall -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused
LNFLAGS =
COMPILEFLAG = -c
OUTPUT = -o
RMFLAGS = -rf

S = src
B = build
SRC = City.cpp Event.cpp EventLink.cpp HashTable.cpp Sensor.cpp SegmentedTable.cpp
OBJ = $(SRC:%.cpp=$(B)/%.o)
MAIN = $(S)/main.cpp

LIBS =
LIBPATH =
INCPATH =

BIN = $(B)/tp-oo_2
MK_D = @mkdir -p $(@D)

ALL = all
CLEAN = clean

.PHONY: $(ALL) $(CLEAN)

$(ALL): $(BIN)

$(BIN): $(OBJ) $(MAIN) $(S)/config.h
	$(MK_D)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT) $@

$(B)/City.o: $(S)/City.cpp $(S)/City.h $(S)/Event.h $(S)/EventLink.h $(S)/HashTable.h $(S)/SegmentedTable.h $(S)/config.h
	$(MK_D)
	$(CXX) $(CXXFLAGS) $(COMPILEFLAG) $(S)/City.cpp $(OUTPUT) $@

$(B)/Event.o: $(S)/Event.cpp $(S)/Event.h $(S)/config.h
	$(MK_D)
	$(CXX) $(CXXFLAGS) $(COMPILEFLAG) $(S)/Event.cpp $(OUTPUT) $@

$(B)/EventLink.o: $(S)/EventLink.cpp $(S)/EventLink.h
	$(MK_D)
	$(CXX) $(CXXFLAGS) $(COMPILEFLAG) $(S)/EventLink.cpp $(OUTPUT) $@

$(B)/HashTable.o: $(S)/HashTable.cpp $(S)/HashTable.h
	$(MK_D)
	$(CXX) $(CXXFLAGS) $(COMPILEFLAG) $(S)/HashTable.cpp $(OUTPUT) $@

$(B)/SegmentedTable.o: $(S)/Event.h $(S)/EventLink.h $(S)/SegmentedTable.cpp $(S)/SegmentedTable.h
	$(MK_D)
	$(CXX) $(CXXFLAGS) $(COMPILEFLAG) $(S)/SegmentedTable.cpp $(OUTPUT) $@

$(B)/Sensor.o: $(S)/Event.h $(S)/EventLink.h $(S)/SegmentedTable.cpp $(S)/Sensor.cpp $(S)/Sensor.h
	$(MK_D)
	$(CXX) $(CXXFLAGS) $(COMPILEFLAG) $(S)/Sensor.cpp $(OUTPUT) $@

$(CLEAN):
	$(RM) $(RMFLAGS) $(B)