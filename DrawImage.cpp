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
	//world.set_perspective(true);
	world.set_sample_number(5.0);
	world.set_diffuse(Vector3D(0,0,1),0.75,1.0);
	std::cout << "Parameters setting completed" << std::endl;	

	std::cout << "Generating image....." << std::endl;
	world.render_scene();
	world.Image->writeToFile("solution.png");
	delete world.Image;
	std::cout << "Image drawing completed" << std::endl;

	std::cout << "Cleaning up" << std::endl;
	world.delete_objects();
	std::cout << "Cleaning completed" << std::endl;

	return 0;
}
