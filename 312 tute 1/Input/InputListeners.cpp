#include "../input/InputListeners.h"

std::set<MouseListener*> g_mouseListeners;
std::set<KeysListener*>  g_keysListeners;
int g_MouseLocX;
int g_MouseLocY;
bool g_keyWaiting[256];
bool g_sKeyWaiting[256];

void RegisterMouseListener(MouseListener* mListener)
{
    g_mouseListeners.insert(mListener);
}

void DeregisterMouseListener(MouseListener* mListener)
{
    std::set<MouseListener*>::iterator i = g_mouseListeners.find(mListener);

    if (i != g_mouseListeners.end()) 
    {
        g_mouseListeners.erase(i);
    }
}

void RegisterKeysListener(KeysListener* kl)
{
    g_keysListeners.insert(kl);
}

void DeregisterKeysListener(KeysListener* kl)
{
    std::set<KeysListener*>::iterator i = g_keysListeners.find(kl);

    if (i != g_keysListeners.end()) 
    {
        g_keysListeners.erase(i);
    }
}

void MouseClick(int button, int state, int x, int y)
{
    MouseButton mb;
    
    if (button == GLUT_LEFT_BUTTON)
    {
        mb = MOUSE_LEFT;
    }
    else if (button == GLUT_MIDDLE_BUTTON) 
    {
        mb = MOUSE_MIDDLE;
    }
    else
    {
        mb = MOUSE_RIGHT;
    }

    // Loop through mouse listeners and call event function
    std::set<MouseListener*>::iterator i = g_mouseListeners.begin();
    while (i != g_mouseListeners.end())
    {
        if (state == GLUT_DOWN)
        {
            (*i)->ClickEvent(mb, g_MouseLocX, g_MouseLocY);
        }
        else
        {
            (*i)->ReleaseEvent(mb, g_MouseLocX, g_MouseLocY);
        }

        i++;
    }

}

void MouseMotion(int x, int y)
{
    g_MouseLocX = x;
    g_MouseLocY = y;

    std::set<MouseListener*>::iterator i = g_mouseListeners.begin();
    while (i != g_mouseListeners.end())
    {
        (*i)->MotionEvent(x, y);
        i++;
    }
}

void KeyDn(unsigned char key, int x, int y)
{
    // Loop through mouse listeners and call event function
    std::set<KeysListener*>::iterator i = g_keysListeners.begin();
    while (i != g_keysListeners.end())
    {
        if (g_keyWaiting[(int)key])
        {
            if (!(*i)->IgnoreRepeat())
            {
                (*i)->KeyDown(key, x, y);
            }
        }
        else
        {
            (*i)->KeyDown(key, x, y);
        }

        i++;
    }
	
    g_keyWaiting[(int)key] = true;
}

void KeyUp(unsigned char key, int x, int y)
{
    g_keyWaiting[(int)key] = false;
    // Loop through mouse listeners and call event function
    std::set<KeysListener*>::iterator i = g_keysListeners.begin();
    while (i != g_keysListeners.end())
    {
        (*i)->KeyUp(key, x, y);

        i++;
    }
}

void SKeyDn(int key, int x, int y)
{
	// Loop through mouse listeners and call event function
    std::set<KeysListener*>::iterator i = g_keysListeners.begin();
    while (i != g_keysListeners.end())
    {
        if (g_sKeyWaiting[key])
        {
            if (!(*i)->IgnoreRepeat()) 
            {
                (*i)->SpecialDown(key, x, y);
            }
        }
        else
        {
            (*i)->SpecialDown(key, x, y);
        }

        i++;
    }
    g_sKeyWaiting[key] = true;
}

void SKeyUp(int key, int x, int y)
{
    g_sKeyWaiting[key] = false;
    // Loop through mouse listeners and call event function
    std::set<KeysListener*>::iterator i = g_keysListeners.begin();
    while (i != g_keysListeners.end())
    {
        (*i)->SpecialUp(key, x, y);

        i++;
    }
}
