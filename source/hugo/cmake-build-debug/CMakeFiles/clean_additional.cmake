# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/hugo_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/hugo_autogen.dir/ParseCache.txt"
  "hugo_autogen"
  )
endif()
