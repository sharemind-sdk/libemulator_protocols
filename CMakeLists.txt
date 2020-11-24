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

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(SharemindLibEmulatorProtocols VERSION 0.2.0 LANGUAGES CXX)

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers 1.6 REQUIRED)


FIND_PACKAGE(SharemindPdkHeaders 0.5.0 REQUIRED)


# LibEmulatorProtocols:
FILE(GLOB_RECURSE SharemindLibEmulatorProtocols_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
SharemindAddInterfaceLibrary(LibEmulatorProtocols
    EXPOSE_FILES ${SharemindLibEmulatorProtocols_HEADERS})
TARGET_INCLUDE_DIRECTORIES(LibEmulatorProtocols
    INTERFACE
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> # TODO
        $<INSTALL_INTERFACE:include>
    )
TARGET_LINK_LIBRARIES(LibEmulatorProtocols INTERFACE Sharemind::PdkHeaders)
INSTALL(FILES ${SharemindLibEmulatorProtocols_HEADERS}
        DESTINATION "include/sharemind/libemulator_protocols"
        COMPONENT "dev")
SharemindCreateCMakeFindFilesForTarget(LibEmulatorProtocols
    DEPENDENCIES
        "SharemindPdkHeaders 0.5.0"
)


# Packaging:
SharemindSetupPackaging()
SharemindAddComponentPackage("dev"
    NAME "libsharemind-emulator-protocols-dev"
    DESCRIPTION "Sharemind Emulator protocols development headers"
    DEB_SECTION "libdevel"
    DEB_DEPENDS
        "libsharemind-pdkheaders-dev (>= 0.5.0)"
        "libstdc++-dev"
)
SharemindPackagingFinalize()
