	glslangValidator.exe -V -S comp LumenComputeShader_comp.glsl -o LumenComputeShader_comp.spv -e main	
	spirv-cross.exe --version 460 LumenComputeShader_comp.spv --output glsl_comp.hlsl --hlsl
	
	
	glslangValidator.exe -V -S frag LumenComputeShader_frag.glsl -o LumenComputeShader_frag.spv -e main
	spirv-cross.exe LumenComputeShader_frag.spv --output glsl_frag.hlsl --hlsl
	
	glslangValidator.exe -V -S vert LumenComputeShader_vert.glsl -o LumenComputeShader_vert.spv -e main
	spirv-cross.exe LumenComputeShader_vert.spv --output glsl_vert.hlsl --hlsl