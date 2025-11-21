glslangValidator.exe -V --glsl-version 460 -S vert GeometryShader_vert.glsl -o GeometryShader_vert.spv -e main
glslangValidator.exe -V --glsl-version 460 -S frag GeometryShader_frag.glsl -o GeometryShader_frag.spv -e main
glslangValidator.exe -V --glsl-version 460 -S geom GeometryShader_geo.glsl  -o GeometryShader_geo.spv  -e main