
#include "KeysListener.h"
#include "InputListeners.h"

KeysListener::KeysListener()
{
    m_ignoreRepeat = false;
    RegisterKeysListener(this);
}

KeysListener::~KeysListener()
{
    DeregisterKeysListener(this);
}

bool KeysListener::IgnoreRepeat()
{
	return m_ignoreRepeat;
}