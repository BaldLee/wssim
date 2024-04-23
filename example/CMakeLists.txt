add_executable(simple_sim simple_sim.cc)

target_link_libraries(simple_sim PRIVATE benchmark player)