#include <iostream>

#include "Core/Base.h"
#include "Core/Timer.h"

#include "Common/RTUtils.h"

#include "InOneWeekend/HittableList.h"
#include "InOneWeekend/Camera.h"

int main()
{
	using namespace RayTracing;

	// Initializing
	Log::Init();
	Timer timer;

	// Image
	constexpr float aspectRatio = 16.0f / 9.0f;
	constexpr int imageWidth = 400;
	constexpr int imageHeight = (int)(imageWidth / aspectRatio);
	constexpr int samplesPerPixel = 100;
	constexpr int maxDepth = 8;

	// World

	HittableList world = Utils::RandomScene();

	// Camera
	constexpr glm::vec3 lookFrom{ 13, 2, 3 };
	constexpr glm::vec3 lookAt{ 0, 0, 0 };
	constexpr glm::vec3 vup{ 0, 1, 0 };
	constexpr float distToFocus = 10.0f;
	constexpr float aperture = 0.1f;

	Camera camera(lookFrom, lookAt, vup, 20, aspectRatio, aperture, distToFocus, 0.0f, 1.0f);

	// Render
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << 255 << std::endl;

	for (int y = imageHeight - 1; y >= 0; --y)
	{
		std::cerr << "\rScanlines remaining: " << y << "   " << std::flush;

		for (int x = 0; x < imageWidth; ++x)
		{
			glm::vec3 color{ 0, 0, 0 };
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				float u = (x + Utils::RandomFloat()) / (imageWidth - 1);
				float v = (y + Utils::RandomFloat()) / (imageHeight - 1);
				Ray ray = camera.GetRay(u, v);
				color += Utils::GetRayColor(ray, world, maxDepth);
			}

			constexpr float scale = 1.0f / samplesPerPixel;
			std::cout << color * scale;
		}
	}

	std::cerr << std::endl << "Finished in "
		<< timer.Elapsed() << " seconds" << std::endl;

	return 0;

}

