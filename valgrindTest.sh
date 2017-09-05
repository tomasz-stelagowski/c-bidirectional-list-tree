#!/bin/bash

if [[ $# == 2 ]]; then
	for f in $2/*.out; do
		valgrind ./$1 <"${f%out}in" > out.tmp;
		if diff $f out.tmp &>/dev/null
		then 
			echo "$f : OK\n"
		else 
			echo "$f : Źle\n" 
		fi 
	done
fi