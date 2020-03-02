#pragma once
#include "stb/stb_image.h"
#include <glad/glad.h>
#include <vector>

class Texture
{
public:
	//д�ɾ�̬�ģ��Ͳ��ô���������
	static unsigned int LoadTextureFromFile(const char* path)
	{
		unsigned int texture_id;
		glGenTextures(1, &texture_id);

		int width, height, nr_channels;
		stbi_set_flip_vertically_on_load(true);  //ʵ�ַ�תy����,��Ϊ OpenGL��������������������½�. ��ͼ���������������������Ͻ�.
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
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); //ָ��һ����ά������ͼƬ
			glGenerateMipmap(GL_TEXTURE_2D); //Ϊ�����������һ��������mipmap�� unity mipmap��https://www.cnblogs.com/MrZivChu/p/mipmap.html

			//������˺���glTexParameteri()
			//ͼ�������ͼ��ռ�ӳ�䵽֡����ͼ��ռ�(ӳ����Ҫ���¹�������ͼ��, �����ͻ����Ӧ�õ�������ϵ�ͼ��ʧ��), ��ʱ�Ϳ���glTexParmeteri()������ȷ����ΰ���������ӳ�������.
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			//GL_TEXTURE_WRAP_S ��ʾ�� s ��������Ļ��Ʒ�ʽ
			//GL_TEXTURE_WRAP_T ��ʾ�� T ��������Ļ��Ʒ�ʽ
			//���� s �� t�ȼ���ƽ������ͼƬ�� x ��� y ��			//GL_REPEAT �Ǳ�ʾ�����ظ����֣���Ҳ���ڲ����õ������Ĭ�ϻ��Ʒ�ʽ��GL_MIRRORED_REPEAT Ҳ���ظ�ͼƬ����������ʾ�Ծ���ʽ�ظ����֣�
			//GL_CLAMP_TO_EDGE ��ʾ��������ᱻԼ���� 0 - 1 ֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч�������ֻ��Ʒ�ʽͨ���������������������곬�� 0 - 1 �ķ�Χʱ��ʹ�õ���			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//������˵Ľ��ܣ�https://blog.csdn.net/u013746357/article/details/90723268
			//������������С�ͷŴ�ʱ�Ĺ��˷�ʽ
			//���˷�ʽ������Ҫʹ�õ������֣�һ���� GL_NEAREST ���ٽ����ˣ����ֹ��˷������������״��ͼ��������Ҳ�ܸ������Ŀ��������������ء�
			//GL_LINEAR �����Թ��ˣ����ܹ�������ƽ����ͼ��������Ҳ�и���ʵ�������
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
			stbi_set_flip_vertically_on_load(false);	//Ϊʲô����Ͳ�����תy������:https://blog.csdn.net/qjh5606/article/details/89847297 Ŀǰ���Լ򵥵����Ϊ��պв��÷�ת
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
		//TODO���úÿ�
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return texture;
	}
};
