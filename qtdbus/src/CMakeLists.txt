include_directories(
    ${CMAKE_SOURCE_DIR}/qtcore/src
    ${PERL_INCLUDE_PATH}
    ${QT_INCLUDES} )

# Run doxsubpp.pl to run xsubpp on QtDBus4.xs
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/QtDBus4.c
                   COMMAND ${PERL_EXECUTABLE} ARGS ${CMAKE_SOURCE_DIR}/qtcore/src/doxsubpp.pl ${PERL_EXECUTABLE} QtDBus4.xs ${CMAKE_CURRENT_BINARY_DIR}/QtDBus4.c
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/QtDBus4.xs
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
# Make sure we build QtDBus4.c as c++ code
set_source_files_properties( ${CMAKE_CURRENT_BINARY_DIR}/QtDBus4.c 
    PROPERTIES LANGUAGE CXX
)

set( CMAKE_CXX_FLAGS ${PERL_CXX_FLAGS} )

set(qtdbus4_LIBRARY_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/QtDBus4.c
    qtdbus4handlers.cpp
)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/blib/arch/auto/QtDBus4)
add_library(perl_qtdbus4 SHARED ${qtdbus4_LIBRARY_SRC})

#PTZ181013 got that now... hav I forgotten a scrub?
# CMakeFiles/perl_qtdbus4.dir/qtdbus4handlers.cpp.o : Dans la fonction « marshall_QDBusReplyQStringList(Marshall*) » :
# /usr/src/Qt4-0.99.0-0/qtdbus/src/qtdbus4handlers.cpp:109 : référence indéfinie vers « QDBusError::QDBusError(QDBusError const&) »
# /usr/src/Qt4-0.99.0-0/qtdbus/src/qtdbus4handlers.cpp:109:(.text+0x608): relocalisation tronquée pour concorder avec la taille : R_X86_64_PC32 vers le symbole indéfini QDBusError::QDBusError(QDBusError const&)
# CMakeFiles/perl_qtdbus4.dir/qtdbus4handlers.cpp.o : Dans la fonction « QDBusReply<QStringList>::isValid() const » :
# /usr/include/qt4/QtDBus/qdbusreply.h:114 : référence indéfinie vers « QDBusError::isValid() const »
# /usr/include/qt4/QtDBus/qdbusreply.h:114:(.text+0x96a): relocalisation tronquée pour concorder avec la taille : R_X86_64_PC32 vers le symbole indéfini QDBusError::isValid() const
# found it in /lib/libQtDBus.dll.a 
target_link_libraries(perl_qtdbus4
    ${SMOKE_QTDBUS_LIBRARY} #${QT_QTCORE_LIBRARY} ${QT_QTXML_LIBRARY} 
    perlqtcore4
    #/lib/qt4/plugins/script/cygqtscriptdbus.dll
    -lQtDBus
    )

set_target_properties(perl_qtdbus4 PROPERTIES OUTPUT_NAME "QtDBus4")
set_target_properties(perl_qtdbus4 PROPERTIES PREFIX "")

install(TARGETS perl_qtdbus4 DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/auto/QtDBus4/)
