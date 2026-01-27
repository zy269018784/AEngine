#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4 OpenGLRightHandedViewMatrix(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up);
glm::mat4 OpenGLLeftHandedViewMatrix(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up);
glm::mat4 VulkanRightHandedViewMatrix(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up);
glm::mat4 VulkanLeftHandedViewMatrix(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up);