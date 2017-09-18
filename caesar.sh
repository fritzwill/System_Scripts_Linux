#!/bin/sh

LOWER_SOURCE="abcdefghijklmnopqrstuvwxyz"
UPPER_SOURCE="ABCDEFGHIJKLMNOPQRSTUVWXYZ"

if [[ $1 == "-h" ]]; then
    echo "Usage: caesar.sh [rotation]

This program will read from stdin and rotate (shift right) the text by the 
specified rotation. If none is specified, then the default value is 13."
    exit 1
elif [ -z $1 ]; then # checks if $1 exists
    tr a-zA-Z n-za-mN-ZA-M
else
    NUM=$(($1 % 26 + 1)) #how much to shift the numbers
    NUM_LOW=$(($NUM-1))
    LOWER_FIRST=$(echo "$LOWER_SOURCE" | cut -c $NUM) #shift letter to z
    LOWER_SECOND=$(echo "$LOWER_SOURCE" | cut -c $NUM_LOW) #a to letter
    UPPER_FIRST=$(echo "$UPPER_SOURCE" | cut -c $NUM)
    UPPER_SECOND=$(echo "$UPPER_SOURCE" | cut -c $NUM_LOW)
    tr [a-zA-Z] [$LOWER_FIRST-za-$LOWER_SECOND$UPPER_FIRST-ZA-$UPPER_SECOND]
fi

