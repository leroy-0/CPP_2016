#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

make re > /dev/null

if      [ -f "trade" ]
then
    echo -e "${GREEN}Launching trade...${NC}"
else
    echo -e "${RED}Please fix your makefile errors${NC}"
    exit 84
fi

php tools/trade_moulinette.php -f tools/data/AMAZON1.TXT -p trade -m 100000
if [ $# -eq 0 ]
	then
		php tools/trade_moulinette.php -f tools/data/CISCO1.TXT -p trade -m 100000
		php tools/trade_moulinette.php -f tools/data/boeing5.txt -p trade -m 100000
		php tools/trade_moulinette.php -f tools/data/BAC1.TXT -p trade -m 100000
		php tools/trade_moulinette.php -f tools/data/ibm5.txt -p trade -m 100000
		php tools/trade_moulinette.php -f tools/data/nike5.txt -p trade -m 100000
fi

make fclean > /dev/null
