cmake_minimum_required(VERSION 3.17)
project(Proyecto_1_Datos_2)
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)


#Json
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.7.3)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

#---

#gtkmm
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
#---
add_executable(Proyecto_1_Datos_2 main.cpp GUI/MainWindow.cpp GUI/MainWindow.h GUI/IDE/CodeEditor.cpp GUI/IDE/CodeEditor.h Interpreter/LineReader.cpp Interpreter/LineReader.h MemoryMgmt/MemoryManager.cpp MemoryMgmt/MemoryManager.h Utilities/ListMemory.cpp Utilities/ListMemory.h Interpreter/OutputManager.cpp Interpreter/OutputManager.h Interpreter/Interpreter.cpp Interpreter/Interpreter.h MemoryMgmt/MemoryLayout.cpp MemoryMgmt/MemoryLayout.h Utilities/Node.cpp Utilities/Node.h ServerSocket/Client/Client.cpp ServerSocket/Client/Client.h ServerSocket/Server/Server.cpp ServerSocket/Server/Server.h JsonManeger/JsonManger.cpp JsonManeger/JsonManger.h Utilities/ReferenceList.cpp Utilities/ReferenceList.h Utilities/Reference.cpp Utilities/Reference.h Utilities/SpecialTypes/StructType.cpp Utilities/SpecialTypes/StructType.h Utilities/SpecialTypes/ReferenceType.cpp Utilities/SpecialTypes/ReferenceType.h Utilities/SpecialTypes/Struct.cpp Utilities/SpecialTypes/Struct.h)

target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})
