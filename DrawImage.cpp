/**
 * @file DrawImage.cpp
 * Performs basic tests of ray tracing.
 * @date JAN 26 2016
 * @author Randolph-zeng
 */


#include <iostream>
#include "World.h"
#include "png.h"

int main()
{
	std::cout << "Building World....." << std::endl;
	World world;
	world.build();
	std::cout << "World building completed" << std::endl;

	std::cout << "Setting View Parameters" << std::endl;
	world.set_sample_number(16.0);
	world.set_diffuse(0.75,1.0);
	std::cout << "Parameters setting completed" << std::endl;	

	std::cout << "Generating image....." << std::endl;
	world.pinhole_ptr->render_scene(world);
	world.pinhole_ptr->Image->writeToFile("solution2.png");
	delete world.pinhole_ptr->Image;
	std::cout << "Image drawing completed" << std::endl;

	std::cout << "Cleaning up" << std::endl;
	world.delete_objects();
	std::cout << "Cleaning completed" << std::endl;

	return 0;
}
