/**
 * @file camera.cpp
 * @brief Camera class implementation file
 * @author Simon Manning
 * @version 0.2
 * @date 07-04-2011
 *
 * TODO: Make m_sensitivity accessible as a cvar for changing
 * via (maybe)menus and (definitely)console.
 * At the moment it's done a dirty way. Will be changed when
 * I create a proper system for storing, using and changing client
 * variables, like sensitivity, fov, zoomfov, etc.
 */

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "../core/Camera.h"
#include "../includes.h"


/* Constants and static declarations */
const Vec3f Camera::WorldY(0.0f, 1.0f, 0.0f);

Vec3f Camera::eye   = Vec3f(0.0, 0.0, 0.0);
Vec3f Camera::xAxis = Vec3f(1.0, 0.0, 0.0);
Vec3f Camera::yAxis = Vec3f(0.0, 1.0, 0.0);
Vec3f Camera::zAxis = Vec3f(0.0, 0.0, 1.0);
Vec3f Camera::view  = Vec3f(0.0, 0.0, -1.0);

Mat4f Camera::viewMatrix = Mat4f::IMatrix;
Mat4f Camera::projMatrix = Mat4f::IMatrix;

float Camera::accumPitch = 0;

int Camera::m_mouseLastX = 0;
int Camera::m_mouseLastY = 0;
float Camera::m_sensitivity = 3.0f;

int Camera::m_screenWidth = 0;
int Camera::m_screenHeight = 0;

bool Camera::m_attached = true;

Camera::Camera()
{
    Clear();

    // TODO: move. register sens command to cmd sys
	CmdSys::Instance()->AddCmd("sensitivity", Sensitivity_f);
}

Camera::~Camera()
{
    Clear();
}

void Camera::Clear()
{
    eye   = Vec3f(0.0, 0.0, 0.0);
    xAxis = Vec3f(1.0, 0.0, 0.0);
    yAxis = Vec3f(0.0, 1.0, 0.0);
    zAxis = Vec3f(0.0, 0.0, 1.0);
    view  = Vec3f(0.0, 0.0, 1.0);
    
    viewMatrix.Identity();
    projMatrix.Identity();
    
    m_mouseLastX = 0;
    m_mouseLastY = 0;
    
    m_sensitivity = 3.0f;
}

void Camera::SetScreenCoords(int w, int h)
{
    m_screenWidth = w;
    m_screenHeight = h;
}

void Camera::Update(bool orth)
{
    if (orth)
    {
        zAxis.Normalise();
        yAxis = Vec3f::Cross(zAxis, xAxis);
        yAxis.Normalise();
        xAxis = Vec3f::Cross(yAxis, zAxis);
        xAxis.Normalise();
        
        view = -zAxis;
    }
    
    viewMatrix[0][0] = xAxis.x;
    viewMatrix[0][1] = yAxis.x;
    viewMatrix[0][2] = zAxis.x;
    viewMatrix[0][3] = 0.0f;

    viewMatrix[1][0] = xAxis.y;
    viewMatrix[1][1] = yAxis.y;
    viewMatrix[1][2] = zAxis.y;
    viewMatrix[1][3] = 0.0f;

    viewMatrix[2][0] = xAxis.z;
    viewMatrix[2][1] = yAxis.z;
    viewMatrix[2][2] = zAxis.z;
    viewMatrix[2][3] = 0.0f;

    viewMatrix[3][0] = Vec3f::Dot(-xAxis, eye);
    viewMatrix[3][1] = Vec3f::Dot(-yAxis, eye);
    viewMatrix[3][2] = Vec3f::Dot(-zAxis, eye);
    viewMatrix[3][3] = 1.0f;
}

void Camera::MotionEvent(int x, int y)
{
    bool chX = false;
    bool cl_mfilter = true;

    // TODO: globalise these cvars for modification
    static float m_yaw = 0.022;
    static float m_pitch = 0.022;

    int centreX = m_screenWidth / 2;
    int centreY = m_screenHeight / 2;

    float xDiff = m_mouseLastX - x; //* m_sensitivity * m_yaw;
    float yDiff = m_mouseLastY - y; //* m_sensitivity * m_pitch;

    // TODO: mouse filtering idea (smoother movement)
    // temp name, need to globalise vars
    // if (cl_mfilter)
    // xdiff = lastdiff + thisdiff * 0.5
    // ydiff = lastdiff + thisdiff * 0.5

    xDiff *= m_sensitivity;
    yDiff *= m_sensitivity;

    xDiff *= m_yaw;
    yDiff *= m_pitch;

    m_mouseLastX = x;
    m_mouseLastY = y;

    Rotate(xDiff, yDiff);


	{
		m_attached = true;

		glutSetCursor(GLUT_CURSOR_NONE);
	}

    #ifndef __APPLE__
    if ((x - centreX) > 10 || (x - centreX) < -10)
    {
        chX = true;

		glutWarpPointer(centreX, y);
        m_mouseLastX = centreX;
    }

    if ((y - centreY) > 10 || (y - centreY) < -10)
    {
        if (chX) glutWarpPointer(centreX, centreY);
        else glutWarpPointer(x, centreY);
        m_mouseLastY = centreY;
    }
    #endif
}

