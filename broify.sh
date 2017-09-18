#!/bin/sh

# script that removes the comments and whitespace of files
if [ "$1" == "-h" ]; then
    echo "Usage: broify.sh
         -d DELIM  Use this as te comment delimiter.   
         -W        Don't strip empty lines."
    exit 1
fi

if [ "$1" == "-d" ] && [ "$3" != "-W" ]; then
    DELIMITER=$2 
    sed "s|$DELIMITER.*$||; s|\s*$||; /^$/d"
elif [ "$1" == "-W" ]; then
    DELIMITER="#"
    sed "s|$DELIMITER.*$||; s|\s*$||"
elif [ "$3" == "-W" ]; then
    DELIMITER=$2
    sed "s|$DELIMITER.*$||; s|\s*$||"
elif [ "$1" == "-dW" ] || [ "$1" == "-Wd" ]; then
    DELIMITER=$2
    sed "s|$DELIMITER.*$||; s|\s*$||"
elif [ $# -eq 0 ]; then
    DELIMITER="#"
    sed "s|$DELIMITER.*$||; s|\s*$||; /^$/d"
fi
