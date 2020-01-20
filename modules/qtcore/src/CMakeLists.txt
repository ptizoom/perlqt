#TODO:PTZ200119 this should be merged with perlqt5::qtcore

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PERL_INCLUDE_PATH}
    ${Qt5Core_PRIVATE_INCLUDE_DIRS}
    ${QT_INCLUDES}
    )

xsubpp(QtCore.xs ${CMAKE_CURRENT_BINARY_DIR}/QtCore.cpp)

# I thought it'd be cool to be able to build the bindings without any runtime
# debugging compiled in.  But that turned out to not really be a good idea, as
# that information is useful in a lot of situations.
add_definitions( -DPERLQTDEBUG )

set( CMAKE_CXX_FLAGS ${PERL_CXX_FLAGS} )

set(perlqtcore_LIBRARY_SRCS
    binding.cpp
    handlers.cpp
    marshall_types.cpp
    util.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/QtCore.cpp
    )

if(WIN32)
    set(libraryName PerlQtCore)
else()
    set(libraryName QtCore)
endif(WIN32)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/blib/arch/auto/${libraryName})

add_library(qtcore SHARED
  ${perlqtcore_LIBRARY_SRCS}
  )
target_link_libraries(qtcore
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
    ${PERL_LIBRARY}
    ${SMOKE_BASE_LIBRARY}
    ${SMOKE_QTCORE_LIBRARY}
    ${SMOKE_QTGUI_LIBRARY}
    ${SMOKE_QTNETWORK_LIBRARY}
    ${PERL_LIBS}
    )

set_target_properties(qtcore PROPERTIES
    OUTPUT_NAME ${libraryName}
    PREFIX "" #TODO:PTZ200118 ${CUSTOM_PERL_SITE_ARCH_DIR}/auto but gives ./../../blib/arch/auto/QtCore//usr/local/local/lib/x86_64-linux-gnu/perl/5.30.0/autoQtCore.so
    INSTALL_NAME_DIR ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/${libraryName}
    EXPORT PerlQtExport
)

perl_extutils_mkbootstrap(QtCore qtcore)
install(FILES QtCore.bs
  EXPORT PerlQtExport
  DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/${libraryName}/
  )
add_custom_target(
  qtcorebs ALL
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/QtCore.bs
    ${LIBRARY_OUTPUT_PATH}/${libraryName}.bs
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/QtCore.bs
  )

install(TARGETS qtcore
  EXPORT PerlQtExport
  DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/${libraryName}/
  )
if (0) #PTZ200120
install(FILES
  binding.h handlers.h listclass_macros.h
  marshall_basetypes.h marshall_complex.h
  marshall.h marshall_macros.h marshall_primitives.h marshall_types.h
  perlqt.h ppport.h
              QtCore.h smokehelp.h smokeperl.h
	      perlqtcore_util.h
  DESTINATION include/perlqt5/Qt4Core #PTZ200116 at least  QtCore.h  clashes with ol'one?
	)
install(FILES doxsubpp.pl DESTINATION share/perlqt5 )
endif (0)
