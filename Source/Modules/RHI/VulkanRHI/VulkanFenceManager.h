#pragma once
#include "VulkanObjects/Synchronization/VulkanFence.h"
#include <list>
#include <vector>
#include <cstdint>
class VulkanDevice;

class VulkanFenceManager
{
public:
	VulkanFenceManager() {};


protected:
	VulkanDevice* Device;

};