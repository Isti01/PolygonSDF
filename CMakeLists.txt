add_falcor_executable(TriangleSample)

target_sources(TriangleSample PRIVATE
    TriangleSample.cpp
    TriangleSample.h
    TriangleSample.slang
)

target_copy_shaders(TriangleSample Samples/TriangleSample)

target_source_group(TriangleSample "Samples")
