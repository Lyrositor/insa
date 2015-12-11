#!/usr/bin/env bash

RM = @rm
GHDL = ghdl
GTKWAVE = gtkwave

RMFLAGS = -rf

CLEAN = clean

ifeq ($(OS),Windows_NT)
	RUNTEST = $(GHDL) -r $< --stop-time=256ns --vcd=$<.vcd && $(GTKWAVE) $<.vcd
else
	RUNTEST = ./$< --stop-time=256ns --vcd=$<.vcd && $(GTKWAVE) $<.vcd
endif

.PHONY: passage_a_niveau testbench_passage_a_niveau test_passage_a_niveau $(CLEAN)

$(CLEAN):
	$(RM) $(RMFLAGS) *.o work-obj93.cf *.vcd

# Modules
passage_a_niveau: passage_a_niveau.vhdl
	$(GHDL) -a passage_a_niveau.vhdl

testbench_passage_a_niveau: passage_a_niveau testbench_passage_a_niveau.vhdl
	$(GHDL) -a testbench_passage_a_niveau.vhdl
	$(GHDL) -e testbench_passage_a_niveau

diviseur: diviseur.vhdl
	$(GHDL) -a diviseur.vhdl

testbench_diviseur: diviseur testbench_diviseur.vhdl
	$(GHDL) -a testbench_diviseur.vhdl
	$(GHDL) -e testbench_diviseur

diviseur_rapide: diviseur_rapide.vhdl
	$(GHDL) -a diviseur_rapide.vhdl

testbench_diviseur_rapide: diviseur_rapide testbench_diviseur_rapide.vhdl
	$(GHDL) -a testbench_diviseur_rapide.vhdl
	$(GHDL) -e testbench_diviseur_rapide

# Tests
test_passage_a_niveau: testbench_passage_a_niveau
	$(RUNTEST)

test_diviseur: testbench_diviseur
	$(RUNTEST)

test_diviseur_rapide: testbench_diviseur_rapide
	$(RUNTEST)