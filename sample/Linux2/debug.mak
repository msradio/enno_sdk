BINARYDIR := Debug

#Toolchain
CC := /opt/env/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc
CXX := /opt/env/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-g++
LD := $(CXX)
AR := /opt/env/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-ar
OBJCOPY := /opt/env/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-objcopy

#Additional flags
PREPROCESSOR_MACROS := 
INCLUDE_DIRS := /opt/enno_sdk/azure-umqtt-c/inc /opt/enno_sdk/azure-umqtt-c/azure-c-shared-utility/inc /opt/enno_sdk/enno_api /opt/enno_sdk
LIBRARY_DIRS := 
LIBRARY_NAMES := 
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -ggdb -ffunction-sections -O0 -std=gnu99 -DNO_SSL
CXXFLAGS := -ggdb -ffunction-sections -O0 -std=gnu99 -DNO_SSL
ASFLAGS := 
LDFLAGS := 
COMMONFLAGS := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
IS_LINUX_PROJECT := 1
