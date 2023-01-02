#!/bin/bash

TESTS_TO_RUN=100

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

shopt -s nullglob
FAILED_TESTS=""

for i in inFiles/test*.in
do
	if [ ${i//[^0-9]/} -gt $TESTS_TO_RUN ]; then
		continue
	fi
	
	printf "test $i >>>  "
	./InOutTester < $i > outFiles/test${i//[^0-9]/}.result
	diff outFiles/test${i//[^0-9]/}.out outFiles/test${i//[^0-9]/}.result

	if [ $? -eq 0 ]
	then
		printf "Game Simulation: ${GREEN}pass${NC},   "
	else
		printf "Game Simulation: ${RED}fail${NC},   "
		FAILED_TESTS+='-'
		FAILED_TESTS+='F'
	fi
	valgrind --log-file=$i.valgrind_log --leak-check=full ./InOutTester < $i 1>/dev/null 2>/dev/null
	if [ -f $i.valgrind_log ]
	then
		cat $i.valgrind_log | grep "ERROR SUMMARY: 0" > /dev/null
		if [ $? -eq 0 ]
		then
			printf "Leak: ${GREEN}pass${NC}\n"
		else
			printf "Leak: ${RED}fail${NC}\n"
			cat $i.valgrind_log
			FAILED_TESTS+="-"
		fi
	else
		printf "Leak: ${RED}couldnt get valgrind file${NC}\n"
		FAILED_TESTS+="-"
	fi
	rm $i.valgrind_log
done

if [ -z ${FAILED_TESTS} ]; then
	printf "\n${GREEN} All tests passed :)${NC}\n\n"
else
	printf "\n${RED} Failed ${FAILED_TESTS}${NC} tests.\n\n"
fi
printf "incress TESTS_TO_RUN in tester.sh in order to run more tests (up to 3141)\n"
