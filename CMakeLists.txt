cmake_minimum_required(VERSION 3.22)
project(VLN LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED)
find_package(Lua REQUIRED)
find_package(Python3 COMPONENTS Development REQUIRED)

# nlohmann/json (header-only)
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# minizip-ng สำหรับ export zip (cross-platform)
FetchContent_Declare(minizip URL https://github.com/zlib-ng/minizip-ng/archive/refs/tags/4.0.7.tar.gz)
FetchContent_MakeAvailable(minizip)

add_subdirectory(thirdparty/rlImGui)

file(GLOB_RECURSE LIVE2D_SOURCES "thirdparty/live2d/Framework/src/*.cpp")

add_executable(VLN 
    src/main.cpp
    src/core/Engine.cpp
    src/scripting/LuaManager.cpp
    src/python/PythonBridge.cpp
    src/editor/TimelineEditor.cpp
    src/live2d/Live2DManager.cpp
    src/audio/AudioManager.cpp      # ใหม่
    src/save/SaveLoadManager.cpp    # ใหม่
    src/gui/SetupWizard.cpp         # ใหม่
    src/gui/DebugMenu.cpp           # ใหม่
    ${LIVE2D_SOURCES}
)

target_link_libraries(VLN PRIVATE raylib ${LUA_LIBRARIES} Python3::Python nlohmann_json::nlohmann_json minizip)
target_include_directories(VLN PRIVATE src thirdparty/rlImGui)

# Packaging สำหรับ release
set(CPACK_PACKAGE_NAME "Visual Live Novel")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "VLN - Visual Novel Engine")
set(CPACK_PACKAGE_VENDOR "Neofilisoft")
include(CPack)   

install(TARGETS VLN DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION assets)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/plugins/ DESTINATION plugins)

# สำหรับ Windows installer (Inno Setup หรือ NSIS)
if(WIN32)
    install(TARGETS VLN DESTINATION .)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION assets)
endif()