BINARYDIR := Debug

#Toolchain
CC := gcc
CXX := g++
LD := $(CXX)
AR := ar
OBJCOPY := objcopy

#Additional flags
PREPROCESSOR_MACROS := 
INCLUDE_DIRS := /opt/enno_sdk/azure-umqtt-c/inc /opt/enno_sdk/azure-umqtt-c/azure-c-shared-utility/inc /opt/enno_sdk/enno_api /opt/enno_sdk
LIBRARY_DIRS := 
LIBRARY_NAMES := ssl crypto
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -ggdb -ffunction-sections -O0 -std=gnu99
CXXFLAGS := -ggdb -ffunction-sections -O0 -std=gnu99
ASFLAGS := 
LDFLAGS := 
COMMONFLAGS := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
IS_LINUX_PROJECT := 1
