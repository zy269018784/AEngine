#include <iostream>
#include "GLFW_Include.h"


int helloes2_0(int argc, char **argv) 
{
	if (!glfwInit())
	{
		std::cout << "init eror" << std::endl;
		return -1;
	}
	glfwSetErrorCallback(GLFWErrorCallback);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
       	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
       	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    	auto Handle = glfwCreateWindow(800, 600, "aaa", NULL, NULL);
    	std::cout << "glfw handle " << Handle << std::endl;
    	glfwMakeContextCurrent(Handle);
	if (gladLoadGLES2Loader((GLADloadproc)(glfwGetProcAddress)))
	{
		std::cout << "gladLoadGL ES failed AA" << std::endl;
	}
    while (!glfwWindowShouldClose(Handle))
    {
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(Handle);
        glfwPollEvents();
    }
	return 0;

}
