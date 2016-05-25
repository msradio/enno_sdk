#!/bin/bash

rm -R azure-umqtt-c
git clone https://github.com/Azure/azure-umqtt-c.git
cd azure-umqtt-c
git clone https://github.com/Azure/azure-c-shared-utility.git
cd ../

