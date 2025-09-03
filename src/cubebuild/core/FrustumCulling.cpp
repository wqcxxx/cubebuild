#include "FrustumCulling.h"

Plane::Plane(const glm::vec3& p1, const glm::vec3& norm)
    : normal(glm::normalize(norm)), distance(glm::dot(normal, p1))
{}
 
float Plane::get_signed_distance_to_plane(const glm::vec3& point) const 
{
    return glm::dot(normal, point) - distance;
}

AABB::AABB(const glm::vec3& position)
    : min(position), max(position + glm::vec3(1.0f)) {}

AABB::AABB(const glm::vec3& min, const glm::vec3& max)
    : min(min), max(max) {}

glm::vec3 AABB::get_center() const
{
    return (min + max) * 0.5f;
}

glm::vec3 AABB::get_extents() const
{
    return (max - min) * 0.5f;
}

bool AABB::check_plane(const Plane& plane) const 
{
    glm::vec3 center = get_center();
    glm::vec3 extents = get_extents();

    float r = extents.x * std::abs(plane.normal.x) +
              extents.y * std::abs(plane.normal.y) +
              extents.z * std::abs(plane.normal.z);
    
    return plane.get_signed_distance_to_plane(center) > -r;
}

bool AABB::is_on_frustum(const Frustum& frustrum) const 
{
    return (check_plane(frustrum.bottom_face) &&
            check_plane(frustrum.top_face) &&
            check_plane(frustrum.far_face) &&
            check_plane(frustrum.near_face) &&
            check_plane(frustrum.right_face) &&
            check_plane(frustrum.left_face));
}

void FrustumCulling::update(const Camera& camera, float aspect, float fov_y, float z_near, float z_far)
{
    const float half_v_side = z_far * tanf(fov_y * 0.5f);
    const float half_h_side = half_v_side * aspect;
    const glm::vec3 front_mult_far = z_far * camera.front;

    m_frustum.near_face = { camera.position + z_near * camera.front, camera.front };
    m_frustum.far_face = { camera.position + front_mult_far, -camera.front };
    m_frustum.right_face = { camera.position, glm::cross(camera.up, front_mult_far - camera.right * half_h_side) };
    m_frustum.left_face = { camera.position, glm::cross(front_mult_far + camera.right * half_h_side, camera.up) };
    m_frustum.top_face = { camera.position, glm::cross(camera.right, front_mult_far - camera.up * half_v_side) };
    m_frustum.bottom_face = { camera.position, glm::cross(front_mult_far + camera.up * half_v_side, camera.right) };
} 

bool FrustumCulling::is_visible(const AABB& aabb) const 
{
    return aabb.is_on_frustum(m_frustum);
}

bool FrustumCulling::is_visible(const glm::vec3& block_position) const 
{
    AABB block_aabb(block_position);
    return is_visible(block_aabb);
}