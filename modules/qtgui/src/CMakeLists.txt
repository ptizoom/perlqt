include_directories(
  #${CMAKE_SOURCE_DIR}/modules/qtcore #PTZ200210 to change... when "invokeslot.h" in commun
  ${CMAKE_SOURCE_DIR}/modules/qtcore/src
    ${PERL_INCLUDE_PATH}
    #${Qt5Core_PRIVATE_INCLUDE_DIRS}
    ${QT_INCLUDES} )

# Run doxsubpp.pl to run xsubpp on QtGui.xs
xsubpp(QtGui.xs ${CMAKE_CURRENT_BINARY_DIR}/QtGui.cpp)

set( CMAKE_CXX_FLAGS ${PERL_CXX_FLAGS} )

set(qtgui_LIBRARY_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/QtGui.cpp
    qtgui_handlers.cpp
)

if(WIN32)
    set(libraryName PerlQtGui)
else()
    set(libraryName QtGui)
endif(WIN32)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/blib/arch/auto/${libraryName})
add_library(perl_qtgui SHARED ${qtgui_LIBRARY_SRC})

target_link_libraries(perl_qtgui
  ${QT_QTGUI_LIBRARY}
  ${SMOKE_QTGUI_LIBRARY}
  qtcore
  )

set_target_properties(perl_qtgui PROPERTIES
  OUTPUT_NAME ${libraryName}
  PREFIX ""
  DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/${libraryName}/
  )

install(TARGETS perl_qtgui
  EXPORT PerlQtExport
  DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/${libraryName}/
  )


perl_extutils_mkbootstrap(QtGui perl_qtgui)
install(FILES QtGui.bs
  EXPORT PerlQtExport
  DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/${libraryName}/
  )
add_custom_target(qtguibs ALL
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/QtGui.bs
    ${LIBRARY_OUTPUT_PATH}/${libraryName}.bs
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/QtGui.bs
  )
