#include <iostream>

#include "Core/Base.h"

#include "InOneWeekend/Color.h"
#include "InOneWeekend/Ray.h"

int main()
{
	// Initializing
	RayTracing::Log::Init();

	// Image
	constexpr float aspectRatio = 16.0f / 9.0f;
	constexpr int imageWidth = 400;
	constexpr int imageHeight = (int)(imageWidth / aspectRatio);

	// Camera
	float viewportHeight = 2.0f;
	float viewportWidth = aspectRatio * viewportHeight;
	float focalLength = 1.0f;

	glm::vec3 origin{ 0, 0, 0 };
	glm::vec3 horizontal{ viewportWidth, 0, 0 };
	glm::vec3 vertical{ 0, viewportHeight, 0 };
	glm::vec3 lowerLeftCorner = origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3{ 0, 0, focalLength };

	// Render
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << 255 << std::endl;

	for (int y = imageHeight - 1; y >= 0; --y)
	{
		for (int x = 0; x < imageWidth; ++x)
		{
			float u = (float)x / (imageWidth - 1);
			float v = (float)y / (imageHeight - 1);

			RayTracing::Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			glm::vec3 color = RayTracing::GetRayColor(ray);

			std::cout << color << std::endl;
		}
	}

	std::cerr << "Done." << std::endl;

	return 0;

}

