#
# Copyright (C) 2015 Cybernetica
#
# Research/Commercial License Usage
# Licensees holding a valid Research License or Commercial License
# for the Software may use this file according to the written
# agreement between you and Cybernetica.
#
# GNU General Public License Usage
# Alternatively, this file may be used under the terms of the GNU
# General Public License version 3.0 as published by the Free Software
# Foundation and appearing in the file LICENSE.GPL included in the
# packaging of this file.  Please review the following information to
# ensure the GNU General Public License version 3.0 requirements will be
# met: http://www.gnu.org/copyleft/gpl-3.0.html.
#
# For further information, please contact us at sharemind@cyber.ee.
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(SharemindLibEmulatorProtocols CXX)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeIncludes/"
                      ${CMAKE_MODULE_PATH})

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

SET(SHAREMIND_LIBEMULATORPROTOCOLS_VERSION "0.1.0")

FIND_PACKAGE(SharemindLibRandom REQUIRED)
FIND_PACKAGE(SharemindLibmodapi REQUIRED)
FIND_PACKAGE(SharemindPdkHeaders REQUIRED)

MACRO(SetList name)
  SET("${name}" "")
  LIST(APPEND "${name}" ${ARGN})
ENDMACRO()

SetList(SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_LINK_LIBRARIES)
SetList(SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_INCLUDE_DIRS
    ${SharemindLibEmulatorProtocols_INCLUDE_DIRS}
    ${SharemindLibRandom_INCLUDE_DIRS}
    ${SharemindLibmodapi_INCLUDE_DIRS}
    ${SharemindPdkHeaders_INCLUDE_DIRS})
SetList(SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_DEFINITIONS
    ${SharemindLibEmulatorProtocols_DEFINITIONS}
    ${SharemindLibRandom_DEFINITIONS}
    ${SharemindLibmodapi_DEFINITIONS}
    ${SharemindPdkHeaders_DEFINITIONS})
LIST(REMOVE_DUPLICATES SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_LINK_LIBRARIES)
LIST(REMOVE_DUPLICATES SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_INCLUDE_DIRS)
LIST(REMOVE_DUPLICATES SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_DEFINITIONS)

SetList(SHAREMIND_LIBEMULATORPROTOCOLS_INSTALL_LINK_LIBRARIES
        ${SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_LINK_LIBRARIES})
SET(SHAREMIND_LIBEMULATORPROTOCOLS_INSTALL_INCLUDE_DIRS
    "${CMAKE_INSTALL_PREFIX}/include"
    ${SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_INCLUDE_DIRS})
SetList(SHAREMIND_LIBEMULATORPROTOCOLS_INSTALL_DEFINITIONS
        ${SHAREMIND_LIBEMULATORPROTOCOLS_EXTERNAL_DEFINITIONS})
LIST(REMOVE_DUPLICATES SHAREMIND_LIBEMULATORPROTOCOLS_INSTALL_INCLUDE_DIRS)

FILE(GLOB_RECURSE SHAREMIND_LIBEMULATORPROTOCOLS_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
ADD_CUSTOM_TARGET("include_SHAREMIND_LIBEMULATORPROTOCOLS_HEADERS_in_IDE"
                  SOURCES ${SHAREMIND_LIBEMULATORPROTOCOLS_HEADERS})

INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        DESTINATION "include/sharemind/libemulator_protocols")

FILE(GLOB_RECURSE SHAREMIND_LIBEMULATORPROTOCOLS_INFILES
     "${CMAKE_CURRENT_SOURCE_DIR}/*.in")
ADD_CUSTOM_TARGET("include_SHAREMIND_LIBEMULATORPROTOCOLS_INFILES_in_IDE"
                  SOURCES ${SHAREMIND_LIBEMULATORPROTOCOLS_INFILES})

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibEmulatorProtocolsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibEmulatorProtocolsConfig.cmake"
  @ONLY)
INSTALL(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibEmulatorProtocolsConfig.cmake"
  DESTINATION "lib/SharemindLibEmulatorProtocols")
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibEmulatorProtocolsConfigVersion.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibEmulatorProtocolsConfigVersion.cmake"
  @ONLY)
INSTALL(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibEmulatorProtocolsConfigVersion.cmake"
  DESTINATION "lib/SharemindLibEmulatorProtocols")
