add_custom_target(qtdbus4pm ALL ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/QtDBus.pm ${CMAKE_BINARY_DIR}/blib/lib/QtDBus.pm)
install(FILES QtDBus.pm DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/)
