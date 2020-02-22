#pragma once
#include "Project.h"
class Shadow : public Project
{
public:
	Shadow ();

	GLFWwindow* CreateWindow(unsigned int width, unsigned int height, GLFWmonitor* monitor, GLFWwindow* share) = 0;


private:

};
