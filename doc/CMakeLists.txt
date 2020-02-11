# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.


find_package(Doxygen)
find_package(Latex)
find_package(Dot)

if(DOXYGEN_FOUND)

  ########################################################################
  # Create the doxygen configuration file
  ########################################################################
  file(TO_NATIVE_PATH ${CMAKE_SOURCE_DIR} top_srcdir)
  file(TO_NATIVE_PATH ${CMAKE_BINARY_DIR} top_builddir)
  file(TO_NATIVE_PATH ${CMAKE_SOURCE_DIR} abs_top_srcdir)
  file(TO_NATIVE_PATH ${CMAKE_BINARY_DIR} abs_top_builddir)

  set(HAVE_DOT ${DOXYGEN_DOT_FOUND})
  set(enable_html_docs YES)
  set(enable_latex_docs NO)
  set(enable_xml_docs YES)

  set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.cmake.in)
  set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  SET(STATIC_PAGES  ${CMAKE_CURRENT_SOURCE_DIR}/footer/perlqt5_footer.html ${CMAKE_CURRENT_SOURCE_DIR}/header/perlqt5_header.html)
  #SET(APIDOC_DIR    ${CMAKE_BINARY_DIR}/doc CACHE PATH "API documentation directory")

  set(DOXYGEN_GENERATE_LATEX NO
    #${enable_latex_docs}
    )
  set(DOXYGEN_GENERATE_XML NO
    #${enable_xml_docs}
    )

  set(built_dirs
    ${CMAKE_CURRENT_BINARY_DIR}/html
    #<DOXYGEN_GENERATE_XML?${CMAKE_CURRENT_BINARY_DIR}/xml>
    )

  IF (WIN32 AND NOT CYGWIN)
    SET(DOXYGEN_GENERATE_MAN NO)
    FIND_PROGRAM(HHC_PROGRAM 
      NAMES hhc.exe 
      PATHS "c:/Program Files/HTML Help Workshop"
      DOC "HTML Help Compiler program")
  ELSE (WIN32 AND NOT CYGWIN)
    SET(DOXYGEN_GENERATE_MAN YES)
    SET(HHC_PROGRAM)
  ENDIF (WIN32 AND NOT CYGWIN)
  
  SET(DOXYGEN_GENERATE_MAN NO)
  
  if(0)
    FILE(MAKE_DIRECTORY ${APIDOC_DIR}/html)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/oai.css ${APIDOC_DIR}/html/oai.css COPYONLY)
    FILE(GLOB header_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/header/*.htm*)
    FILE(GLOB footer_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/footer/*.htm*)
    FILE(GLOB images_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/images/*.png)
  endif(0)

  configure_file(${doxyfile_in} ${doxyfile} @ONLY)


  ########################################################################
  # Make and install doxygen docs
  ########################################################################

  add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
    COMMAND ${CMAKE_COMMAND} -E echo_append "Building DOXY API Documentation..."
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    COMMAND ${CMAKE_COMMAND} -E echo "Done."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    #VERBATIM
    )

  add_custom_target(doc
    ALL
    DEPENDS ${doxyfile} ${CMAKE_CURRENT_BINARY_DIR}/html/index.html 
    )
  
  install(
    DIRECTORY ${built_dirs}
    DESTINATION share/doc/perlqt5
    COMPONENT "docs"
    )
  install(FILES
    ${PROJECT_SOURCE_DIR}/

    DESTINATION share/doc/perlqt5
    COMPONENT "docs"
    )

  #DOXYGEN_DOT_EXECUTABLE

  if(0)  
    set(DOCS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/doc)
    add_custom_target(doxy-update
      COMMAND ${DOXYGEN_EXECUTABLE} -u
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      )
    ExternalProject_Add(ep_oai_docs
      SOURCE_DIR ${DOCS_SOURCE_DIR}
      COMMENT "OAI documents -- "
      CONFIGURE_COMMAND test -f config.status || ${DOCS_SOURCE_DIR}/configure --prefix=$(CMAKE_CURRENT_BINARY_DIR) --enable-maintainer-mode --enable-shared
      )
    ExternalProject_Add_Step(ep_oai_docs autoupdate
      DEPENDEES download
      COMMAND autoupdate --verbose
      WORKING_DIRECTORY ${DOCS_SOURCE_DIR}
      )
    ExternalProject_Add_Step(ep_oai_docs init
      DEPENDEES autoupdate
      COMMAND autoreconf --force --install --verbose --warnings=all --symlink
      COMMENT "OAI documents customised :: being autoreconfed"
      WORKING_DIRECTORY ${DOCS_SOURCE_DIR}
      BYPRODUCTS configure Makefile.in config.h.in
      )
  endif()


endif(DOXYGEN_FOUND)
