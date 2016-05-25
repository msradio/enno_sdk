#!/bin/bash

rm -R build_enno
mkdir build_enno
cd build_enno
cmake ../
make
cp ../azure_build/libumqtt.a ./
cp ../azure_build/libaziotsharedutil.a ./


