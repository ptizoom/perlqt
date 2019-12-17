add_custom_target(qthelp4pm ALL ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/QtHelp.pm ${CMAKE_BINARY_DIR}/blib/lib/QtHelp.pm)
install(FILES QtHelp.pm DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/)
