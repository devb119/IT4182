project(libfdr C)
set(fdr_src dllist.c jrb.c jval.c)

if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
  set(fdr_src ${fdr_src} fields.c)
  message(STATUS "${CMAKE_SYSTEM_NAME} is detected and fields.c is added.")
else (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
  message(STATUS "${CMAKE_SYSTEM_NAME} is detected, you can use fields.c only in Linux")
endif (${CMAKE_SYSTEM_NAME} STREQUAL Linux)


add_library(fdr STATIC ${fdr_src})
target_compile_options(fdr PRIVATE -w)