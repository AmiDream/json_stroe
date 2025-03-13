# CMakeList.txt: json_stroe 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_TOOLCHAIN_FILE  "D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
  
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("json_stroe")

# 将源代码添加到此项目的可执行文件。
add_executable (json_stroe "json_stroe.cpp" "json_stroe.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET json_stroe PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
find_package(nlohmann_json CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

target_link_libraries(json_stroe PRIVATE  nlohmann_json::nlohmann_json)
target_link_libraries(json_stroe PRIVATE  libpqxx::pqxx)