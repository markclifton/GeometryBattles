cmake_minimum_required(VERSION 2.8)

project(GeometryBattles)
add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/dependencies/ProjectSane/libProjectSane.so)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/ProjectSane/)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/ProjectSane/includes/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")

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
