#!/usr/bin/env bash

RM = @rm
GHDL = ghdl
GTKWAVE = gtkwave

RMFLAGS = -rf

CLEAN = clean

ifeq ($(OS),Windows_NT)
	RUNTEST = $(GHDL) -r $< --stop-time=64ns --vcd=$<.vcd && $(GTKWAVE) $<.vcd
else
	RUNTEST = ./$< --stop-time=50ns --vcd=$<.vcd && $(GTKWAVE) $<.vcd
endif

.PHONY: memory256x8 processor reg8bits testbench test $(CLEAN)

$(CLEAN):
	$(RM) $(RMFLAGS) *.o work-obj93.cf *.vcd

# Modules	
reg8bits: reg8bits.vhdl
	$(GHDL) -a reg8bits.vhdl

memory256x8: memory256x8.vhdl
	$(GHDL) -a memory256x8.vhdl

processor: reg8bits processor.vhdl
	$(GHDL) -a processor.vhdl

testbench: memory256x8 processor reg8bits testbench.vhdl
	$(GHDL) -a testbench.vhdl
	$(GHDL) -e testbench

# Tests
test: testbench
	$(RUNTEST)
