#!/usr/bin/env bash

RM = @rm
GHDL = ghdl
GTKWAVE = gtkwave

RMFLAGS = -rf

CLEAN = clean

ifeq ($(OS),Windows_NT)
	RUNTEST = $(GHDL) -r $< --stop-time=64ns --vcd=$<.vcd && $(GTKWAVE) $<.vcd
else
	RUNTEST = ./$< --stop-time=64ns --vcd=$<.vcd && $(GTKWAVE) $<.vcd
endif

.PHONY: memory256x8 processor testbench test $(CLEAN)

$(CLEAN):
	$(RM) $(RMFLAGS) *.o work-obj93.cf *.vcd

# Modules
register_1: ../tp-ac_1/register_1.vhdl
	$(GHDL) -a ../tp-ac_1/register_1.vhdl
	
register_n: register_1 ../tp-ac_1/register_n.vhdl
	$(GHDL) -a ../tp-ac_1/register_n.vhdl

memory256x8: memory256x8.vhdl
	$(GHDL) -a memory256x8.vhdl

processor: register_n processor.vhdl
	$(GHDL) -a processor.vhdl

testbench: memory256x8 processor testbench.vhdl
	$(GHDL) -a testbench.vhdl
	$(GHDL) -e testbench

# Tests
test: testbench
	$(RUNTEST)
