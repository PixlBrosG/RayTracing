#pragma once

#include "InOneWeekend/RTWeekend.h"

namespace RayTracing {

	class Camera
	{
	public:
		// vfov = vertical field-of-view in degrees
		Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vup, float vfov, float aspectRatio, float aperture, float focusDist);

		Ray GetRay(float s, float t) const;
	private:
		glm::vec3 m_Origin;
		glm::vec3 m_LowerLeftCorner;

		glm::vec3 m_Horizontal;
		glm::vec3 m_Vertical;

		glm::vec3 m_U, m_V, m_W;
		float m_LensRadius;
	};

}
