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
        //void Update(float dt); // Obs³uga wejœcia lub œledzenia lokomotywy
        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();

        void RotateX(float angle);
        void RotateY(float angle);
        void RotateZ(float angle);

        void setHAngle(float angle);
        void setVAngle(float angle);

        void deltaHAngle(float angle);
        void deltaVAngle(float angle);

        void deltaZoom(float delta);

        void ShowParams();
        //lm::mat4 GetViewMatrix() const;

        //void SetPerspective(float fovDeg, float aspect, float near, float far);
        //void SetOrthographic(...); // jeœli chcesz tryb orto

        //void SetPosition(...);     // itd.

    private:
        glm::vec3 position;
        glm::vec3 lookPoint;
        glm::vec3 upDirection;

        float fov, aspect, nearPlane, farPlane;

        float zoom; 
        float hAngle;
        float vAngle;

        glm::mat4 M;
};
