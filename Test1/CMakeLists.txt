# Test 1/CMakeLists.txt

set(SOURCES
"${CMAKE_SOURCE_DIR}/Test1/main.cpp"
)

add_executable(test1 ${SOURCES})

target_include_directories(test1 PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)