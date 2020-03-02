#!/bin/sh

echo There were $# parameters passed.
count=0
s=0
for param in $(cat $1)
do
s=$(($s+param))
count=$((count+1))
done

result=$((s/count))
echo "Ans = $result"