cmake_minimum_required(VERSION 2.8)
project(GeometryBattles)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    game/*.h
    game/*.cpp
    game/**/*.h
    game/**/*.cpp
    game/**/**/*.h
    game/**/**/*.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

IF(APPLE)
    # Header Includes
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/projectsane/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/glad/)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/glm/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/glfw/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/irrKlang/include)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/mac/freeimage/include)

    # Package Included Libraries
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/mac/projectsane/lib/libProjectSane.a)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/mac/glfw/lib/libglfw.3.3.dylib)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/mac/irrKlang/lib/libirrklang.dylib)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/mac/freeimage/lib/libfreeimage.a)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/dependencies/mac/irrKlang/lib/ikpMP3.dylib"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

ELSE()
    # Package Included Libraries
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/ProjectSane/lib/libProjectSane.a)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/irrKlang/lib/libIrrKlang.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/glfw3/lib/libglfw3.a)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/freeimage/lib/libfreeimage.a)

    # System Available Libraries
    target_link_libraries(${PROJECT_NAME} GLU)
    target_link_libraries(${PROJECT_NAME} GL)
    target_link_libraries(${PROJECT_NAME} X11)
    target_link_libraries(${PROJECT_NAME} Xrandr)
    target_link_libraries(${PROJECT_NAME} Xxf86vm)
    target_link_libraries(${PROJECT_NAME} Xinerama)
    target_link_libraries(${PROJECT_NAME} Xcursor)
    target_link_libraries(${PROJECT_NAME} rt)
    target_link_libraries(${PROJECT_NAME} m)
    target_link_libraries(${PROJECT_NAME} pthread)
    target_link_libraries(${PROJECT_NAME} dl)

    # Header Includes
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/glm/)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/glad/)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/glfw3/includes)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/irrKlang/includes)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/freeimage/includes)
    include_directories(${CMAKE_SOURCE_DIR}/dependencies/linux/ProjectSane/includes)
ENDIF()

# Post Build Steps

## Create Resource Dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")

## Copy Images
file(GLOB RESOURCES_IMAGES resources/images/* )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/images")
foreach( file_i ${RESOURCES_IMAGES})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_if_different ${file_i} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/images/"
        )
endforeach()

## Copy Models
file(GLOB RESOURCES_MODELS resources/models/* )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/models")
foreach( file_i ${RESOURCES_MODELS})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_if_different ${file_i} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/models/"
        )
endforeach()

## Copy Shaders
file(GLOB RESOURCES_SHADERS resources/shaders/* )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/shaders")
foreach( file_i ${RESOURCES_SHADERS})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_if_different ${file_i} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/shaders/"
        )
endforeach()

## Copy Sounds
file(GLOB RESOURCES_SOUNDS resources/sounds/* )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/sounds")
foreach( file_i ${RESOURCES_SOUNDS})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_if_different ${file_i} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/sounds/"
        )
endforeach()
