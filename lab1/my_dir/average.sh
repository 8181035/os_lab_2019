#!/bin/sh

echo There were $# parameters passed.

s=0
for param in "$@"
do
s=$(($s+param))
done

echo " Ans = $(($s/$#))"