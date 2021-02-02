#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
#find_package(Threads REQUIRED)

add_library(sudo_plug_sample SHARED sudo_plug_sample.cpp)

target_include_directories(sudo_plug_sample PUBLIC ${USER}/code/sudo/include)
target_compile_features(sudo_plug_sample PUBLIC cxx_std_20)

