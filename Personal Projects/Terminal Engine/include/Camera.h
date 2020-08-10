#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

class Camera
{
    private:
        Vector3 posistion;
        Vector3 rotation;

        Matrix44 viewMatrix;
        Matrix44 projMatrix;


        float fov, aspectRatio, nearPlane, farPlane;
    public:
        Camera();
        ~Camera();

        inline Vector3& getPosition(){ return posistion; }
        inline Vector3& getRotation(){ return rotation; }

        inline void calculateViewMatrix()
        {
            viewMatrix.setIdentity();
            viewMatrix.rotate(Vector3(1, 0, 0), rotation.getX());
            viewMatrix.rotate(Vector3(0, 1, 0), rotation.getY());
            viewMatrix.rotate(Vector3(0, 0, 1), rotation.getZ());
            viewMatrix.translate(posistion);
        }

        inline Matrix44 getPVMatrix()
        { 
            return projMatrix  * viewMatrix; 
        }
        void createProjection( float inputfov, float inputspectRatio, float inputNearPlane, float inputFarPlane );
};



#endif