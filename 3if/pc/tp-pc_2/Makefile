default: help

help:
	@echo Useful targets:
	@echo "  small.txt medium.txt large.txt many.txt:  generate some input files "
	@echo "  question1 question2 question3 question5 question8: compile your programs"
	@echo "  run1 run2 run3 run5 run8:  run your programs through the 'time' utility"
	@echo "  clean:  delete all generated files"

all: tiny.txt small.txt medium.txt large.txt many.txt question1 question2 question3 question5 question8

#########################
# workload generation

tiny.txt:
	./generator.cs 20 20 0 > $@

small.txt:
	./generator.cs 20 32 50 > $@

medium.txt:
	./generator.cs 20 50 50 > $@

large.txt:
	./generator.cs 20 64 50 > $@

many.txt:
	./generator.cs 1000 50 75 > $@

#########################
## program compilation

question1: question1.c primes.o
	gcc -Wall -pthread -o question1 question1.c primes.o -lm

question2: question2.c primes.o
	gcc -Wall -pthread -o question2 question2.c primes.o -lm

question3: question3.c primes.o
	gcc -Wall -pthread -o question3 question3.c primes.o -lm

question5: question5.c primes.o
	gcc -Wall -pthread -o question5 question5.c primes.o -lm

question8: question8.c primes.o
	gcc -Wall -pthread -o question8 question8.c primes.o -lm

primes.o: primes.c primes.h
	gcc -c -Wall primes.c


# add your own rules when you create new programs

#########################
## program execution

run1: question1
	time -p ./question1

run2: question2
	time -p ./question2 medium.txt

run3: question3
	time -p ./question3 medium.txt

run5: question5
	time -p ./question5 large.txt

run8: question8
	time -p ./question8 large.txt

#########################
## utilities

clean:
	rm -f question1 question2 question3 question5 question6 question8 tiny.txt small.txt medium.txt large.txt many.txt *.o

