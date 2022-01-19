#include "InOneWeekend/Camera.h"

namespace RayTracing {

	Camera::Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vup, float vfov, float aspectRatio)
		: m_Origin(lookFrom)
	{
		float theta = glm::radians(vfov);
		float h = glm::tan(theta / 2);
		float viewportHeight = 2.0f * h;
		float viewportWidth = aspectRatio * viewportHeight;

		glm::vec3 w = glm::normalize(lookFrom - lookAt);
		glm::vec3 u = glm::normalize(glm::cross(vup, w));
		glm::vec3 v = glm::cross(w, u);

		m_Horizontal = viewportWidth * u;
		m_Vertical = viewportHeight * v;
		m_LowerLeftCorner = m_Origin - m_Horizontal / 2.0f - m_Vertical / 2.0f - w;
	}

	Ray Camera::GetRay(float s, float t) const
	{
		return Ray(m_Origin, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin);
	}

}
