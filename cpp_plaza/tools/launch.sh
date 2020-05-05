#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

make re > /dev/null

if      [ -f "plazza" ]
then
    echo -e "${GREEN}Testing plazza...${NC}"
else
    echo -e "${RED}Please fix your makefile errors${NC}"
    exit 84
fi

cat tools/liberty_cmd | ./plazza 5

make fclean > /dev/null
