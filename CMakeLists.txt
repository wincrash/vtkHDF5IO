cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(vtkHDF5IO)


find_package(HDF5 REQUIRED COMPONENTS C CXX HL)
include_directories(${HDF5_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/highfive)
add_executable(vtkHDF5IO src/writedata.cpp)
target_link_libraries(vtkHDF5IO ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES}  ${HDF5_HL_LIBRARIES})
