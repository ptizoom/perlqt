install( FILES signals.pm slots.pm isa.pm debug.pm classinfo.pm DESTINATION ${CUSTOM_PERL_SITE_ARCH_DIR}/QtCore )
add_custom_target(qtcorepmlibmkdir ALL ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/blib/lib/QtCore)
add_custom_target(qtcorepmlibsubdir ALL ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}/blib/lib/QtCore)
