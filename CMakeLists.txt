# 1. The Minimum Version Required
cmake_minimum_required(VERSION 3.10)

# 2. Project Name and Version
project(ThreadedHeart VERSION 1.0)

# 3. Set the C++ Standard to 17 (Modern Industry Standard)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Tell CMake where our "Vault" (Headers) is
include_directories(include)

# 5. List all our "Kitchen" files (Source files)
set(SOURCES 
    src/main.cpp
    src/SensorModule.cpp
    # We will add more files here later!
)

# 6. Create the "Finished Product" (The Executable)
add_executable(heart_engine ${SOURCES})

# 7. Threading Support (Crucial for this project!)
find_package(Threads REQUIRED)
target_link_libraries(heart_engine PUBLIC Threads::Threads)

# --- UNIT TESTING SECTION ---

# 1. Find the GTest package on Ubuntu
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 2. Create a separate executable just for tests
add_executable(run_tests tests/test_sensor.cpp src/SensorModule.cpp)

# 3. Link GTest and Threads to our test engine
target_link_libraries(run_tests GTest::GTest GTest::Main Threads::Threads)