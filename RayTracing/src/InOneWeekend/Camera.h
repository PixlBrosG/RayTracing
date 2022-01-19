#pragma once

#include "InOneWeekend/RTWeekend.h"

namespace RayTracing {

	class Camera
	{
	public:
		// vfov = vertical field-of-view in degrees
		Camera(float vfov, float aspectRatio);

		Ray GetRay(float u, float v) const;
	private:
		glm::vec3 m_Origin;
		glm::vec3 m_LowerLeftCorner;

		glm::vec3 m_Horizontal;
		glm::vec3 m_Vertical;
	};

}
