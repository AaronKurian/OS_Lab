#!/bin/bash
echo "Enter a Number"
read num
sum=0
while [ $num -ne 0 ]
do
	ld=$((num%10))
	sum=$((sum+ld))
	num=$((num/10))
done
echo "The sum of Digits is $sum"
