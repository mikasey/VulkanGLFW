@echo off
set glslc=%VULKAN_SDK%/Bin/glslc.exe

%glslc% basic_triangle.vert -o vert.spv
%glslc% basic_triangle.frag -o frag.spv
