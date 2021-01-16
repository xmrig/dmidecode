cmake_minimum_required(VERSION 2.8.12)
project(dmidecode)

add_definitions(-D_FILE_OFFSET_BITS=64)

set(SOURCES_DMIDECODE
    config.h
    dmidecode.c
    dmidecode.h
    dmioem.c
    dmioem.h
    dmiopt.c
    dmiopt.h
    dmioutput.c
    dmioutput.h
    types.h
    util.c
    util.h
    version.h
    )

if (WIN32)
    list(APPEND SOURCES_DMIDECODE winsmbios.h winsmbios.c res/dmidecode.rc)
    set(EXTRA_LIBS ws2_32)
endif()

if (CMAKE_C_COMPILER_ID MATCHES GNU)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
endif()

add_executable(dmidecode ${SOURCES_DMIDECODE})
target_link_libraries(dmidecode ${EXTRA_LIBS})
