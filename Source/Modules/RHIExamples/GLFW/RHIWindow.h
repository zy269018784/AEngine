#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
namespace GLFW_RHIWindow
{
	class RHIWindow
	{
	public:
		enum GraphicsAPI {
			OpenGL33,
			OpenGL46,
			ES20,
			ES31,
			ES32,
			Vulkan,
			D3D9,
			D3D10,
			D3D11,
			D3D12,
			Metal
		};
	public:
		RHIWindow(int Width, int Height, GraphicsAPI API);
		~RHIWindow();
	public:
		GLFWwindow* GetHandle();
	public:
		void MakeContextCurrent(void);
		void SetFramebufferSizeCallback(GLFWframebuffersizefun Callback);
		int WindowShouldClose(void);
		void SwapBuffers(void);
		void PollEvents(void);
	private:
		GLFWwindow* Handle;
	};
}