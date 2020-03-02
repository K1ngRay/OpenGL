#pragma once
#include "stb/stb_image.h"
#include <glad/glad.h>
#include <vector>

class Texture
{
public:
	//写成静态的，就不用创建对象了
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
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); //指定一个二维的纹理图片
			glGenerateMipmap(GL_TEXTURE_2D); //为纹理对象生成一组完整的mipmap。 unity mipmap：https://www.cnblogs.com/MrZivChu/p/mipmap.html

			//纹理过滤函数glTexParameteri()
			//图象从纹理图象空间映射到帧缓冲图象空间(映射需要重新构造纹理图像, 这样就会造成应用到多边形上的图像失真), 这时就可用glTexParmeteri()函数来确定如何把纹理象素映射成像素.
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			//GL_TEXTURE_WRAP_S 表示在 s 轴上纹理的环绕方式
			//GL_TEXTURE_WRAP_T 表示在 T 轴上纹理的环绕方式
			//这里 s 和 t等价于平面纹理图片的 x 轴和 y 轴			//GL_REPEAT 是表示纹理重复出现，它也是在不设置的情况下默认环绕方式。GL_MIRRORED_REPEAT 也是重复图片，但是他表示以镜像方式重复出现；
			//GL_CLAMP_TO_EDGE 表示纹理坐标会被约束在 0 - 1 之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。这种环绕方式通常会在我们设置纹理坐标超过 0 - 1 的范围时被使用到。			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//纹理过滤的介绍：https://blog.csdn.net/u013746357/article/details/90723268
			//设置纹理在缩小和放大时的过滤方式
			//过滤方式我们主要使用的有两种，一种是 GL_NEAREST 即临近过滤，这种过滤方法会产生颗粒状的图案，但是也能更清晰的看到组成纹理的像素。
			//GL_LINEAR 即线性过滤，它能够产生更平滑的图案，但是也有更真实的输出。
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
			stbi_set_flip_vertically_on_load(false);	//为什么这里就不用旋转y轴了呢:https://blog.csdn.net/qjh5606/article/details/89847297 目前可以简单的理解为天空盒不用翻转
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
