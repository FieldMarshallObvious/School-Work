#include "Camera.h"
#include <math.h>

Camera::Camera()
 :fov(0), aspectRatio(0), nearPlane(0), farPlane(0),
  posistion(0, 0, 0), rotation(0, 0, 0),
  viewMatrix(), projMatrix()
{
    calculateViewMatrix();
}

Camera::~Camera(){}

void Camera::createProjection( float inputfov, float inputAspectRatio, float inputNearPlane, float inputFarPlane )
{   
    projMatrix.setIdentity();

    float tanhfov = (float)tanf(inputfov / 2);

    projMatrix.m00 = 1 / (inputAspectRatio * tanhfov);
    projMatrix.m11 = 1 / tanhfov;
    projMatrix.m22 = -(inputNearPlane + inputFarPlane ) / ( inputFarPlane - inputNearPlane );
    projMatrix.m23 = -1;
    projMatrix.m32 = -(2 * inputFarPlane * inputFarPlane ) / ( inputFarPlane - inputNearPlane );

}