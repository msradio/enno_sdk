BINARYDIR := Debug

#Toolchain
CC := /opt/env/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-gcc
CXX := /opt/env/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-g++
LD := $(CXX)
AR := /opt/env/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-ar
OBJCOPY := /opt/env/arm-hisiv200-linux/bin/arm-hisiv200-linux-gnueabi-objcopy

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
