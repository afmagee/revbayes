#!/bin/sh
if [ "$1" = "clean" ]
then
	rm -rf build
else
if [ ! -d build ]; then
	mkdir build
fi

    #################
    # generate git version number
    ./generate_version_number.sh
    cp ../../src/revlanguage/utils/GitVersion.cpp GitVersion_backup.cpp
    mv GitVersion.cpp ../../src/revlanguage/utils/

	./regenerate.sh $@
	cd build 
	CC=gcc CXX=g++ cmake .
	make -j 8
	cd ..
	
    cp GitVersion_backup.cpp ../../src/revlanguage/utils/GitVersion.cpp
    rm GitVersion_backup.cpp
fi
