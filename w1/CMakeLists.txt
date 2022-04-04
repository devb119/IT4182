add_executable(tudien bai1.c)

add_subdirectory(libfdr)
target_link_libraries(tudien fdr)
