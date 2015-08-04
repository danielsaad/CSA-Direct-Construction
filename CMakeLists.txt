CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project ("CSA Direct Construction" CXX)

set(CMAKE_VERBOSE_MAKEFILE on)

ADD_CUSTOM_TARGET(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Switch CMAKE_BUILD_TYPE to Debug")

ADD_CUSTOM_TARGET(release 
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Switch CMAKE_BUILD_TYPE to Release")

#adding compiler definitions
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11")
MESSAGE("Flags Debug = ${CMAKE_CXX_FLAGS_DEBUG}")
MESSAGE("Flags Release = ${CMAKE_CXX_FLAGS_RELEASE}")
MESSAGE("Flags = ${CMAKE_CXX_FLAGS}")

#adding include dirs
include_directories("${CMAKE_SOURCE_DIR}/include")
link_directories("${CMAKE_SOURCE_DIR}/lib")

#adding subdirs
add_subdirectory(src)