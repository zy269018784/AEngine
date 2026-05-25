#include "RHIApplicationTriangle.h"
#include "RHIApplicationTriangleIndexed.h"
#include "RHIApplicationDepthTest.h"
#include "RHIApplicationUBO.h"
#include "RHIApplicationSSBO.h"
#include "RHIApplicationTexture1D.h"
#include "RHIApplicationTexture1DArray.h"
#include "RHIApplicationTexture2D.h"
#include "RHIApplicationTexture2DArray.h"
#include "RHIApplicationTexture3D.h"
#include "RHIApplicationTextureCubeMap.h"
#include "RHIApplicationTextureCubeMapArray.h"
#include "RHIApplicationSamplerObject.h"
#include "RHIApplicationGeometryShader.h"
#include "RHIApplicationRenderTarget.h"
#include "RHIApplicationTextureRenderTarget.h"
#include "RHIApplicationTexture2DSperateImageSampler.h"
#include "RHIApplicationTexture2DCombinedImageSampler.h"
#include "GLFWWindow/GLFWWindow.h"

void Example_Model()
{
	//RHIApplicationModel App;
	//App.Run();
}

void Example_Triangle()
{
	RHIApplicationTriangle App;
	App.Run();
}

void Example_TriangleIndexed()
{
	RHIApplicationTriangleIndexed App;
	App.Run();
}

void Example_DepthTest()
{
	RHIApplicationDepthTest App;
	App.Run();
}


void Example_Scene()
{
	//RHIApplicationScene App;
	//App.Run();
}


void Example_UBO()
{
	RHIApplicationUBO App;
	App.Run();
}

void Example_SSBO()
{
	RHIApplicationSSBO App;
	App.Run();
}

void Example_Texture1D()
{
	RHIApplicationTexture1D App;
	App.Run();
}

void Example_Texture1DArray()
{
	RHIApplicationTexture1DArray App;
	App.Run();
}

void Example_Texture2D()
{
	std::cout << "Example_Texture2D 1" << std::endl;
	RHIApplicationTexture2D App;
	std::cout << "Example_Texture2D 2" << std::endl;
	App.Run();
	std::cout << "Example_Texture2D 3" << std::endl;
}

void Example_TextureRenderTarget()
{
	RHIApplicationTextureRenderTarget App;
	App.Run();
}

void Example_Texture2DArray()
{
	RHIApplicationTexture2DArray App;
	App.Run();
}

void Example_Texture3D()
{
	RHIApplicationTexture3D App;
	App.Run();
}

void Example_TextureCubeMap()
{
	RHIApplicationTextureCubeMap App;
	App.Run();
}

void Example_TextureCubeMapArray()
{
	RHIApplicationTextureCubeMapArray App;
	App.Run();
}


void Example_SampleObject()
{
	RHIApplicationSamplerObject App;
	App.Run();
}

void Example_GeometryShader()
{
	RHIApplicationGeometryShader App;
	App.Run();
}

void Example_Player()
{
	//RHIApplicationPlayer App;
	//App.Run();
}

void Example_RenderTarget()
{
	RHIApplicationRenderTarget App;
	App.Run();
}

void Example_SperateImageSampler()
{
	RHIApplicationTexture2DSperateImageSampler App;
	App.Run();
}


void error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}
int RHIExample()
{
	std::cout << "RHIExample 1" << std::endl;
	glfwInit();
	glfwSetErrorCallback(error_callback);
	std::cout << "RHIExample 2" << std::endl;

#if  PROJECT_USE_SDL3
	SDL_Init(SDL_INIT_VIDEO);
#endif


	/*									OpenGL	Vulkan
		Example_Triangle				OK
		Example_TriangleIndexed			OK
		Example_DepthTest				OK
		Example_UBO						OK
		Example_SSBO					OK
		Example_Texture3D				OK		OK
		Example_Texture1D					
		Example_Texture1DArray			
		Example_Texture2D				OK		OK	
		Example_Texture2DArray			OK,		OK	
		Example_TextureCubeMap			OK,		OK
		Example_TextureCubeMapArray		OK,		
	*/
	//Example_Model();
	//Example_Triangle();
	//Example_TriangleIndexed();
	//Example_DepthTest();
	//Example_UBO();
	//Example_SSBO();
	//Example_Texture1D();
	//Example_Texture1DArray();
	//Example_Texture2D();
	//Example_Texture2DArray();
	//Example_Texture3D();
	Example_TextureCubeMap();
	//Example_TextureCubeMapArray();
	//Example_SampleObject();
	//Example_GeometryShader();
	//Example_Scene();
	//Example_Player();
	//Example_RenderTarget();
	//Example_TextureRenderTarget();
	//Example_SperateImageSampler();

	return 0;
}