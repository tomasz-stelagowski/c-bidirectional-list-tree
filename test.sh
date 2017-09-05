#!/bin/bash

if [[ $# == 2 ]]; then
	for f in $2/*.out; do
		./$1 <"${f%out}in" > out.tmp;
		if diff $f out.tmp &>/dev/null
		then 
			echo "$f : OK"
		else 
			echo "$f : Źle" 
		fi 
	done
elif [[ $# == 3 ]]; then
	for f in $3/*.out; do
		./$2 -v <"${f%out}in" > out.tmp 2> err.tmp
		if diff $f out.tmp &>/dev/null;  then 
			echo "$f : OK";
		else
			echo "$f : Źle";
		fi;
		if  diff "${f%out}err" err.tmp &>/dev/null; then 
			echo "$f wyjscie diagnostyczne: OK";
		else 
			echo "$f wyjscie diagnostyczne: Źle";
		fi
	done
fi