add_custom_target(qtguipm ALL ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/QtGui.pm ${CMAKE_BINARY_DIR}/blib/lib/QtGui.pm)
install(FILES QtGui.pm DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/)
