#!/bin/sh

if [ "$1" = "" ] || [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo;
    echo "Usage:" $0 "git_release_tag" ;
    echo;
    exit 1;
fi

# echo
# git fetch --all

# echo
# git show-ref --tags
#
# # turn the detached message off
# # git config --global advice.detachedHead false
# echo
# git checkout tags/$1
# git describe --tags --abbrev=0


# run from top git directory
#
git archive --format=tar.gz --prefix=$1/ --output $1.tar.gz $1

# git archive --format=zip    --prefix=$1/ --output $1.zip    $1
#
# echo
# ls -l $1.tar.gz $1.zip
#
# echo
# git checkout master
