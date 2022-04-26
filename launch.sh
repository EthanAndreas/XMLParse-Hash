#!/bin/bash

echo -e "\n$(tput setaf 2)    Compilation   \n==================\n$(tput setaf 7)"

#compilation de base du programme
make clean
make 

#Display
echo -e "$(tput setaf 2)\n==================\nEnd of compilation\n\n$(tput setaf 7)" 

#Display
echo -e "$(tput setaf 4)Program's launching\n===================\n$(tput setaf 7)"

#Program's launching with read and write files

./bin/exe $@

#Display
echo -e "$(tput setaf 4)\n===================\n  End of programm  \n$(tput setaf 7)"
