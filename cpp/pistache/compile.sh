#!/usr/bin/env bash

echo -e "${GREEN}Build or Debug mode? (build/debug)${NC}"
read -r mode

if make -sj4 -C "${mode}/"; then
  echo "Running..."
  sleep 1
  "./${mode}/PISTACHERestAPI"
else
  echo "Error on compiling!"
fi
