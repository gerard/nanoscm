#!/bin/bash

CODE="((make-lambda 2) (+ 5 1) (* 1 0))"
OUT=`echo $CODE | $1`
if [ "$OUT" != "$CODE" ]
then
    echo FAILED "[echo $CODE | $1]"
    exit 1
fi

CODE="(+ (+ 5 1) (* 1 0))"
OUT=`echo $CODE | $1`
if [ "$OUT" != "$CODE" ]
then
    echo FAILED "[echo $CODE | $1]"
    exit 1
else
    echo PASSED
fi
