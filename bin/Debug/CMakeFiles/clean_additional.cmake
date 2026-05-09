# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DeviceTest_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DeviceTest_autogen.dir\\ParseCache.txt"
  "DeviceTest_autogen"
  "modules\\Comm\\CMakeFiles\\Comm_autogen.dir\\AutogenUsed.txt"
  "modules\\Comm\\CMakeFiles\\Comm_autogen.dir\\ParseCache.txt"
  "modules\\Comm\\Comm_autogen"
  "modules\\ScdParse\\CMakeFiles\\ScdParse_autogen.dir\\AutogenUsed.txt"
  "modules\\ScdParse\\CMakeFiles\\ScdParse_autogen.dir\\ParseCache.txt"
  "modules\\ScdParse\\ScdParse_autogen"
  )
endif()
