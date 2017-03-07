#!/bin/sh

function echoc() {
	echo -e "\e[0;91m$1\e[0m"
}

function useage() {
	echoc "Useage:"
	echoc "\t./mktag TAG_NAME"
	exit 1
}

if [ $# -ne 1 ]; then
	echo $#
        useage
fi


TAG_NAME=$1
export TAG_NAME

echoc "tag: $TAG_NAME"

./repo forall -c 'echo $REPO_PATH;echo $TAG_NAME;git tag $TAG_NAME;git push $REPO_REMOTE $TAG_NAME'
