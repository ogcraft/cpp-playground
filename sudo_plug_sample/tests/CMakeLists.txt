set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(cpptest_test tests.cpp catch_amalgamated.cpp)
target_compile_features(cpptest_test PUBLIC cxx_std_20)
target_link_libraries(cpptest_test Threads::Threads)
