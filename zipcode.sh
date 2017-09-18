#!/bin/sh

#scrapes web for zipcodes

#usage
if [ "$1" == "-h" ]; then
    echo "Usage: zipcode.sh
            
            -c      CITY    Which city to search
            -f      FORMAT  Which format (text, csv)
            -s      STATE   Which stat to search (Indiana)

            If no city is specified, then all the zip codes for the state aredisplayed"
    exit 1
fi

#variable initial
CITY="NA"
FORMAT="text"
STATE="Indiana"

# tags
while [ $# -gt 0 ] 
do
    case $1 in
        -c) CITY="$2"
            shift 
            ;;
        -f) # makes sure format is valid
            if [ $2 != "text" ] && [ $2 != "csv" ]; then
                echo "invalid format"
                exit 1
            fi
            FORMAT=$2
            shift 
            ;;
        -s) STATE=$(echo "$2" | sed 's_ _%20_' )
            shift 
            ;;
    esac
    shift
done
##
# logic for displaying
##
#no city text
if [ "$CITY" == "NA" ] && [ $FORMAT == "text" ]; then
    curl -s http://www.zipcodestogo.com/$STATE/ | grep -Eo '>[0-9]{5}<' | grep -Eo [0-9]{5}

#no city csv
elif [ "$CITY" == "NA" ] && [ $FORMAT == "csv" ]; then
    curl -s http://www.zipcodestogo.com/$STATE/ | grep -Eo '>[0-9]{5}<' | grep -Eo [0-9]{5} | tr "\n" "," | sed 's|.$|\n|'

#city text
elif [ "$CITY" != "NA" ] && [ $FORMAT = "text" ]; then
    curl -s http://www.zipcodestogo.com/$STATE/ | grep -E "/$CITY/" | grep -Eo '>[0-9]{5}<' | grep -Eo [0-9]{5}

#city csv
elif [ "$CITY" != "NA" ] && [ $FORMAT == "csv" ]; then
    curl -s http://www.zipcodestogo.com/$STATE/ | grep -E "/$CITY/" | grep -Eo '>[0-9]{5}<' | grep -Eo [0-9]{5} | tr "\n" "," | sed 's|.$|\n|'

fi

exit 0
           
