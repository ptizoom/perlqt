cmake_minimum_required(VERSION 2.8.11)

project(PerlQt)

if(MSVC)
    # Use all the cores
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif(MSVC)

set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --show-leak-kinds=definite --errors-for-leak-kinds=definite")
find_program(MEMORYCHECK_COMMAND NAMES valgrind)
include(CTest)

set(BUILD_TESTS OFF CACHE BOOL "Build tests")
set(ENABLE_GUI_TESTS OFF CACHE BOOL "Run GUI tests in the \"test\" target")
set(USE_BUILD_DIR_FOR_TESTS OFF CACHE BOOL "Use to toggle between using the build dir or the install dir for tests.")

find_package(Perl REQUIRED)
find_package(PerlLibs REQUIRED)

set(_qt_comps
  DBus  Help Multimedia MultimediaWidgets
  Network  OpenGL    Positioning    PrintSupport
  Qml    Quick    QuickWidgets
  Script    Sql    Svg    Test    UiTools    WebChannel    WebEngineCore
  WebEngineWidgets    Widgets    Xml    XmlPatterns
  )
set(_qt_comps_req 
  Core Gui
  )

find_package(Qt5 COMPONENTS ${_qt_comps_req} REQUIRED)
find_package(Qt5 COMPONENTS ${_qt_comps}     QUIET)

#PTZ200118 back compatibility with QT3,QT4 perlqt projects
foreach(_cmps ${_qt_comps_req} ${_qt_comps})
  string(TOUPPER ${_cmps} _u_cmps)
  set(QT_QT${_u_cmps}_LIBRARY ${Qt5${_cmps}_LIBRARIES})
endforeach()
  
#PTZ191127 could it be that smoke is here with a better version....
include(ExternalProject)
set(_src_d ${PROJECT_SOURCE_DIR}/smokegen)
ExternalProject_Add(ep_smokegenerator
  PREFIX ${PROJECT_BINARY_DIR}
  #GIT_REPOSITORY git://anongit.kde.org/smokegen.git
  #GIT_BRANCH clang clang_PTZ191127
  SOURCE_DIR ${_src_d}
  #INSTALL_COMMAND make install
  #STEP_TARGETS  install
  BUILD_BYPRODUCTS smokegen smoke.h
  )

set(_src_d ${PROJECT_SOURCE_DIR}/smokeqt)
ExternalProject_Add(ep_smokeqt
  PREFIX ${PROJECT_BINARY_DIR}
  #GIT_REPOSITORY git://anongit.kde.org/smokeqt.git
  #GIT_BRANCH clang Qt5v2_PTZ191127
  SOURCE_DIR ${_src_d}
  BUILD_BYPRODUCTS smokeqt qtcore_smoke.h  qthelp_smoke.h
    qtnetwork_smoke.h      qtprintsupport_smoke.h  qtquickwidgets_smoke.h
    qttest_smoke.h        qtwebenginecore_smoke.h     qtxml_smoke.h qtdbus_smoke.h
    qtmultimedia_smoke.h         qtopengl_smoke.h       qtqml_smoke.h
    qtscript_smoke.h        qtuitools_smoke.h     qtwebenginewidgets_smoke.h
    qtgui_smoke.h   qtmultimediawidgets_smoke.h  qtpositioning_smoke.h
    qtquick_smoke.h         qtsql_smoke.h
    qtwebchannel_smoke.h  qtwidgets_smoke.h
  DEPENDS ep_smokegenerator
  #INSTALL_COMMAND make install
  #STEP_TARGETS  install
  )
#needs /usr/local/include/smoke
ExternalProject_Get_property(ep_smokeqt INSTALL_DIR BINARY_DIR)
message("build dir of ep_smokeqt = ${INSTALL_DIR} , ${BINARY_DIR}")
#then include dir is temporaly...
set(ep_smokeqt_INCLUDE_DIR  ${INSTALL_DIR}/include/smoke)
list(PREPEND SMOKE_QTCORE_INCLUDE_DIR ${INSTALL_DIR}/include/smoke)
list(APPEND  SMOKE_QTCORE_INCLUDE_DIR /usr/include/smoke)

foreach(_cmps ${_qt_comps_req} ${_qt_comps})
  string(CONCAT _qt_cmps_i "Qt" ${_cmps})
  list(APPEND _smokeqt_cmps ${_qt_cmps_i})
endforeach()

#TODO:PTZ200118 find system wide smoke-qt may be at higher priority ?
#
#find_package(Smoke REQUIRED COMPONENTS QtCore)
find_package(Smoke COMPONENTS  ${_smokeqt_cmps} QUIET)

