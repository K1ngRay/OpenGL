#pragma once

#include<GLFW/glfw3.h>

class Project
{
public:
	Project();

	virtual GLFWwindow* CreateWindow(unsigned int width, unsigned int height, GLFWmonitor* monitor, GLFWwindow* share) = 0;

};

Project::Project()
{
}

