#!/bin/bash

if [ $# == 1 ]; then
	if [ ! -d $1 ]; then
		mkdir -p $1
	fi
	repository=$(pwd)
	cd $1
	if [ ! -d ./include ]; then
		mkdir -p include
	fi
	if [ ! -d ./lib ]; then
		mkdir lib
	fi

	if [ -d "${repository}/include" ] && [ -f "${repository}/include/merlin_utility.hpp" ]; then
		cp "${repository}/include/merlin_utility.hpp" ./include/
	else
		echo "[Error] Sources not found - The installation script must be called from the repository (cd to Merlin-utility/)."
	fi
	if [ -d "${repository}/src" ] && [ -f "${repository}/src/merlin_utility.cpp" ]; then
		g++ -shared -fPIC -Wall -Wextra -pedantic -std=c++17 -O2 "${repository}/src/merlin_utility.cpp" -I./include/ -o libmerlin_utility.so
		mv libmerlin_utility.so ./lib/
	else
		echo "[Error] Sources not found - The installation script must be called from the repository (cd to Merlin-utility/)."
	fi
else
	echo "[Error] Expected 1 argument ($# given) - (Only) the installation directory is required."
fi

