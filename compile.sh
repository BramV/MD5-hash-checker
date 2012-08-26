#!/bin/bash

if [ $(which gcc) ]; then
	COMPILER=gcc
else
	COMPILER=clang
fi

$COMPILER -o analyze_dictionary dictionary_info.c
$COMPILER -o md5-test test.c md5.c hex.c
$COMPILER -o unhasherBruteForce bruteforce.c md5.c hex.c
$COMPILER -o unhasherDictonary dict.c md5.c hex.c
