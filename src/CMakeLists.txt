include_directories(
    ${PERL_INCLUDE_PATH}
)

add_definitions(${PERL_CXX_FLAGS})

add_library(smokeperl SHARED
    handlers.cpp
    marshall.cpp
    methodcall.cpp
    methodresolution.cpp
    smokebinding.cpp
    smokemanager.cpp
    smokeobject.cpp
    virtualmethodcall.cpp
    xsfunctions.cpp
)

target_compile_features(smokeperl PUBLIC
    cxx_auto_type
    cxx_deleted_functions
    cxx_nullptr
)

target_link_libraries(smokeperl
    ${PERL_LIBRARY}
    ${SMOKE_BASE_LIBRARY}
    ${PERL_LIBS}
)

install(
  TARGETS smokeperl
  EXPORT PerlQtExport
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  )

install(FILES
  smokebinding.h smokemanager.h
  smokeperl_export.h
  smokehelp.h smokeperl.h
  smokeobject.h
  handlers.h
  #listclass_macros.h
  #marshall_basetypes.h marshall_complex.h
  marshall.h
  methodcall.h virtualmethodcall.h
  #marshall_macros.h marshall_primitives.h marshall_types.h
  #perlqt.h ppport.h QtCore.h perlqtcore_util.h

  EXPORT PerlQtExport
  DESTINATION include/smokeperlqt5
  )

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
