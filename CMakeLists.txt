# Specifies the minimum version of CMake required.
cmake_minimum_required(VERSION 3.31)

# Defines the project name and the language used.
project(my_c_app C)

# Specifies the C standard to use.
set(CMAKE_C_STANDARD 11)

# Creates a static library from your vector source file.
# Static libraries are compiled into your executable at build time.
add_library(my_c_lib STATIC
        src/vector.c
        src/linked_list.c
        src/mempool.c
)

# Now that the 'my_c_lib' target exists, we can add its properties.
# Adds the include directory so the compiler can find 'vector.h' when building the library.
# We use PUBLIC so that any targets which link to this library (like my_c_app)
# will also get this include path automatically.
target_include_directories(my_c_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Creates the executable for your main application from main.c.
add_executable(my_c_app src/main.c)

# Links the 'my_c_app' executable with the 'my_c_lib' library.
# This tells the linker to include the compiled vector code in your final program.
# Because the library's include directory was set as PUBLIC, the executable
# automatically inherits the path to 'include/'.
target_link_libraries(my_c_app PRIVATE my_c_lib)

