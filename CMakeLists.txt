# minimum require
cmake_minimum_required(VERSION 3.11.0)

# global solution
project(MyImplot VERSION 0.1.0)

# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
#set(CMAKE_DEBUG_POSTFIX "_d")    
#set(CMAKE_RELEASE_POSTFIX "_r") 

set(PROJECT_DIR ${PROJECT_SOURCE_DIR})
message("PROJECT_DIR: ${PROJECT_DIR}")

set(APP_DIR ${PROJECT_SOURCE_DIR}/implot_demo)


###############################################################################
# 3RD PARTY LIBS
###############################################################################

# FETCH CONTENT LIBS
include(FetchContent) 
# set(FETCHCONTENT_FULLY_DISCONNECTED ON)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw) 
FetchContent_MakeAvailable(glfw)

# GLAD
add_subdirectory(${APP_DIR}/3rdparty/glad)

# NFD
add_subdirectory(${APP_DIR}/3rdparty/nativefiledialog-extended)

include_directories(${APP_DIR}/3rdparty/)





###############################################################################
# IMGUI
###############################################################################
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/imgui)
message("IMGUI_DIR: ${IMGUI_DIR}")

#file(GLOB IMGUI_SRC ${IMGUI_DIR}/*.cpp)
#file(GLOB IMGUI_HEAD ${IMGUI_DIR}/*.h)

set(IMGUI_HEAD
    ${IMGUI_DIR}/imconfig.h
    ${IMGUI_DIR}/imgui_internal.h
    ${IMGUI_DIR}/imgui.h
    ${IMGUI_DIR}/imstb_rectpack.h
    ${IMGUI_DIR}/imstb_textedit.h
    ${IMGUI_DIR}/imstb_truetype.h    
    ${IMGUI_DIR}/backends/imgui_impl_glfw.h
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.h
    ${IMGUI_DIR}/backends/imgui_impl_opengl3_loader.h
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.h
)

set(IMGUI_SRC
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)


find_package(OpenGL REQUIRED)

# imgui library: imgui is build by default, but you can
# provide your own version by setting QTIMGUI_BUILD_IMGUI to OFF
add_library(imgui STATIC ${IMGUI_SRC} ${IMGUI_HEAD} )
#target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_link_libraries(imgui PUBLIC glfw glad OpenGL::GL imm32)

include_directories(${IMGUI_DIR} ${IMGUI_DIR}/examples ${IMGUI_DIR}/examples/libs/gl3w ${IMGUI_DIR}/backends ${IMGUI_DIR}/misc/cpp)


###############################################################################
# IMPLOT
###############################################################################
set(IMPLOT_DIR ${PROJECT_SOURCE_DIR}/implot)
message("IMPLOT_DIR: ${IMPLOT_DIR}")

set(IMPLOT_HEADERS ${IMPLOT_DIR}/implot.h ${IMPLOT_DIR}/implot_internal.h)
set(IMPLOT_SRC     ${IMPLOT_DIR}/implot.cpp ${IMPLOT_DIR}/implot_items.cpp ${IMPLOT_DIR}/implot_demo.cpp) 


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../implot/backends")
list(APPEND IMPLOT_HEADERS ${IMPLOT_DIR}/backends/implot_backend.h ${IMPLOT_DIR}/backends/implot_impl_opengl3.h)
list(APPEND IMPLOT_SRC ${IMPLOT_DIR}/backends/implot_backend.h ${IMPLOT_DIR}/backends/implot_impl_opengl3.cpp)
endif()

add_library(implot ${IMPLOT_HEADERS} ${IMPLOT_SRC})
target_link_libraries(implot PUBLIC imgui)
target_compile_definitions(implot PUBLIC IMPLOT_DEBUG IMPLOT_DLL_EXPORT IMPLOT_BACKEND_ENABLE_OPENGL3 IMGUI_IMPL_OPENGL_LOADER_GLAD)

include_directories(${IMPLOT_DIR}/)


###############################################################################
# APP FRAMEWORK
###############################################################################

add_library(app 
  ${APP_DIR}/common/App.h
  ${APP_DIR}/common/App.cpp
  ${APP_DIR}/common/Shader.h
  ${APP_DIR}/common/Native.h
  ${APP_DIR}/common/Native.cpp
  ${APP_DIR}/common/Image.h
  ${APP_DIR}/common/Fonts/Fonts.h
  ${APP_DIR}/common/Fonts/FontAwesome5.cpp
  ${APP_DIR}/common/Fonts/RobotoRegular.cpp
  ${APP_DIR}/common/Fonts/RobotoBold.cpp
  ${APP_DIR}/common/Fonts/RobotoItalic.cpp
  ${APP_DIR}/common/Fonts/RobotoMonoRegular.cpp
  ${APP_DIR}/common/Fonts/RobotoMonoBold.cpp
  ${APP_DIR}/common/Fonts/RobotoMonoItalic.cpp
)
target_include_directories(app PUBLIC ${APP_DIR}/common ${APP_DIR}/3rdparty/glad/include)

target_link_libraries(app implot nfd)
target_compile_features(app PRIVATE cxx_std_17)


###############################################################################
# DEMO APPS
###############################################################################
set(IMPLOT_DEMO_DIR ${PROJECT_SOURCE_DIR}/implot_demo)

# main ImPlot demo
add_executable(demo "${IMPLOT_DEMO_DIR}/demos/demo.cpp")
target_link_libraries(demo app)


# goto subs
#add_subdirectory(imgui)
#add_subdirectory(implot)