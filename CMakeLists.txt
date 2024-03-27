cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

add_library(deck_library STATIC src/utils/deck.cc src/utils/card.cc)

target_include_directories(deck_library PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(decktest test/testdeck.cc)

target_link_libraries(decktest PRIVATE deck_library)