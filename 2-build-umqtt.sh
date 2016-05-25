#!/bin/bash

rm -R build_umqtt
mkdir build_umqtt
cd build_umqtt
cmake -DcompileOption_C:STRING="-D__STDC_NO_ATOMICS__=1" -Drun_valgrind:BOOL=0 ../azure-umqtt-c/
make umqtt
mv azure-c-shared-utility/libaziotsharedutil.a ./


