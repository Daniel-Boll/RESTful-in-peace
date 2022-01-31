#!/usr/bin/env bash

ESC="\e["

GREEN="${ESC}0;32m"
RED="${ESC}0;31m"
NC="${ESC}0m"

# ask if it's build or debug mode
echo -e "${GREEN}Build or Debug mode? (build/debug)${NC}"
read -r mode

if [ "$mode" == "build" ]; then
  echo -e "${GREEN}Building...${NC}"
  cmake -Bbuild -DCPM_SOURCE_CACHE=.cache/CPM
elif [ "$mode" == "debug" ]; then
  echo -e "${GREEN}Building in debug mode...${NC}"
  cmake -DCMAKE_BUILD_TYPE=Debug -Bdebug -DCPM_SOURCE_CACHE=.cache/CPM
else
  echo -e "${RED}Invalid mode!${NC}"
fi

if [ $? -eq 0 ]; then # Check to see if it succeeded
  echo -e "${GREEN}Building with cmake${NC}"
  bear -- make -sj4 -C "$mode" # Generate the compile_commands.json
else
  echo -e "${RED}Error building!${NC}"
fi
