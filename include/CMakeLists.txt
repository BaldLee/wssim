add_library(libjson INTERFACE)
add_library(libthreadpool INTERFACE)
add_library(libwssim INTERFACE)
add_library(libtestcase INTERFACE)

target_include_directories(libjson INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(libthreadpool INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(libwssim INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(libtestcase INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(libwssim INTERFACE libjson libthreadpool pthread)
target_link_libraries(libtestcase INTERFACE libwssim)