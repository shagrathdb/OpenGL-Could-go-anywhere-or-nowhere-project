/**
 * Global functions and data structures for input listener classes.
 */

#ifndef _INPUTLISTENERS_H_
#define _INPUTLISTENERS_H_

#include "../input/MouseListener.h"
#include "../input/KeysListener.h"
#include "../includes.h"

#include <set>


extern std::set<MouseListener*> g_mouseListeners;
extern std::set<KeysListener*>  g_keysListeners;
extern int g_MouseLocX;
extern int g_MouseLocY;
extern bool g_keyWaiting[256];
extern bool g_sKeyWaiting[256];

void RegisterMouseListener(MouseListener* mListener);

void DeregisterMouseListener(MouseListener* mListener);

void RegisterKeysListener(KeysListener* kl);

void DeregisterKeysListener(KeysListener* kl);

void MouseClick(int button, int state, int x, int y);

void MouseMotion(int x, int y);

void KeyDn(unsigned char key, int x, int y);

void KeyUp(unsigned char key, int x, int y);

void SKeyDn(int key, int x, int y);

void SKeyUp(int key, int x, int y);

#endif
