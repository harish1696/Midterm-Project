add_executable(countStock main.cpp detectQRcode.cpp decodeQRcode.cpp countID.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries (countStock ${OpenCV_LIBS})
