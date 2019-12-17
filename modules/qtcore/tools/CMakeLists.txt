include_directories( ${Qt5Core_INCLUDE_DIRS} )


#/usr/include/x86_64-linux-gnu/qt5/QtCore/qglobal.h:1187:4: error: #error "You must build your code with position independent code if Qt was built with -reduce-relocations. " "Compile your code with -fPIC (-fPIE is not enough)."
# 1187 | #  error "You must build your code with position independent code if Qt was built with -reduce-relocations. "\
#      |    ^~~~~
#PTZ191219 from function(get_smokegen_args RESULT_NAME moduleName)
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Og")
  #TODO:PTZ191125 if debug/maintainer mode
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()
## disable deprecation warnings
#if(CMAKE_COMPILER_IS_GNUCXX)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
#endif()
#
#PTZ191219 remove  -DQT_NO_DEBUG
list(APPEND QT_QTCORE_LIBRARY ${Qt5Core_LIBRARIES})

add_subdirectory( puic )

#PTZ191216 need `QDomDocument::QDomDocument()'

list(APPEND QT_QTXML_LIBRARY  Qt5::Xml)

add_subdirectory( prcc )
