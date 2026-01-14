#include <iostream>
#include "Model/Model.h"

int ModelMain(int argc, char **argv)
{
    std::cout << "periwinkle_plant_1k.gltf" << std::endl;
    Model model;
    model.LoadModel("periwinkle_plant_1k.gltf");
    return 0;
}