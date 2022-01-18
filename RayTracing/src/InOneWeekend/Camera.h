#pragma once

#include "InOneWeekend/RTWeekend.h"

namespace RayTracing {

	class Camera
	{
	public:
		Camera();

		Ray GetRay(float u, float v) const;
	private:
		glm::vec3 m_Origin;
		glm::vec3 m_LowerLeftCorner;

		glm::vec3 m_Horizontal;
		glm::vec3 m_Vertical;
	};

}
