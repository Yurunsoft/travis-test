cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

# Note: update this to your new project's name and version
project(ChineseUtil 
  VERSION 1.0
  LANGUAGES CXX
)

set(VENDOR_DEPENDENCIES_DIR ${CMAKE_BINARY_DIR}/_deps)

# ---- Include guards ----

if (DEFINED PHP_FFI)
  if (DEFINED PHP_CONFIG_DIR)
    set(PHP_CONFIG_DIR "${PHP_CONFIG_DIR}/")
  else ()
    set(PHP_CONFIG_DIR "")
  endif ()
  # 读取include目录
  execute_process(COMMAND ${PHP_CONFIG_DIR}php-config --include-dir
  OUTPUT_VARIABLE PHP_INCLUDE_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # 读取链接库
  execute_process(COMMAND ${PHP_CONFIG_DIR}php-config --libs
  OUTPUT_VARIABLE PHP_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # 读取链接参数
  execute_process(COMMAND ${PHP_CONFIG_DIR}php-config --ldflags
  OUTPUT_VARIABLE PHP_LDFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # 获取插件存放目录
  execute_process(COMMAND ${PHP_CONFIG_DIR}php-config --extension-dir
  #    RESULT_VARIABLE PHP_EXTDIR
  OUTPUT_VARIABLE PHP_EXTDIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # 添加宏
  add_definitions(
    -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1
    -DHAVE_CONFIG_H
    -DPHP_ATOM_INC
  )
  # 包含目录, 保持与php-config --includes的结果一致
  include_directories(
    BEFORE
    ${PHP_INCLUDE_DIR}
    ${PHP_INCLUDE_DIR}/Zend
    ${PHP_INCLUDE_DIR}/main
    ${PHP_INCLUDE_DIR}/TSRM
    ${PHP_INCLUDE_DIR}/ext
  )
endif ()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.3
)

CPMAddPackage(
  NAME nlohmann_json
  VERSION 3.9.0
  URL https://github.com/nlohmann/json/releases/download/v3.9.0/include.zip
  URL_HASH SHA256=5b9b819aed31626aefe2eace23498cafafc1691890556cd36d2a8002f6905009
)

find_package(nlohmann_json QUIET)

include_directories(
  BEFORE
  ${VENDOR_DEPENDENCIES_DIR}/nlohmann_json-src/include
)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files automatically.
# Keep that in mind when changing files, or explicitly mention them here.
FILE(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
FILE(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface target:
# add_library(ChineseUtil INTERFACE)  
# set_target_properties(ChineseUtil PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_17)

add_library(ChineseUtil SHARED ${headers} ${sources} ${vec_headers} ${vec_sources})

set_target_properties(ChineseUtil PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "chinese_util")

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(ChineseUtil PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

# Link dependencies (if required)
# target_link_libraries(Greeter PUBLIC cxxopts)
target_link_libraries(ChineseUtil)

target_include_directories(ChineseUtil
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed
# should match the project's regular header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  DEPENDENCIES ""
)
