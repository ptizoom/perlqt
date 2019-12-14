add_subdirectory( QtCore )
add_custom_target(perlqtcore4pm ALL ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/QtCore.pm ${CMAKE_BINARY_DIR}/blib/lib/QtCore.pm)
install( FILES QtCore.pm DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR} )
