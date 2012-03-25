/**
 * @class MouseListener
 * @brief Handles mouse input using MouseListener class and GLUT callbacks.
 *
 * Uses an abstract base class (MouseListener) to provide an interface that
 * receives notifications about the state of the mouse and provides virtual
 * methods to define event-driven behaviour (when mouse is moved/clicked).
 *
 * @author Simon Manning <simon@ecksd.com>
 * @version 0.1
 * @date 16-03-2011
 */

#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

#include <set>


enum MouseButton
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

class MouseListener
{
  public:
    /** Base constructor: adds object to list of MouseListener objects. */
    MouseListener();
    
    /** Destructor: removes object from list. */
    virtual ~MouseListener();
    
    /**
     * Mouse movement callback.
     * @param x New mouse X coordinate.
     * @param y New mouse Y coordinate.
     */
    virtual void MotionEvent(int x, int y) {}
    
    /**
     * Mouse click callback.
     * @param x New mouse X coordinate.
     * @param y New mouse Y coordinate.
     */
    virtual void ClickEvent(MouseButton button, int x, int y) {}

    /**
     * Mouse release callback.
     * @param x New mouse X coordinate.
     * @param y New mouse Y coordinate.
     */
    virtual void ReleaseEvent(MouseButton button, int x, int y) {}    
};

#endif