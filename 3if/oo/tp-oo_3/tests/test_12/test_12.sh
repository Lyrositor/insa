#!/usr/bin/env bash

> test_12.log.infile
log_part=`cat test_12.log.part.infile`
for i in {1..10000}
do
    echo "$log_part" >> test_12.log.infile
done
tp-oo_3 test_12.log.infile
rm test_12.log.infile
