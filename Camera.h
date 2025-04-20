#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera
{
    public:
        Camera();
        //void Update(float dt); // Obs�uga wej�cia lub �ledzenia lokomotywy
        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();

        //lm::mat4 GetViewMatrix() const;

        //void SetPerspective(float fovDeg, float aspect, float near, float far);
        //void SetOrthographic(...); // je�li chcesz tryb orto

        //void SetPosition(...);     // itd.

    private:
        glm::vec3 position;
        glm::vec3 lookPoint;
        glm::vec3 upDirection;

        float fov, aspect, nearPlane, farPlane;
};
