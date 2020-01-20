xsubpp(qtcore.xs ${CMAKE_CURRENT_BINARY_DIR}/qtcore.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PERL_INCLUDE_PATH}
    ${Qt5Core_PRIVATE_INCLUDE_DIRS}
)

add_definitions(${PERL_CXX_FLAGS})

if(WIN32)
    set(libraryName PerlQtCore)
else()
    set(libraryName QtCore)
endif(WIN32)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/blib/arch/auto/PerlQt5/${libraryName})

add_library(perlqt5core SHARED
    ${CMAKE_CURRENT_BINARY_DIR}/qtcore.cpp
    can.cpp
    invokeslot.cpp
    perlqtobject.cpp
    perlqtmetaobject.cpp
    qtcore_handlers.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/qtcore.bs
)

target_link_libraries(perlqt5core
    Qt5::Core
    ${PERL_LIBRARY}
    ${SMOKE_BASE_LIBRARY}
    ${SMOKE_QTCORE_LIBRARY}
    ${PERL_LIBS}
    smokeperl
)

set_target_properties(perlqt5core PROPERTIES
    OUTPUT_NAME ${libraryName}
    PREFIX ""
    INSTALL_NAME_DIR ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/PerlQt5/${libraryName}/
)

install(
    TARGETS perlqt5core
    EXPORT PerlQtExport
    DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/PerlQt5/${libraryName}/
)
#TODO:PTZ200116 I know, better use ExtUtils packages, but hey here .bs file might need TLC to redirect sub-package
# libraries (eg. smokegen.so etc..) to this  intermediary ${CMAKE_BINARY_DIR}/lib directory....
# tricky.
#
add_custom_target(
    perlqt5corepm ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/QtCore.pm ${CMAKE_BINARY_DIR}/blib/lib/PerlQt5/QtCore.pm
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/qtcore.bs ${LIBRARY_OUTPUT_PATH}/${libraryName}.bs
)

perl_extutils_mkbootstrap(qtcore perlqt5core)
install(FILES qtcore.bs
  OUTPUT_NAME ${libraryName}.bs
  EXPORT PerlQtExport
  DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/PerlQt5/${libraryName}/
  )


install(FILES QtCore.pm DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/PerlQt5)


  
add_subdirectory(tests)

#from QtCore4
include (FindPerlMore)

add_subdirectory(lib)
#PTZ191211 ::QtCore and ::Qt but really should be added to PerlQt5::
add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(t)
