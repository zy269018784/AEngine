	glslangValidator.exe -V -S comp -D LumenComputeShader_comp.hlsl -o LumenComputeShader_comp.spv -e hellomain	
	spirv-cross.exe --version 460 LumenComputeShader_comp.spv --output hlsl_comp.glsl 
