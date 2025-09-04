#! /bin/bash
rm -rfv ../bin/shaders/*
glslc shadersGLSL/shader.frag -o src/shaders/frag.spv
glslc shadersGLSL/shader.vert -o src/shaders/vert.spv
echo "Shader build stage ended"
