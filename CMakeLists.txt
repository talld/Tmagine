cmake_minimum_required(VERSION 3.16)
project(Tmagine)

# LUA ##########################################################################
FIND_PACKAGE(Lua 5.3 REQUIRED)
set( LIBS_INCLUDE_DIRS ${INCLUDE_DIRS} ${LUA_INCLUDE_DIR} )
set( LIBRARIES         ${LIBRARIES}    ${LUA_LIBRARIES}   )

add_subdirectory(Libs)
################################################################################
### gUse                                                                     ###
################################################################################
set( LIBRARIES ${LIBRARIES} gUse )
set(CMAKE_C_STANDARD 99)
add_library(termbox Code/Termbox2/termbox.c)

set( LIBRARIES ${LIBRARIES} termbox )
set( LIBS_INCLUDE_DIRS ${LIBS_INCLUDE_DIRS} Code/Termbox2 )
################################################################################
### GAME                                                                     ###
################################################################################
set(CMAKE_CXX_STANDARD 17)

set(GAME_SRC ${GAME_SRC}
        main.cpp
        Code/FlagKeeper/FlagKeeper.cpp
        Code/LineReader/LineReader.cpp
        Code/DialogueSorter/Dialogue.cpp
	)

set(GAME_PCH ${GAME_PCH}
        Tmagine.pch
        )


set(GAME_INC ${GAME_INC}
        Code/FlagKeeper
        Code/LineReader
        Code/DialogueSorter
        )

add_executable(Tmagine ${GAME_SRC} ${LIBS_SRC})
target_precompile_headers(Tmagine PUBLIC ${GAME_PCH})
target_include_directories(Tmagine PUBLIC ${GAME_INC} ${LIBS_INCLUDE_DIRS})
target_link_libraries(Tmagine ${LIBRARIES})
