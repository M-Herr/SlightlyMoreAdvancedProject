cmake_minimum_required(VERSION 3.0)

project(
    ExampleProject
    VERSION 1.0
    LANGUAGES CXX)


find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

set(PROJECT_INCLUDE_DIR
${CMAKE_CURRENT_SOURCE_DIR}/include)

set(PROJECT_SOURCE_DIR 
${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PROJECT_HEADER
${PROJECT_INCLUDE_DIR}/Core/Application.hpp
${PROJECT_INCLUDE_DIR}/Core/CommandLineArgs.hpp
${PROJECT_INCLUDE_DIR}/Core/Logging.hpp
${PROJECT_INCLUDE_DIR}/Core/SignalHandling.hpp
${PROJECT_INCLUDE_DIR}/Core/Layer.hpp
${PROJECT_INCLUDE_DIR}/Core/LayerStack.hpp
${PROJECT_INCLUDE_DIR}/Util/UUID.hpp
${PROJECT_INCLUDE_DIR}/UI/MainWindow.hpp
${PROJECT_INCLUDE_DIR}/UI/Window.hpp
${PROJECT_INCLUDE_DIR}/UI/UIComponent.hpp
${PROJECT_INCLUDE_DIR}/UI/Button.hpp
)

set(PROJECT_SOURCE 
${PROJECT_SOURCE_DIR}/Core/EntryPoint.cpp
${PROJECT_SOURCE_DIR}/Core/Application.cpp
${PROJECT_SOURCE_DIR}/Core/CommandLineArgs.cpp
${PROJECT_SOURCE_DIR}/Core/SignalHandling.cpp
${PROJECT_SOURCE_DIR}/Core/Layer.cpp
${PROJECT_SOURCE_DIR}/Core/LayerStack.cpp
${PROJECT_SOURCE_DIR}/Util/UUID.cpp
${PROJECT_SOURCE_DIR}/UI/MainWindow.cpp
${PROJECT_SOURCE_DIR}/UI/Window.cpp
${PROJECT_SOURCE_DIR}/UI/Button.cpp
)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines -O2")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")


add_executable(ExampleProject ${PROJECT_SOURCE} ${PROJECT_HEADER})
set_property(TARGET ExampleProject PROPERTY CXX_STANDARD 23)

target_include_directories(ExampleProject 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(ExampleProject PRIVATE GTest::gtest_main spdlog::spdlog glfw OpenGL::GL imgui::imgui glad::glad)

#set_target_properties(ExampleProject PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/example_project.hh)

install(TARGETS ExampleProject DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/lib")