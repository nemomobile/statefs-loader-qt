PROJECT(statefs-loader-qt)
cmake_minimum_required(VERSION 2.8)

IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
  SET(LIB_SUFFIX "")
ELSE(CMAKE_SIZEOF_VOID_P EQUAL 4)
  SET(LIB_SUFFIX 64)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

set(DST_LIB lib${LIB_SUFFIX})
set(prefix ${CMAKE_INSTALL_PREFIX})


if(${USEQT} STREQUAL "4")

find_package(Qt4 4.7.0 REQUIRED)
include(${QT_USE_FILE})
add_definitions(-DQT_SHARED)
include_directories(
  ${QT_INCLUDE_DIR}
)

elseif(${USEQT} STREQUAL "5")

find_package(Qt5Core REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})
add_definitions(${Qt5Core_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

endif(${USEQT} STREQUAL "4")


set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -Wall -O2 -feliminate-unused-debug-types -std=c++0x"
  )

#-Wno-psabi is to remove next g++ warning/note:
#the mangling of 'va_list' has changed in GCC 4.4
set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -Wno-psabi"
)


find_package(PkgConfig REQUIRED)

pkg_check_modules(COR cor REQUIRED)
pkg_check_modules(STATEFS statefs>=0.3.0 REQUIRED)

INCLUDE_DIRECTORIES(
  ${COR_INCLUDES}
  ${STATEFS_INCLUDES}
)

link_directories(
  ${COR_LIBRARY_DIRS}
  ${STATEFS_LIBRARY_DIRS}
)

add_subdirectory(src)
