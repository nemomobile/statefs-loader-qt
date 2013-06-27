set(CMAKE_AUTOMOC TRUE)

if(${USEQT} STREQUAL "4")

add_library(loader-qt4
  SHARED wrapqt.cpp qtloader.cpp
)

target_link_libraries(loader-qt4
  ${QT_QTCORE_LIBRARY}
)

install(TARGETS loader-qt4 DESTINATION ${DST_LIB}/statefs)

elseif(${USEQT} STREQUAL "5")

add_library(loader-qt5
  SHARED wrapqt.cpp qtloader.cpp
)

target_link_libraries(loader-qt5
  ${Qt5Core_LIBRARIES}
)

install(TARGETS loader-qt5 DESTINATION ${DST_LIB}/statefs)

endif(${USEQT} STREQUAL "4")
