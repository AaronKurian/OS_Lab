#!/bin/bash

#1st cmd
echo "Hello, World!"

#2nd cmd
name="Aaron"
echo "Hii, $name!"

#3rd cmd
echo "Enter ur name: "
read name
echo "Hello, $name!"

#4th cmd
echo "Enter a number: "
read num

if [ $num -gt 10 ]; then
	echo "The number is greater than 10"
else
	echo "The number is less than 10"
fi

#5th cmd
for i in 1 2 3 4 5 
do 
	echo "Number: $i"
done

#6th cmd
count=1
while [ $count -le 5 ]
do
	echo "Count: $count"
	((count++))
done


#7th cmd
greet() {
    echo "Hello, $1!"
}

greet "Bob"

#8th cmd
echo "Hello"
if [ $? -eq 0 ]; then
    echo "The last command was successful."
else
    echo "The last command failed."
fi
