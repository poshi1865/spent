#! /bin/bash

mkdir ~/.expenses/ 2> /dev/null
make

if [ $? -eq 0 ];
then
    echo "Installed successfully"
else 
    echo "Installer failed"
fi
