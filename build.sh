#!/usr/bin/env bash

TOOLCHAIN=""

TOOLCHAINS_HOME="/opt/toolchains"


. $TOOLCHAINS_HOME/include/log.sh


# If you need environment, we only import environment variables and global variable.
case $0 in
	*bash)
		if [ -z "$1" -a -z "$TOOLCHAIN" ]; then
			warnning 2 "Miss var 'TOOLCHAIN', please set this variable in $0!" 
			return 
		fi
		IMPORT=1
	;;
esac

. $TOOLCHAINS_HOME/include/environment.sh 

if [ -z $TOOLCHAIN ]; then
	test -n "$IMPORT" && return || exit
fi

echo "The toolchain ($TOOLCHAIN) environment was initialized successfully!"

#If this script was include, we only set environment variable & global variable.
test -n "$IMPORT" && return

########## Build Project ##########
notice 1 "Start build module ..."

