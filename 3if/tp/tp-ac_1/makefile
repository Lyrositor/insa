#!/usr/bin/env bash

RM = @rm
GHDL = ghdl
GTKWAVE = gtkwave

RMFLAGS = -rf

CLEAN = clean

RUNTEST = ./$< --stop-time=20ns --vcd=$<.vcd && $(GTKWAVE) $<.vcd
RUNTEST_W = $(GHDL) -r $< --stop-time=20ns --vcd=$<.vcd && $(GTKWAVE) $<.vcd

.PHONY: fulladder testbench_fulladder adder testbench_adder clock_generator register_1 register_n testbench_register_8 counter testbench_counter test_fulladder test_fulladder_w test_adder_8 test_adder_8_w test_clock test_clock_w test_register_8 test_register_8_w test_counter test_counter_w $(CLEAN)

# Modules
fulladder: fulladder.vhdl
	$(GHDL) -a fulladder.vhdl

testbench_fulladder: fulladder testbench_fulladder.vhdl
	$(GHDL) -a testbench_fulladder.vhdl
	$(GHDL) -e testbench_fulladder

adder: fulladder adder.vhdl
	$(GHDL) -a adder.vhdl

testbench_adder: adder testbench_adder.vhdl
	$(GHDL) -a testbench_adder.vhdl
	$(GHDL) -e testbench_adder

clock_generator: clock_generator.vhdl
	$(GHDL) -a clock_generator.vhdl
	$(GHDL) -e clock_generator

register_1: register_1.vhdl
	$(GHDL) -a register_1.vhdl

register_n: register_1 register_n.vhdl
	$(GHDL) -a register_n.vhdl

testbench_register_8: register_n testbench_register_8.vhdl
	$(GHDL) -a testbench_register_8.vhdl
	$(GHDL) -e testbench_register_8

counter: adder register_n counter.vhdl
	$(GHDL) -a counter.vhdl

testbench_counter: counter testbench_counter.vhdl
	$(GHDL) -a testbench_counter.vhdl
	$(GHDL) -e testbench_counter

# Tests
test_fulladder: testbench_fulladder
	$(RUNTEST)

test_fulladder_w: testbench_fulladder
	$(RUNTEST_W)

test_adder_8: testbench_adder
	$(RUNTEST)

test_adder_8_w: testbench_adder
	$(RUNTEST_W)

test_clock: clock_generator
	$(RUNTEST)

test_clock_w: clock_generator
	$(RUNTEST_W)

test_register_8: testbench_register_8
	$(RUNTEST)

test_register_8_w: testbench_register_8
	$(RUNTEST_W)

test_counter: testbench_counter
	$(RUNTEST)

test_counter_w: testbench_counter
	$(RUNTEST_W)

$(CLEAN):
	$(RM) $(RMFLAGS) *.o work-obj93.cf *.vcd