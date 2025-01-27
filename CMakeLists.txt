cmake_minimum_required(VERSION 3.30)
project(NetTrafficObserver)

set(CMAKE_CXX_STANDARD 20)

add_executable(NetTrafficObserver main.cpp)
cmake_minimum_required(VERSION 3.10)
project(NetTrafficObserver)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)

include_directories(${PCAP_INCLUDE_DIRS})
link_directories(${PCAP_LIBRARY_DIRS})

add_executable(NetTrafficObserver main.cpp)

target_link_libraries(NetTrafficObserver ${PCAP_LIBRARIES})
