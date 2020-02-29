cmake_minimum_required(VERSION 3.10)

project(math)

add_library(math
    src/AABB2.cc
    src/AABB3.cc
    src/area.cc
    src/frustum.cc
    src/interpolation.cc
    src/intersection.cc
    src/mat3.cc
    src/mat4.cc
    src/plane.cc
    src/quat.cc
    src/rasterization.cc
    src/sampling.cc
    src/spatial.cc
    src/utils.cc
    src/vec3.cc
    src/vec4.cc)

target_include_directories(math PUBLIC
    include)
