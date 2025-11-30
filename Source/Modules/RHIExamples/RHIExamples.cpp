#include "RHIApplicationTriangle.h"
#include "RHIApplicationTriangleIndexed.h"
#include "RHIApplicationModel.h"
#include "RHIApplicationScene.h"
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
#include "RHIApplicationPlayer.h"
#include "Window/GLFWWindow.h"
#include "Vulkan/Common.h"
void Example_Model(GLFWwindow* Window)
{
	RHIApplicationModel App(Window);
	App.Run();
}

void Example_Triangle(GLFWwindow* Window)
{
	RHIApplicationTriangle App(Window);
	App.Run();
}

void Example_TriangleIndexed(GLFWwindow* Window)
{
	RHIApplicationTriangleIndexed App(Window);
	App.Run();
}

void Example_DepthTest(GLFWwindow* Window)
{
	RHIApplicationDepthTest App(Window);
	App.Run();
}


void Example_Scene(GLFWwindow* Window)
{
	RHIApplicationScene App(Window);
	App.Run();
}


void Example_UBO(GLFWwindow* Window)
{
	RHIApplicationUBO App(Window);
	App.Run();
}

void Example_SSBO(GLFWwindow* Window)
{
	RHIApplicationSSBO App(Window);
	App.Run();
}

void Example_Texture1D(GLFWwindow* Window)
{
	RHIApplicationTexture1D App(Window);
	App.Run();
}

void Example_Texture1DArray(GLFWwindow* Window)
{
	RHIApplicationTexture1DArray App(Window);
	App.Run();
}
void Example_Texture2D(GLFWwindow* Window)
{
	RHIApplicationTexture2D App(Window);
	App.Run();
}

void Example_Texture2DArray(GLFWwindow* Window)
{
	RHIApplicationTexture2DArray App(Window);
	App.Run();
}

void Example_Texture3D(GLFWwindow* Window)
{
	RHIApplicationTexture3D App(Window);
	App.Run();
}

void Example_TextureCubeMap(GLFWwindow* Window)
{
	RHIApplicationTextureCubeMap App(Window);
	App.Run();
}

void Example_TextureCubeMapArray(GLFWwindow* Window)
{
	RHIApplicationTextureCubeMapArray App(Window);
	App.Run();
}


void Example_SampleObject(GLFWwindow* Window)
{
	RHIApplicationSamplerObject App(Window);
	App.Run();
}

void Example_GeometryShader(GLFWwindow* Window)
{
	RHIApplicationGeometryShader App(Window);
	App.Run();
}

void Example_Player(GLFWwindow* Window)
{
	RHIApplicationPlayer App(Window);
	App.Run();
}

int RHIExample()
{
#ifdef PROJECT_USE_GLFW
	glfwInit();
#endif
#if USE_RHI_VULKAN
	//GLFW_RHIWindow::RHIWindow* Window = new GLFW_RHIWindow::RHIWindow(800, 600, GLFW_RHIWindow::RHIWindow::GraphicsAPI::Vulkan);
	GLFWWindow *Window = new GLFWWindow(IWindow::Vulkan);
#else
	//GLFW_RHIWindow::RHIWindow* Window = new GLFW_RHIWindow::RHIWindow(800, 600, GLFW_RHIWindow::RHIWindow::GraphicsAPI::OpenGL46);
	GLFWWindow *Window = new GLFWWindow(IWindow::OpenGL46);
	Window->MakeContextCurrent();
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
		Example_TextureCubeMap			OK,		
		Example_TextureCubeMapArray		OK,		
	*/
	//Example_Model(Window->GetHandle());
	Example_Triangle(Window->GetHandle());
	//Example_TriangleIndexed(Window->GetHandle());
	//Example_DepthTest(Window->GetHandle());
	//Example_UBO(Window->GetHandle());
	//Example_SSBO(Window->GetHandle());
	//Example_Texture1D(Window->GetHandle());
	//Example_Texture1DArray(Window->GetHandle());
	//Example_Texture2D(Window->GetHandle());
	
	//Example_Texture2DArray(Window->GetHandle());
	//Example_Texture3D(Window->GetHandle());
	//Example_TextureCubeMap(Window->GetHandle());
	//Example_TextureCubeMapArray(Window->GetHandle());
	//Example_SampleObject(Window->GetHandle());
	//Example_GeometryShader(Window->GetHandle());
	//Example_Scene(Window->GetHandle());
	//Example_Player(Window->GetHandle());
	CleanupWindow(Window->GetHandle());

	return 0;
}