void Camera::ClickEvent(MouseButton mb, int x, int y)
{
    
}

void Camera::ReleaseEvent(MouseButton mb, int x, int y)
{
    
}

void Camera::Move(const GLfloat distance)
{
    eye -= zAxis * distance;
    
    Update(false);
}

void Camera::Strafe(const GLfloat distance)
{
    eye += xAxis * distance;
    
    Update(false);
}

void Camera::Rotate(float yawDeg, float pitchDeg)
{
    Mat4f rotation;
    
    accumPitch += pitchDeg;
    
    if (accumPitch > 90.0f)
    {
        pitchDeg = 90.0f - (accumPitch - pitchDeg);
        accumPitch = 90.0f;
    }

    if (accumPitch < -90.0f)
    {
        pitchDeg = -90.0f - (accumPitch - pitchDeg);
        accumPitch = -90.0f;
    }
    
    if (yawDeg != 0.0f)
    {
        rotation.Rotate(WorldY, yawDeg);
        xAxis = xAxis * rotation;
        zAxis = zAxis * rotation;
    }
    
    if (pitchDeg != 0.0f)
    {
        rotation.Rotate(xAxis, pitchDeg);
        yAxis = yAxis * rotation;
        zAxis = zAxis * rotation;
    }
}

void Camera::Perspective(float fovY, float ratio, float zNear, float zFar)
{
    float xymax = zNear * tan(fovY * (3.14159265358f / 360.0f));
    float ymin = -xymax;
    float xmin = -xymax;

    float width = xymax - xmin;
    float height = xymax - ymin;

    float depth = zFar - zNear;
    float q = -(zFar + zNear) / depth;
    float qn = -2 * (zFar * zNear) / depth;

    float w = 2 * zNear / width;
    w = w / ratio;
    float h = 2 * zNear / height;

    projMatrix[0][0]  = w;
    projMatrix[0][1]  = 0;
    projMatrix[0][2]  = 0;
    projMatrix[0][3]  = 0;

    projMatrix[1][0]  = 0;
    projMatrix[1][1]  = h;
    projMatrix[1][2]  = 0;
    projMatrix[1][3]  = 0;

    projMatrix[2][0]  = 0;
    projMatrix[2][1]  = 0;
    projMatrix[2][2] = q;
    projMatrix[2][3] = -1;

    projMatrix[3][0] = 0;
    projMatrix[3][1] = 0;
    projMatrix[3][2] = qn;
    projMatrix[3][3] = 0;
}
Vec3f tgt;

Vec3f Camera::GetTgt()
{

	return eye-zAxis;
}

void Camera::LookAt(const Vec3f& pos, const Vec3f& target, Vec3f& up)
{
    eye = pos;

    zAxis = eye - target;
    zAxis.Normalise();

    view = -zAxis;

    xAxis = Vec3f::Cross(up, zAxis);
    xAxis.Normalise();

    yAxis = Vec3f::Cross(zAxis, xAxis);
    yAxis.Normalise();
    xAxis.Normalise();

    viewMatrix[0][0] = xAxis.x;
    viewMatrix[1][0] = xAxis.y;
    viewMatrix[2][0] = xAxis.z;
    viewMatrix[3][0] = Vec3f::Dot(-xAxis, eye);

    viewMatrix[0][1] = yAxis.x;
    viewMatrix[1][1] = yAxis.y;
    viewMatrix[2][1] = yAxis.z;
    viewMatrix[3][1] = Vec3f::Dot(-yAxis, eye);

    viewMatrix[0][2] = zAxis.x;
    viewMatrix[1][2] = zAxis.y;
    viewMatrix[2][2] = zAxis.z;    
    viewMatrix[3][2] = Vec3f::Dot(-zAxis, eye);

    accumPitch = ((-asinf(viewMatrix[1][2])) * 180.0f) / 3.14159265358f;
}

Mat4f& Camera::GetVM() const
{
    return viewMatrix;
}

Mat4f& Camera::GetPM() const
{
    return projMatrix;
}

Vec3f& Camera::GetPos()
{
    return eye;
}

Vec3f& Camera::GetView()
{
    return view;
}

void Camera::SetSensitivity(float sens)
{
    m_sensitivity = sens;
}

float Camera::GetSensitivity()
{
    return m_sensitivity;
}


// Global function for modifying sensitivity in console
void Sensitivity_f()
{
	if (CmdSys::Instance()->Argc() == 0)
    {
        float sens = Camera::GetSensitivity();
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        ss << sens;
        std::string out = "sensitivity is: ";
        out += ss.str();
        return;
    }
    else
    {
        //float sens = atof(_cs->Argv().at(0).c_str()); // C-way
        // C++ way
        float sens;
        std::stringstream ss(CmdSys::Instance()->Argv().at(0).c_str());
        ss >> sens;
        Camera::SetSensitivity(sens);
    }
}