	glslangValidator.exe -V -S comp -D LumenComputeShader_comp.hlsl -o LumenComputeShader_comp.spv -e main	
	spirv-cross.exe --version 460 LumenComputeShader_comp.spv --output hlsl_comp.glsl 
	
	glslangValidator.exe -V -S frag -D LumenComputeShader_frag.hlsl -o LumenComputeShader_frag.spv -e main
	spirv-cross.exe LumenComputeShader_frag.spv --output hlsl_frag.glsl
	
	glslangValidator.exe -V -S vert -D LumenComputeShader_vert.hlsl -o LumenComputeShader_vert.spv -e main
	spirv-cross.exe LumenComputeShader_vert.spv --output hlsl_vert.glsl 