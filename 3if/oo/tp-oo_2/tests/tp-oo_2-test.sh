#!/usr/bin/env bash
echo -----------------------------------------------------------
echo Tests pour le binome : $1
echo -----------------------------------------------------------

nTestCount=0
nSuccesfulTests=0
nStrResult="$1 "

function run_test {
	echo $2
	let "nTestCount=$nTestCount+1"
	./$1 < $3 > temp1.txt
	grep -v '^#' temp1.txt > temp2.txt
	diff -wB $4 temp2.txt
	if [ $? -eq 0 ]; then
		echo PASSED
		let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
	fi

	rm -f temp1.txt temp2.txt
}

run_test $1 ADD.1 add.1.in add.1.out
run_test $1 STATS_C.2 stats_c.2.in stats_c.2.out
run_test $1 JAM_DH.3 jam_dh.3.in jam_dh.3.out
run_test $1 STATS_D7.4 stats_d7.4.in stats_d7.4.out
run_test $1 OPT.5 opt.5.in opt.5.out
if [ -f max.6.in ]
then
	run_test $1 MAX.6 max.6.in max.6.out
fi

echo -----------------------------------------------------------
echo RESULTS
echo -----------------------------------------------------------
echo Results: $nSuccesfulTests/$nTestCount
echo CSVLine: $nStrResult
echo $nStrResult >> results.txt
