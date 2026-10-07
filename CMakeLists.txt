cmake_minimum_required(VERSION 3.20)

project(file_qr LANGUAGES CXX)

include(FetchContent)
include(CTest)

FetchContent_Declare(
  qrcodegen
  GIT_REPOSITORY https://github.com/nayuki/QR-Code-generator.git
  GIT_TAG v1.8.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(qrcodegen)

add_library(qrcodegen STATIC
  "${qrcodegen_SOURCE_DIR}/cpp/qrcodegen.cpp"
)
target_include_directories(qrcodegen PUBLIC
  "${qrcodegen_SOURCE_DIR}"
)
target_compile_features(qrcodegen PUBLIC cxx_std_11)

add_executable(file_qr src/main.cpp)
target_compile_features(file_qr PRIVATE cxx_std_17)
target_link_libraries(file_qr PRIVATE qrcodegen)

if (BUILD_TESTING)
  add_test(NAME file_qr_missing_argument COMMAND file_qr)
  set_tests_properties(file_qr_missing_argument PROPERTIES WILL_FAIL TRUE)
endif()
