#!/bin/sh

get_message() {
    shuf <<EOF | head -n 1 | cowsay
It is certain
It is decidedly so
Without a doubt
Yes, definitely
You may rely on it
As I see it, yes
Most likely
Oulook good
Yes
Signs point to yes
Reply hazy try again
Ask again later
Better not tell you now
Cannot predict now
Concentrate and ask again
Don't count on it
My reply is no
My sources say no
Oulook not so good
Very doubtful
EOF
}

early_exit() {
    cowsay "Sorry to see ya go so soon!"
    exit 1
}

cowsay "I know everything"

INPUT_STRING=""

while [ 1 ] 
do
    trap early_exit HUP INT TERM
    read -p "Question? " INPUT_STRING
    if [ "$INPUT_STRING" != "" ]; then
        get_message
    fi
done


