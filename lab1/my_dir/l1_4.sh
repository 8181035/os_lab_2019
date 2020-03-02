#!/bin/sh

MAXCOUNT=150
count=1

while [ "$count" -le $MAXCOUNT ]     
do
  r=$(od -A n -t d -N 1 /dev/urandom)
  echo $r >> numbers.txt
  let "count += 1"  
done