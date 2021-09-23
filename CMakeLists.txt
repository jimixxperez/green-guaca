CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT( fsdl2 )

SET( CC "g++")
SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14 -Wall -Wextra -pedantic -g3 -ggdb3 -fdiagnostics-color=always" )
SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14 -g0 O2" )

SET( CMAKE_BUILD_TYPE "Debug" )
SET( SOURCE_FILES
	src/main.cpp
	src/game.cpp
    src/textureManager.cpp
    src/entityManager.cpp
)
FIND_PACKAGE( GLM REQUIRED PATHS /usr/local/Cellar/glm)
FIND_LIBRARY( SDL2_LIBRARY NAME SDL2 )

message ([STATUS] "SDL2_INCLUDE_DIR" ${SDL2_INCLUDE_DIRS})
message ([STATUS] "SDL2_LIBRARY" ${SDL2_LIBRARIES})
message ([STATUS] "GLM in ${GLM_INCLUDE_DIRS}")

INCLUDE_DIRECTORIES( include )
INCLUDE_DIRECTORIES( 
    /usr/local/Cellar/sdl2/2.0.16/include/SDL2
    /usr/local/Cellar/sdl2_image/2.0.5/include/SDL2 
    /usr/local/Cellar/glm/0.9.9.8/include
    )

ADD_EXECUTABLE( fsdl2
	${SOURCE_FILES}
)

TARGET_LINK_LIBRARIES( fsdl2 
"-L/usr/local/Cellar/sdl2/2.0.16/lib  -lSDL2" 
"-L/usr/local/Cellar/sdl2_image/2.0.5/lib -lSDL2_image"
)

INSTALL(TARGETS fsdl2
        RUNTIME DESTINATION .)