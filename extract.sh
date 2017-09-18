#!/bin/sh

if [ -z "$1" ]; then
    echo "Usage: extract.sh archive1 archive2..."
    exit 1
else
    for i in $@
    do
        if [[ $i == *".tgz" || $i == *".tar.gz" ]]; then
            tar -xvzf $i
        elif [[ $i == *".tbz" || $i == *".tar.bz2" ]]; then
            tar -xjf $i
        elif [[ $i == *".txz" || $i == *".tar.xz" ]]; then
            tar -Jxvf $i
        elif [[ $i == *".zip" || $i == *".jar" ]]; then
            unzip $i
        fi
    done
fi
exit 0
