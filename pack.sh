FILES="README.md makefile pack.sh convert.cpp cwsp_*.cpp src/* include/*
data/binarySource model/Dict"
if [ $# -eq 0 ]
then
    echo "Please input version numbers of cwsp to package."
    exit
elif [ $# -eq 1 ]
then
    VERSION="$@"
    echo "Version number:"$VERSION
    echo "tar -czvf cwsp"$VERSION" README.md makefile pack.sh convert.cpp cwsp_*.cpp src/* include/* data/* model/* scripts/*"
    tar -czvf cwsp${VERSION}.tar $FILES
else
    echo "Too much parameters, just input version number after script."
fi
