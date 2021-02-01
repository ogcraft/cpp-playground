set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(cpptest1 cpptest1.cpp)
target_compile_features(cpptest1 PUBLIC cxx_std_20)
target_link_libraries(cpptest1 Threads::Threads)

add_executable(cpptest_argv cpptest_argv.cpp)
target_compile_features(cpptest_argv PUBLIC cxx_std_20)
target_link_libraries(cpptest_argv Threads::Threads)
