#!/bin/bash

# run from github qgama repository

OPTS="";
for opt in "$@"
do
    if [ "$opt" = "-h" ];  then
	echo $0 " [ -q | -u | -s]" ;
	exit 1;
    fi
    echo
    OPTS="${OPTS}  $opt"
done


compare() {
    echo "  " "$1" " "

    for i in `find -name  "$1" | grep -v ./build | grep -v ./gama/`;
    do
	diff ${OPTS} ../gama-qt/rw/$i $i;  # relative path to GNU git repository
    done
}

echo
echo "Finding differences for"
compare "*.cpp"
compare "*.h"
compare "*.txt"
compare "*.md"
compare '*.gkf'
compare "*.dox"
compare "*.html"
compare "*.sql"
compare "README*"
compare "Doxy*"
compare "ChangeLog*"
echo
