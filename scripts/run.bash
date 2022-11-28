#!/bin/bash

BASEDIR=$(dirname $(realpath $0))
cd $BASEDIR/..

if [[ "$1" == "deb" ]]; then
    SOURCE_FILE=examples/code_1.72.2-1665614327_amd64.deb
    MIDDLE_FILE=examples/code_1.72.2-1665614327_amd64.pkg
    OUTPUT_FILE=examples/code_1.72.2-1665614327_amd64_2.deb
elif [[ "$1" == "big" ]]; then
    SOURCE_FILE=examples/bigdata.bin
    MIDDLE_FILE=examples/bigdata.pkg
    OUTPUT_FILE=examples/bigdata2.bin
elif [[ "$1" == "zip" ]]; then
    SOURCE_FILE=examples/zipfile.zip
    MIDDLE_FILE=examples/zipfile.pkg
    OUTPUT_FILE=examples/zipfile2.zip
else
    SOURCE_FILE=examples/text.txt
    MIDDLE_FILE=examples/text.pkg
    OUTPUT_FILE=examples/utext.txt
fi

echo
echo -e "\033[30;41m""Compressing""\033[0m"
echo
build/compress $SOURCE_FILE -o $MIDDLE_FILE -m 4
echo
echo -e "\033[30;43m""Unpacking""\033[0m"
echo
build/compress -x -o $OUTPUT_FILE $MIDDLE_FILE
echo 
echo -e "\033[30;42m""Checksums""\033[0m"
echo
echo "Source File: $(sha256sum $SOURCE_FILE)"
echo "Output File: $(sha256sum $OUTPUT_FILE)"
echo
echo -e "\033[30;44m""Size of files""\033[0m"
echo -e "\033[36;40m""source file: ""\033[0m" $(du -h $SOURCE_FILE)
echo -e "\033[36;40m""middle file: ""\033[0m" $(du -h $MIDDLE_FILE)
echo -e "\033[36;40m""output file: ""\033[0m" $(du -h $OUTPUT_FILE)
echo