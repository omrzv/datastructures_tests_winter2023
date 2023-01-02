#!/bin/bash

for i in outFiles/test*.result
do
	rm $i
done

printf "cleaned all .result files\n"
