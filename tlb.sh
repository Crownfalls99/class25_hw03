#!/bin/bash
for((num=1;num<=8192;num=num*2))
do
	time=$(./tlb $num 10000)
	echo "$num pages:  $time" >> analysis.txt
	echo "$num"
done

