add_library(card STATIC utils/card.cc)
add_library(deck STATIC utils/deck.cc)
add_library(player STATIC utils/player.cc)
add_library(json SHARED 3rd_party/json.cc)
add_library(thread_pool SHARED 3rd_party/BS_thread_pool.cc)

target_include_directories(card PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(deck PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(player PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(json PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(thread_pool PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(deck PRIVATE card)
target_link_libraries(player PRIVATE deck)