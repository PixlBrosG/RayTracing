#include "InOneWeekend/Camera.h"

namespace RayTracing {

	Camera::Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vup, float vfov, float aspectRatio, float aperture, float focusDist)
		: m_Origin(lookFrom)
	{
		float theta = glm::radians(vfov);
		float h = glm::tan(theta / 2);
		float viewportHeight = 2.0f * h;
		float viewportWidth = aspectRatio * viewportHeight;

		m_W = glm::normalize(lookFrom - lookAt);
		m_U = glm::normalize(glm::cross(vup, m_W));
		m_V = glm::cross(m_W, m_U);

		m_Horizontal = focusDist * viewportWidth * m_U;
		m_Vertical = focusDist * viewportHeight * m_V;
		m_LowerLeftCorner = m_Origin - m_Horizontal / 2.0f - m_Vertical / 2.0f - focusDist * m_W;

		m_LensRadius = aperture / 2;
	}

	Ray Camera::GetRay(float s, float t) const
	{
		glm::vec3 rd = m_LensRadius * Utils::RandomInUnitDisk();
		glm::vec3 offset = m_U * rd.x + m_V * rd.y;

		return Ray(m_Origin + offset, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin - offset);
	}

}
