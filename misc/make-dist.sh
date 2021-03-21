#!/bin/sh

if [ "$1" = "" ] || [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo;
    echo "Usage:" $0 "git_release_tag" ;
    echo;
    exit 1;
fi


# run from top git directory
#
git archive --worktree-attributes --format=tar.gz --prefix=$1/ \
    --output $1.tar.gz $1

# git archive --worktree-attributes --format=zip    --prefix=$1/ \
#     --output $1.zip    $1
