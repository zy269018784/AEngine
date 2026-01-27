#include "CoordSystem.h"

glm::mat4 OpenGLRightHandedViewMatrix(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up)
{
    return {};
}

glm::mat4 OpenGLLeftHandedViewMatrix(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up)
{
    glm::mat4 View1 = glm::lookAtRH(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
    //glm::mat4 View2 = glm::lookAtRH(Eye, Target, Up);
    return View1;
}

glm::mat4 VulkanRightHandedViewMatrix(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up)
{
    return {};
}

glm::mat4 VulkanLeftHandedViewMatrix(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up)
{
    glm::mat4 View1 = glm::lookAtLH(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, -1, 0));
    //glm::mat4 View2 = glm::lookAtLH(Eye, Target, Up);
    return View1;
}

