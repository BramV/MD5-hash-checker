#!/bin/bash

if [ $(which gcc) ]; then
	COMPILER=gcc
else
	COMPILER=clang
fi

$COMPILER -o md5-test test.c md5.c hex.c
$COMPILER -o unhasher main.c md5.c hex.c
