# Test 2/CMakeLists.txt

set(SOURCES
"${CMAKE_SOURCE_DIR}/Test2/main.cpp"
)

add_executable(test2 ${SOURCES})

target_include_directories(test2 PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)