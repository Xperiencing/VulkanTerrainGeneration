#ifndef PLANE_H
#define PLANE_H

#include "all_headers.h"

//Vertex structure, defining the attributes of each vertex.
struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}
	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}
};

//Class to generate a flat plane to work with for terrain generation.
class Plane
{
public:
	//plane attributes;
	float size, area;
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	Plane(float SIZE, float AREA) {
		size = SIZE;
		area = AREA;

		generateVertsIndices();

		/*vertices = {
			{{-0.5f, 1.0f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, 1.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 1.0f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

			{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};

		indices = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};*/
	}

private:
	//Function to generate the vertices positions and indeces
	void generateVertsIndices() {
		for (int j = 0; j <= size; ++j)
		{
			for (int i = 0; i <= size; ++i)
			{
				float x = (float)i / area;
				float z = (float)j / area;
				float y = f(z, x);
				

				vertices.push_back({ glm::vec3(x, y, z), { floatRand(), floatRand(), floatRand() }, { (float)i/area, (float)j/area} });
			}
		}

		for (int j = 0; j < size; ++j)
		{
			for (int i = 0; i < size; ++i)
			{
				int row1 = j * (size + 1);
				int row2 = (j + 1) * (size + 1);

				// triangle 1
				indices.push_back(uint16_t(row1 + i));
				indices.push_back(uint16_t(row1 + i + 1));
				indices.push_back(uint16_t(row2 + i + 1));

				// triangle 2
				indices.push_back(uint16_t(row1 + i));
				indices.push_back(uint16_t(row2 + i + 1));
				indices.push_back(uint16_t(row2 + i));
			}
		}
	}

	float f(float x, float y)
	{
		// use any curve function you want
		return sin(x*2.0f*3.141526f) * sin(y*2.0f*3.141526f) * 0.5f;
	}

	float floatRand() {
		return float(rand()) / (float(RAND_MAX) + 1.0);
	}
};

#endif