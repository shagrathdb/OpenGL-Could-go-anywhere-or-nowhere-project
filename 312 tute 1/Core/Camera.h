/**
 * @class Camera
 * @brief OpenGL first person camera class.
 *
 * TODO: Change from static class to singleton for use with MouseListener.
 *
 * @author Simon Manning
 * @version 0.2
 * @date 07-04-2011
 */

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../utility/Vec3f.h"
#include "../utility/Mat4f.h"
#include "../input/MouseListener.h"
#include "../includes.h"



class Camera : public MouseListener
{
  public:    
    /** Constructor. */
    Camera();
    
    /** Destructor. */
    ~Camera();
    
    /** Reset camera values. */
    static void Clear();
    
    /** Update view matrix. */
    static void Update(bool orth);

    /** Rotation/mouse look. */
    static void Rotate(float yawDeg, float pitchDeg);
    
    /** MouseListener callbacks */
    void MotionEvent(int x, int y);
    void ClickEvent(MouseButton mb, int x, int y);
    void ReleaseEvent(MouseButton mb, int x, int y);
    
    static void Perspective(float fovY, float ratio, float zNear, float zFar);
    static void LookAt(const Vec3f& pos, const Vec3f& target, Vec3f& up);
    
	void SetPos(Vec3f& pos) { eye = pos; }

    /** Set and get mouse sensitivity */
    static void SetSensitivity(float sens);
    static float GetSensitivity();

    Mat4f& GetVM() const;
    Mat4f& GetPM() const;
	Vec3f GetTgt();
    static void SetScreenCoords(int w, int h);
    static int GetWindowW() { return m_screenWidth; }
    static int GetWindowH() { return m_screenHeight; }
    
    static Vec3f& GetPos();
    static Vec3f& GetView();

	/** Temp */
	static void Move(const GLfloat distance);
	void Strafe(const GLfloat distance);
  private:
    static Vec3f eye;
    static Vec3f view;
    static Vec3f xAxis;
    static Vec3f yAxis;
    static Vec3f zAxis;
    
    static Mat4f viewMatrix;
    static Mat4f projMatrix;
    
    static float accumPitch;
    
    static const Vec3f WorldY;
    
    static int m_mouseLastX;
    static int m_mouseLastY;
    
    static float m_sensitivity;

    static int m_screenWidth;
    static int m_screenHeight;

	static bool m_attached;
};

// Global function for accessing SetSensitivity from cmdsys
void Sensitivity_f();

#endif
