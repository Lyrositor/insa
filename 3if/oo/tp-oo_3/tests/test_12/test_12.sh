#!/usr/bin/env bash

> /tmp/test_12.log.infile
log_part=`cat test_12.log.part.infile`
for i in {1..10000}
do
    echo "$log_part" >> /tmp/test_12.log.infile
done
tp-oo_3 /tmp/test_12.log.infile
rm /tmp/test_12.log.infile
