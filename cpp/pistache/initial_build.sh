#!/usr/bin/env bash

ESC="\e["

GREEN="${ESC}0;32m"
RED="${ESC}0;31m"
NC="${ESC}0m"

echo -e "${RED}Deleting${NC} current build folder"
rm -rf build
echo -e "${GREEN}Creating${NC} new build folder"
mkdir -p build
echo -e "${GREEN}Building with cmake${NC}"
cmake --build build -DUSE_CCACHE=ON -DCPM_SOURCE_CACHE=.cache/CPM
if [ $? -eq 0 ]; then
  echo -e "${GREEN}Building with cmake${NC}"
  cd .. && bear -- make -sj4 -C build
else
  echo -e "${RED}Error building!${NC}"
fi
