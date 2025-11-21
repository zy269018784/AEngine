#include "RHIWindow.h"
namespace GLFW_RHIWindow
{
	RHIWindow::RHIWindow(int Width, int Height, GraphicsAPI API)
	{
		//glfwInit();
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//Handle = glfwCreateWindow(Width, Height, "", nullptr, nullptr);
		//return;

		glfwInit();

		switch (API)
		{
		case OpenGL33:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			break;
		case OpenGL46:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			break;
		case ES20:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			break;
		case ES31:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			break;
		case ES32:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			break;
		case Vulkan:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;
		case D3D9:
		case D3D10:
		case D3D11:
		case D3D12:
		case Metal:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;
		default:
			break;
		}

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		Handle = glfwCreateWindow(Width, Height, "", nullptr, nullptr);
	}

	RHIWindow::~RHIWindow()
	{
		glfwTerminate();
		glfwDestroyWindow(Handle);
	}

	GLFWwindow* RHIWindow::GetHandle()
	{
		return Handle;
	}

	void RHIWindow::MakeContextCurrent()
	{
		glfwMakeContextCurrent(Handle);
	}

	void RHIWindow::SetFramebufferSizeCallback(GLFWframebuffersizefun Callback)
	{
		glfwSetFramebufferSizeCallback(Handle, Callback);
	}

	int RHIWindow::WindowShouldClose()
	{
		return glfwWindowShouldClose(Handle);
	}

	void RHIWindow::SwapBuffers(void)
	{
		glfwSwapBuffers(Handle);
	}

	void RHIWindow::PollEvents(void)
	{
		glfwPollEvents();
	}
}