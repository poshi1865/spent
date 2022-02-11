#! /bin/bash

mkdir ~/.expenses/ 2> /dev/null
make
cp ./bin/spent ~/bin/spent

if [ $? -eq 0 ];
then
    echo "Installed successfully"
else 
    echo "Installer failed"
fi
