cmake_minimum_required(VERSION 3.22)
project(Tmagine)

set(CMAKE_CXX_STANDARD 17)

# LUA ##########################################################################
FIND_PACKAGE(Lua 5.4 REQUIRED)
set( LIBS_INCLUDE_DIRS ${INCLUDE_DIRS} ${LUA_INCLUDE_DIR} )
set( LIBRARIES         ${LIBRARIES}    ${LUA_LIBRARIES}   )

################################################################################
### gUse                                                                     ###
################################################################################

# gLog #########################################################################
set(GLOG_ROOT gUse/gLog)
set(GLOG_INCLUDE_DIR ${GLOG_ROOT}/Inc)
set(GLOG_SRC
        ${GLOG_ROOT}/Src/gLog.c
    )

set(GUSE_INCLUDE_DIR ${GUSE_INCLUDE_DIR} ${GLOG_INCLUDE_DIR})
set(GUSE_SRC         ${GUSE_SRC}         ${GLOG_SRC})

# gStr #########################################################################
set(GSTR_ROOT gUse/gStr)
set(GSTR_INCLUDE_DIR ${GSTR_ROOT}/Inc)
set(GSTR_SRC
        ${GSTR_ROOT}/Src/GString.cpp
   )

set(GUSE_INCLUDE_DIR ${GUSE_INCLUDE_DIR} ${GSTR_INCLUDE_DIR})
set(GUSE_SRC         ${GUSE_SRC}         ${GSTR_SRC})

################################################################################
set(LIBS_INCLUDE_DIRS ${LIBS_INCLUDE_DIRS} ${GUSE_INCLUDE_DIR})
set(LIBS_SRC ${LIBS_SRC} ${GUSE_SRC})

set(GAME_SRC ${GAME_SRC}
        main.cpp
        Code/FlagKeeper/FlagKeeper.cpp
        Code/LineReader/LineReader.cpp
        )

set(GAME_PCH ${GAME_PCH}
        Tmagine.pch
        )


set(GAME_INC ${GAME_INC}
        Code/FlagKeeper
        Code/LineReader
        )

add_executable(Tmagine ${GAME_SRC} ${LIBS_SRC})
target_precompile_headers(Tmagine PUBLIC ${GAME_PCH})
target_include_directories(Tmagine PUBLIC ${GAME_INC} ${LIBS_INCLUDE_DIRS})
target_link_libraries(Tmagine ${LIBRARIES})
