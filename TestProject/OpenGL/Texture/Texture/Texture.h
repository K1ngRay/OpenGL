#pragma once
#include "stb/stb_image.h"
#include <glad/glad.h>
#include <vector>

class Texture
{
public:
	//TODO:为什么这里要写静态的
	static unsigned int LoadTextureFromFile(const char* path)
	{
		unsigned int texture_id;
		glGenTextures(1, &texture_id);

		int width, height, nr_channels;
		stbi_set_flip_vertically_on_load(true);  //实现翻转y坐标,因为 OpenGL的纹理坐标起点在于左下角. 而图像纹理坐标的起点在于左上角.
		stbi_uc *data = stbi_load(path, &width, &height, &nr_channels, 0);
		if (data)
		{
			GLenum format;
			if (nr_channels == 1)
			{
				format = GL_RED;
			}
			else if (nr_channels == 3)
			{
				format = GL_RGB;
			}
			else if (nr_channels == 4)
			{
				format = GL_RGBA;
			}

			glBindTexture(GL_TEXTURE_2D, texture_id);
			//TODO：调试看看data里面存了什么,还有这两句是什么意思
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		return texture_id;
	}

	static unsigned int LoadTexturesFromFile(vector<string> faces)
	{
		unsigned int texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

		int width, height, channels;
		for (int i = 0; i < faces.size(); i++)
		{
			stbi_set_flip_vertically_on_load(false);	//为什么这里就不用旋转y轴了呢
			stbi_uc *data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			}
			stbi_image_free(data);
		}
		//TODO：好好看
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return texture;
	}
};
