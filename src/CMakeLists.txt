add_library(deck STATIC utils/deck.cc)
add_library(card STATIC utils/card.cc)

target_include_directories(deck PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(card PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(deck PRIVATE card)