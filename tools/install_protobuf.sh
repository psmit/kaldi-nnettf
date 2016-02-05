#!/bin/bash

# install the protobuf library 


if [ ! -f protobuf-cpp-3.0.0-beta-2.tar.gz ]; then
  wget -T 10 -t 3 https://github.com/google/protobuf/releases/download/v3.0.0-beta-2/protobuf-cpp-3.0.0-beta-2.tar.gz || exit 1;
fi

tar -xvzf protobuf-cpp-3.0.0-beta-2.tar.gz  || exit 1;

mv protobuf-3.0.0-beta-2 protobuf
cd protobuf 

./configure --prefix=`pwd`/install || exit 1

make -j 4 || exit 1
make install || exit 1

