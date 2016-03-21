#!/usr/bin/env bash

export PATH=$PATH:bin/:../bin/

BIN="tp-oo_4"
NUM_ATTEMPTS=5
NUM_BLOCKS=1000
NUM_SUB_BLOCKS=100
RESULTS_FILE="benchmark.csv"
TMP_INPUT_FILE="/tmp/tp-oo_4-benchmark-input.txt"
TMP_CANVAS_FILE="/tmp/tp-oo_4-benchmark-canvas.txt"

TIME="time -f %e"

echo "Time (without saving);Time (with saving);Time (loading)" > $RESULTS_FILE
exec 3>/dev/null 4>/dev/null

for n in $(seq 1 $NUM_ATTEMPTS)
do
    echo "Attempt #$n"

    # Reset temp files
    > $TMP_INPUT_FILE
    > $TMP_CANVAS_FILE

    # Generate creation commands
    for i in $(seq 1 $NUM_BLOCKS)
    do
        for j in $(seq 1 $NUM_SUB_BLOCKS)
        do
            X1=$RANDOM
            Y1=$RANDOM
            X2=$RANDOM
            Y2=$RANDOM
            echo "S segment_${i}_${j} $X1 $Y1 $X2 $Y2" >> $TMP_INPUT_FILE
            echo "R rectangle_${i}_${j} $X1 $Y1 $X2 $Y2" >> $TMP_INPUT_FILE
        done
        printf "OR union_$i" >> $TMP_INPUT_FILE
        for j in $(seq 1 $NUM_SUB_BLOCKS)
        do
            printf " segment_${i}_${j} rectangle_${i}_${j}" >> $TMP_INPUT_FILE
        done
        printf "\n" >> $TMP_INPUT_FILE
    done
    
    # Test execution time (without saving)
    timeNoSaving=$( TIMEFORMAT="%R"; { time $BIN < $TMP_INPUT_FILE 1>&3 2>&4; } 2>&1)
    echo "Time (without saving): $timeNoSaving"
    
    # Add saving instruction
    echo "SAVE $TMP_CANVAS_FILE" >> $TMP_INPUT_FILE
    
    # Test execution time (with saving)
    timeWithSaving=$( TIMEFORMAT="%R"; { time $BIN < $TMP_INPUT_FILE 1>&3 2>&4; } 2>&1)
    echo "Time (with saving): $timeWithSaving"

    # Test execution time (with loading)
    echo "LOAD $TMP_CANVAS_FILE" > $TMP_INPUT_FILE
    timeLoading=$( TIMEFORMAT="%R"; { time $BIN < $TMP_INPUT_FILE 1>&3 2>&4; } 2>&1)
    echo "Time (loading): $timeLoading"
        
    # Write the results in the summary file

    echo "$timeNoSaving;$timeWithSaving;$timeLoading" >> $RESULTS_FILE
done

exec 3>&- 4>&-
