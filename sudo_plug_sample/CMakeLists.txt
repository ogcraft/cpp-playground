cmake_minimum_required(VERSION 3.1...3.19)

project(
  sudo_plug_sample
  VERSION 1.0
  LANGUAGES CXX)
  
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src)
#add_subdirectory(tests)
