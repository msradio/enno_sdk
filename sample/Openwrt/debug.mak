BINARYDIR := Debug

#Toolchain
CC := /opt/qstak/qsdk/staging_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-uclibc-gcc
CXX := /opt/qstak/qsdk/staging_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-uclibc-g++
LD := $(CXX) 
AR := /opt/qstak/qsdk/staging_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-uclibc-ar
OBJCOPY := /opt/qstak/qsdk/staging_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-uclibc-objcopy

#Additional flags
PREPROCESSOR_MACROS := 
INCLUDE_DIRS := /opt/enno_sdk/azure-umqtt-c/inc /opt/enno_sdk/azure-umqtt-c/azure-c-shared-utility/inc /opt/enno_sdk/enno_api /opt/enno_sdk /opt/qstak/qsdk/staging_dir/target-mips_34kc_uClibc-0.9.33.2/usr/include
LIBRARY_DIRS := /opt/qstak/qsdk/staging_dir/target-mips_34kc_uClibc-0.9.33.2/usr/lib
LIBRARY_NAMES := alljoyn alljoyn_c alljoyn_about alljoyn_services_common crypto
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -g -Wall -ffunction-sections -O0 -std=gnu99 -DNO_SSL -DQCC_OS_GROUP_POSIX
CXXFLAGS := -g -Wall -ffunction-sections -O0 -std=gnu99 -DNO_SSL -DQCC_OS_GROUP_POSIX
ASFLAGS := 
LDFLAGS := 
COMMONFLAGS := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