include_directories(
    ${SMOKE_INCLUDE_DIR}
    ${SMOKE_QTCORE_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${SMOKE_CMAKE_MODULE_DIR})
include(MacroOptionalFindPackage)
include(MacroOptionalAddBindings)
include(MacroLogFeature)
include(MacroProve)
find_package(PerlMore)
find_package(XSUBPP REQUIRED QUIET)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(BUILD_TESTS ON CACHE BOOL "Build tests" FORCE)
    enable_testing()

    include(CodeCoverage)
    setup_target_for_coverage(
        coverage
        ctest
        coverage
    )
else()
    if (BUILD_TESTS)
        enable_testing()
    endif()
endif()

string(LENGTH "${PERL_INSTALL_PREFIX}" PERL_INSTALL_PREFIX_LEN)
math(EXPR PERL_INSTALL_PREFIX_LEN "${PERL_INSTALL_PREFIX_LEN}+1")
string(LENGTH "${PERL_SITE_ARCH_DIR}" PERL_SITE_ARCH_DIR_LEN)
math(EXPR CUSTOM_PERL_SITE_ARCH_DIR_SUBSTRING_LEN "${PERL_SITE_ARCH_DIR_LEN}-${PERL_INSTALL_PREFIX_LEN}")
string(SUBSTRING ${PERL_SITE_ARCH_DIR} ${PERL_INSTALL_PREFIX_LEN} ${CUSTOM_PERL_SITE_ARCH_DIR_SUBSTRING_LEN} CUSTOM_PERL_SITE_ARCH_DIR)
file(TO_NATIVE_PATH "${CMAKE_INSTALL_PREFIX}/${CUSTOM_PERL_SITE_ARCH_DIR}" CUSTOM_PERL_SITE_ARCH_DIR)
set(CUSTOM_PERL_SITE_ARCH_DIR ${CUSTOM_PERL_SITE_ARCH_DIR} CACHE DIR "Custom installation directory for perl binary extension")

# the RPATH to be used when installing, but only if it's not a system directory
GET_FILENAME_COMPONENT(SMOKE_LIB_DIR ${SMOKE_BASE_LIBRARY} PATH)
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES ${SMOKE_LIB_DIR} isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:${SMOKE_LIB_DIR}")
ENDIF("${isSystemDir}" STREQUAL "-1")

GET_FILENAME_COMPONENT(PERL_LIB_DIR ${PERL_LIBRARY} PATH)
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES ${PERL_LIB_DIR} isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:${PERL_LIB_DIR}")
ENDIF("${isSystemDir}" STREQUAL "-1")

get_target_property(QtCore_location Qt5::Core LOCATION)
GET_FILENAME_COMPONENT(QtCore_lib_dir ${QtCore_location} PATH)
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES ${QtCore_lib_dir} isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:${QtCore_lib_dir}")
ENDIF("${isSystemDir}" STREQUAL "-1")

if (NOT LIB_INSTALL_DIR)
    set (LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})
endif (NOT LIB_INSTALL_DIR)

add_subdirectory(src)
add_subdirectory(modules)

macro_display_feature_log()

#install(EXPORT PerlQtExport DESTINATION ${CMAKE_INSTALL_PREFIX}/share/perlqt/cmake NAMESPACE PERLQT_)
add_subdirectory(cmake)

#https://stackoverflow.com/questions/9827208/run-a-shell-command-ctags-in-cmake-and-make
# Add a top-level "tags" target which includes all files in both
# the build and source versions of src/*.
set_source_files_properties(tags PROPERTIES GENERATED true)
add_custom_target(ctags
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q 
        ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    #COMMAND ln -sf ${CMAKE_CURRENT_BINARY_DIR}/tags ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# ...but only make it a dependency of the project if the ctags program
# is available, else it will fail to build on Windows.
find_program(CTAGS_PATH ctags)
if(CTAGS_PATH)
    message(STATUS "Found ctags: ${CTAGS_PATH}")
    #add_dependencies( tags)
endif(CTAGS_PATH)

set_source_files_properties(TAGS PROPERTIES GENERATED true)
add_custom_target(TAGS
    COMMAND find 
      ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
      -regex "\".*\\.[cChH]\(pp\)?\"" -print
      | etags -
    VERBATIM
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# ...but only make it a dependency of the project if the ctags program
# is available, else it will fail to build on Windows.
find_program(ETAGS_PATH etags)
if(ETAGS_PATH)
    message(STATUS "Found etags: ${ETAGS_PATH}")
endif(ETAGS_PATH)

add_subdirectory(doc)

