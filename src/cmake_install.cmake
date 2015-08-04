# Install script for directory: /home/daniel/Códigos/CSA-Direct-Construction/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/csa" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/csa")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/csa"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/daniel/Códigos/CSA-Direct-Construction/bin/csa")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/daniel/Códigos/CSA-Direct-Construction/bin" TYPE EXECUTABLE FILES "/home/daniel/Códigos/CSA-Direct-Construction/src/csa")
  if(EXISTS "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/csa" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/csa")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/csa")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/csa")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/misc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/misc")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/misc"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/daniel/Códigos/CSA-Direct-Construction/bin/misc")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/daniel/Códigos/CSA-Direct-Construction/bin" TYPE EXECUTABLE FILES "/home/daniel/Códigos/CSA-Direct-Construction/src/misc")
  if(EXISTS "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/misc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/misc")
    file(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/misc")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/daniel/Códigos/CSA-Direct-Construction/bin/misc")
    endif()
  endif()
endif()

