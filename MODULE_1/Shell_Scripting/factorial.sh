#!/bin/bash

echo "Enter a number: "
read num
fact=1
i=1
while [ $i -le $num ]
do
	fact=$((fact*i))
	((i++))
done
echo "The factorial of $num is $fact"	
