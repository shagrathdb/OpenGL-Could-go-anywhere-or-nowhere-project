#include "../includes.h"
#include <set>
#include <iterator>
#include <iostream>

#include "../input/MouseListener.h"
#include "../input/InputListeners.h"


MouseListener::MouseListener()
{
    RegisterMouseListener(this);
}

MouseListener::~MouseListener()
{
    DeregisterMouseListener(this);
}
