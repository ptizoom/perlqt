include(FindQwt5)

include_directories( ${QT_INCLUDES} ${Qwt5_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

########### next target ###############

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/smokedata.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_1.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_2.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_3.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_4.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_5.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_6.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_7.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_8.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_9.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_10.cpp

    COMMAND ${SMOKE_GEN_BIN}
    ARGS -config "${CMAKE_CURRENT_BINARY_DIR}/../qtgui/config.xml" -smokeconfig "${CMAKE_CURRENT_SOURCE_DIR}/smokeconfig.xml"
         -I "${Qwt5_INCLUDE_DIR}" -- ${CMAKE_CURRENT_SOURCE_DIR}/qwt_includes.h
    DEPENDS ${SMOKE_GEN_BIN} "${CMAKE_CURRENT_SOURCE_DIR}/smokeconfig.xml"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

macro_add_file_dependencies( ${CMAKE_CURRENT_BINARY_DIR}/smokedata.cpp ${CMAKE_CURRENT_BINARY_DIR}/x_1.cpp )

set(smokeqwt_LIB_SRCS ${CMAKE_CURRENT_BINARY_DIR}/smokedata.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_1.cpp 
	${CMAKE_CURRENT_BINARY_DIR}/x_2.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_3.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_4.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_5.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_6.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_7.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_8.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_9.cpp
	${CMAKE_CURRENT_BINARY_DIR}/x_10.cpp)

IF(CMAKE_CXX_FLAGS MATCHES "-fvisibility")
    ADD_DEFINITIONS(-DGCC_VISIBILITY)
ENDIF(CMAKE_CXX_FLAGS MATCHES "-fvisibility")

if (CYGWIN)
  #PTZ181004
  # an ... extern "C" SMOKE_EXPORT void init_qwt_Smoke(); is not enough to links mokeqwt
  #CMakeFiles/perl_qwt.dir/Qwt.c.o : Dans la fonction « boot_Qwt » :
  #/home/ptizo/.local/share/.cpan/build/Qt4-0.99.0-0/qwt/src/Qwt.xs:90 : référence indéfinie vers « init_qwt_Smoke »
  #/home/ptizo/.local/share/.cpan/build/Qt4-0.99.0-0/qwt/src/Qwt.xs:90:(.text+0x61a): relocalisation tronquée pour concorder avec la taille : R_X86_64_PC32 vers le symbole indéfini init_qwt_Smoke
  #CMakeFiles/perl_qwt.dir/Qwt.c.o:Qwt.c:(.rdata$.refptr.qwt_Smoke[.refptr.qwt_Smoke]+0x0) : référence indéfinie vers « qwt_Smoke »
  add_library(smokeqwt STATIC ${smokeqwt_LIB_SRCS})
  #add_library(smokeqwt OBJECT ${smokeqwt_LIB_SRCS})
else (CYGWIN)
  add_library(smokeqwt SHARED ${smokeqwt_LIB_SRCS})
endif (CYGWIN)

target_link_libraries(smokeqwt smokeqtcore smokeqtgui ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Qwt5_Qt4_LIBRARY})

set_target_properties(smokeqwt PROPERTIES VERSION 3.0.0 SOVERSION 3 )

install(TARGETS smokeqwt LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    RUNTIME DESTINATION bin)

if (WIN32)
    # Get rid of the "lib" prefix on archives/DLLs in Windows.
    set_target_properties(smokeqwt
        PROPERTIES PREFIX "" IMPORT_PREFIX "")
endif (WIN32)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../qwt_smoke.h DESTINATION include/smoke)
