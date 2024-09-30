# CMakeList.txt : CMake project for SlotMachineTest, include source and define
# project specific logic here.
#

# Add source to this project's executable.

set(SOURCE 
${SOURCE}
${CMAKE_CURRENT_SOURCE_DIR}/SlotMachineTest.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Payline.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/Reel.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/Slot.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/SlotMachine.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Symbol.cpp)
set(HEADERS 
${HEADERS}
${CMAKE_CURRENT_SOURCE_DIR}/SlotMachineTest.h
${CMAKE_CURRENT_SOURCE_DIR}/Payline.h
${CMAKE_CURRENT_SOURCE_DIR}/Reel.h 
${CMAKE_CURRENT_SOURCE_DIR}/Slot.h 
${CMAKE_CURRENT_SOURCE_DIR}/SlotMachine.h 
${CMAKE_CURRENT_SOURCE_DIR}/Symbol.h)
add_executable(SlotMachineTest ${SOURCE} ${HEADERS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SlotMachineTest PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
