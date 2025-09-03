#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Camera.h>
#include <Block.h>

#include <memory>
#include <array>

struct Plane 
{
    glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
    float distance = 0.0f;

    Plane() = default;

    Plane(const glm::vec3& p1, const glm::vec3& norm);
    float get_signed_distance_to_plane(const glm::vec3& point) const;
};

struct Frustum 
{
    Plane top_face;
    Plane bottom_face;

    Plane right_face;
    Plane left_face;

    Plane far_face;
    Plane near_face;
};

struct AABB 
{
    glm::vec3 min;
    glm::vec3 max;

    AABB(const glm::vec3& position);
    AABB(const glm::vec3& min, const glm::vec3& max);
    
    glm::vec3 get_center() const;
    glm::vec3 get_extents() const;

    bool check_plane(const Plane& plane) const;
    bool is_on_frustum(const Frustum& frustrum) const;
};

class FrustumCulling 
{
    private:
        Frustum m_frustum;

    public:
        void update(const Camera& camera, float aspect, float fov_y, float z_near, float z_far);
        bool is_visible(const AABB& aabb) const;
        bool is_visible(const glm::vec3& block_position) const;
};