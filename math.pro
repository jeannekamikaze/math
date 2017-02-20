TEMPLATE = lib
CONFIG += static
CONFIG -= qt

CONFIG(release, debug|release) {
    DESTDIR=$$(SRC)/build/release
    OBJECTS_DIR=$$(SRC)/.obj/release/$$TARGET
}
else {
    DESTDIR=$$(SRC)/build/debug
    OBJECTS_DIR=$$(SRC)/.obj/debug/$$TARGET
}

QMAKE_CXXFLAGS_DEBUG += -DDEBUG
unix: {
    QMAKE_CXXFLAGS += --std=c++11
}
win32: {
    QMAKE_CXXFLAGS += -DNOMINMAX
    QMAKE_CXXFLAGS_DEBUG += /Zi
    QMAKE_LFLAGS_DEBUG += /DEBUG
}

INCLUDEPATH = include
DEPENDPATH = include

HEADERS += \
    include/math/AABB2.h \
    include/math/AABB3.h \
    include/math/area.h \
    include/math/axis_plane.h \
    include/math/camera.h \
    include/math/circle.h \
    include/math/defs.h \
    include/math/determinant.h \
    include/math/frustum.h \
    include/math/interpolation.h \
    include/math/intersection.h \
    include/math/mat3.h \
    include/math/mat4.h \
    include/math/plane.h \
    include/math/quad2.h \
    include/math/quad3.h \
    include/math/quat.h \
    include/math/rasterization.h \
    include/math/ray3.h \
    include/math/sampling.h \
    include/math/spatial.h \
    include/math/sphere.h \
    include/math/texel.h \
    include/math/triangle2.h \
    include/math/triangle3.h \
    include/math/utils.h \
    include/math/vec2.h \
    include/math/vec3.h \
    include/math/vec4.h

SOURCES += \
    src/AABB2.cc \
    src/AABB3.cc \
    src/area.cc \
    src/frustum.cc \
    src/interpolation.cc \
    src/intersection.cc \
    src/mat3.cc \
    src/mat4.cc \
    src/plane.cc \
    src/quat.cc \
    src/rasterization.cc \
    src/sampling.cc \
    src/spatial.cc \
    src/utils.cc \
    src/vec3.cc \
    src/vec4.cc
