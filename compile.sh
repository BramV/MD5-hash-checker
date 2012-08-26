#!/bin/bash
clear
if [ $(which gcc) ]; then
	COMPILER=gcc
else
	COMPILER=clang
fi

$COMPILER -o md5-test test.c md5.c hex.c
$COMPILER -o unhasherBruteForce bruteforce.c md5.c hex.c
$COMPILER -o unhasherDictonary dict.c md5.c hex.c
