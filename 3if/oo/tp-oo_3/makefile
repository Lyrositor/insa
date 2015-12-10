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

DEFINITIONS = -DCOLORS -DNDEBUG -DUSE_BOOST

BUILD = bin
SRC = src/ConfigReader.cpp src/Document.cpp src/DotFileWriter.cpp src/HistoryManager.cpp src/Logger.cpp src/LogEntry.cpp src/LogReader.cpp
OBJ = $(SRC:%.cpp=$(BUILD)/%.o)
MAIN = src/main.cpp

LIBS = -lboost_regex
LIBPATH =
INCPATH = include

BIN = $(BUILD)/tp-oo_3
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

$(BUILD)/src/ConfigReader.o: src/ConfigReader.cpp src/ConfigReader.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Document.o: src/Document.cpp src/Document.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/DotFileWriter.o: src/DotFileWriter.cpp src/DotFileWriter.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/HistoryManager.o: src/HistoryManager.cpp src/HistoryManager.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Logger.o: src/Logger.cpp src/Logger.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/LogEntry.o: src/LogEntry.cpp src/LogEntry.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/LogReader.o: src/LogReader.cpp src/LogReader.h
	$(MK_D)
	$(MK_MODULE)
