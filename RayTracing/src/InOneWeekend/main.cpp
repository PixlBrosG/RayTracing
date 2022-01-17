#include <iostream>

int main()
{
	// Image
	constexpr int imageWidth  = 256;
	constexpr int imageHeight = 256;

	// Render
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << 255 << std::endl;

	for (int y = imageHeight - 1; y >= 0; --y)
	{
		for (int x = 0; x < imageWidth; ++x)
		{
			float r = (float)x / (imageWidth  - 1);
			float g = (float)y / (imageHeight - 1);
			float b = 0.25f;

			int ir = (int)(255.999f * r);
			int ig = (int)(255.999f * g);
			int ib = (int)(255.999f * b);

			std::cout << ir << ' ' << ig << ' ' << ib << std::endl;
		}
	}

	return 0;

}