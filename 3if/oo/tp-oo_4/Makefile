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
SRC = src/Canvas.cpp src/ConvexPolygon.cpp src/Editor.cpp src/Figure.cpp src/FigureGroup.cpp src/HistoryManager.cpp src/Intersection.cpp src/Polygon.cpp src/Rectangle.cpp src/Segment.cpp src/Union.cpp src/Vector2D.cpp
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

$(BUILD)/src/Canvas.o: src/Canvas.cpp src/Canvas.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/ConvexPolygon.o: src/ConvexPolygon.cpp src/ConvexPolygon.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Editor.o: src/Editor.cpp src/Editor.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Figure.o: src/Figure.cpp src/Figure.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/FigureGroup.o: src/FigureGroup.cpp src/FigureGroup.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/HistoryManager.o: src/HistoryManager.cpp src/HistoryManager.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Intersection.o: src/Intersection.cpp src/Intersection.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Polygon.o: src/Polygon.cpp src/Polygon.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Rectangle.o: src/Rectangle.cpp src/Rectangle.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Segment.o: src/Segment.cpp src/Segment.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Union.o: src/Union.cpp src/Union.h
	$(MK_D)
	$(MK_MODULE)

$(BUILD)/src/Vector2D.o: src/Vector2D.cpp src/Vector2D.h
	$(MK_D)
	$(MK_MODULE)
