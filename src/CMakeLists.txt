add_executable(csa main.cpp suffixSorting.cpp)
target_link_libraries(csa sdsl divsufsort divsufsort64)
install(TARGETS csa DESTINATION ${CMAKE_SOURCE_DIR}/bin)

