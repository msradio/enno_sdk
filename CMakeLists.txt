PROJECT (enno_sample C)
SET(CMAKE_INSTALL_PREFIX, ${CMAKE_CURRENT_SOURCE_DIR}/install)
SET(CMAKE_BUILD_PREFIX, ${CMAKE_CURRENT_SOURCE_DIR}/build)

ADD_DEFINITIONS(-DDEBUD -D__STDC_VERSION__=199901L -std=gnu99 -Wall)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/azure-umqtt-c/inc ${CMAKE_CURRENT_SOURCE_DIR}/azure-umqtt-c/azure-c-shared-utility/inc ${CMAKE_CURRENT_SOURCE_DIR})
#these are the C source files
set(enno_c_files
./enno_api/enno_api.c
)
#these are the C headers
set(enno_h_files
./enno_api/enno_api.h
)
#this is the product (a library)
add_library(ennoapi ${enno_c_files})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/azure-umqtt-c/ ${CMAKE_CURRENT_SOURCE_DIR}/azure-umqtt-c/azure-c-shared-utility )
target_link_libraries(ennoapi crypto ssl aziotsharedutil umqtt)



ADD_EXECUTABLE(enno_sample sample/sample_src.c)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build build ./)
TARGET_LINK_LIBRARIES(enno_sample -lcrypto -lssl libaziotsharedutil.a libumqtt.a libennoapi.a)


