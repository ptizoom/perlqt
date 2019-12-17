add_custom_target(qtuitools4pm ALL ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/QtUiTools.pm ${CMAKE_BINARY_DIR}/blib/lib/QtUiTools.pm)
install(FILES QtUiTools.pm DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/)
