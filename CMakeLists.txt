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
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5
    COMPONENTS
    DBus
    Gui
    Help
    Multimedia
    MultimediaWidgets
    Network
    OpenGL
    Positioning
    PrintSupport
    Qml
    Quick
    QuickWidgets
    Script
    Sql
    Svg
    Test
    UiTools
    WebChannel
    WebEngineCore
    WebEngineWidgets
    Widgets
    Xml
    XmlPatterns
    QUIET
    )
  
#PTZ191127 could be smoke is here with a better version....
#add_subdirectory(smokegen)
#add_subdirectory(smokeqt)
include(ExternalProject)
set(_src_d ${PROJECT_SOURCE_DIR}/smokegen)
ExternalProject_Add(ep_smokegenerator
  PREFIX ${PROJECT_BINARY_DIR}
  #GIT_REPOSITORY git://anongit.kde.org/smokegen.git
  #GIT_BRANCH clang clang_PTZ191127
  SOURCE_DIR ${_src_d}
  BUILD_BYPRODUCTS smokegen smoke.h
  )

set(_src_d ${PROJECT_SOURCE_DIR}/smokeqt)
ExternalProject_Add(ep_smokeqt
  PREFIX ${PROJECT_BINARY_DIR}
  #GIT_REPOSITORY git://anongit.kde.org/smokeqt.git
  #GIT_BRANCH clang Qt5v2_PTZ191127
  SOURCE_DIR ${_src_d}
  BUILD_BYPRODUCTS smokeqt qtcore_smoke.h  qthelp_smoke.h               qtnetwork_smoke.h      qtprintsupport_smoke.h  qtquickwidgets_smoke.h  qttest_smoke.h        qtwebenginecore_smoke.h     qtxml_smoke.h qtdbus_smoke.h  qtmultimedia_smoke.h         qtopengl_smoke.h       qtqml_smoke.h           qtscript_smoke.h        qtuitools_smoke.h     qtwebenginewidgets_smoke.h qtgui_smoke.h   qtmultimediawidgets_smoke.h  qtpositioning_smoke.h  qtquick_smoke.h         qtsql_smoke.h           qtwebchannel_smoke.h  qtwidgets_smoke.h
  DEPENDS           ep_smokegenerator
  )
#needs /usr/local/include/smoke
ExternalProject_Get_property(ep_smokeqt INSTALL_DIR)
message("build dir of ep_smokeqt = ${INSTALL_DIR}")
#then include dir is temporaly...
set(ep_smokeqt_INCLUDE_DIR  ${INSTALL_DIR}/include/smoke)
list(PREPEND SMOKE_QTCORE_INCLUDE_DIR ${INSTALL_DIR}/include/smoke)
list(APPEND SMOKE_QTCORE_INCLUDE_DIR /usr/include/smoke)

find_package(Smoke REQUIRED COMPONENTS QtCore)
find_package(Smoke
    COMPONENTS
    QtDBus
    QtGui
    QtHelp
    QtMultimedia
    QtMultimediaWidgets
    QtNetwork
    QtPositioning
    QtPrintSupport
    QtOpenGL
    QtQml
    QtQuick
    QtQuickWidgets
    QtScript
    QtSql
    QtSvg
    QtTest
    QtUiTools
    QtWebChannel
    QtWebEngineCore
    QtWebEngineWidgets
    QtWidgets
    QtXml
    QtXmlPatterns
    QUIET
)

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
