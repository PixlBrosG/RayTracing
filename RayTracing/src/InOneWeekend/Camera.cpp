#include "InOneWeekend/Camera.h"

namespace RayTracing {

	Camera::Camera()
		: m_Origin(0, 0, 0)
	{
		float aspectRatio = 16.0f / 9.0f;
		float viewportHeight = 2.0f;
		float viewportWidth = aspectRatio * viewportHeight;
		float focalLength = 1.0f;

		m_Horizontal = glm::vec3{ viewportWidth, 0.0f, 0.0f };
		m_Vertical = glm::vec3{ 0.0f, viewportHeight, 0.0f };
//		m_LowerLeftCorner = m_Origin - m_Horizontal / 2.0f - m_Vertical / 2 - glm::vec3{ 0.0f, 0.0f, focalLength };
		m_LowerLeftCorner = glm::vec3{ -viewportWidth / 2.0f, -viewportHeight / 2.0f, -focalLength };
	}

	Ray Camera::GetRay(float u, float v) const
	{
		return Ray(m_Origin, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical);
	}

}