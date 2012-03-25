#include "../input/Bindings.h"
#include "../core/CmdSys.h"
#include "../input/InputListeners.h"

Bindings* Bindings::m_instance = NULL;

Bindings::Bindings()
{
    // Add the binding system commands to the cmd sys
    CmdSys::Instance()->AddCmd("bind", Bind_f);
    CmdSys::Instance()->AddCmd("unbind", Unbind_f);
}

Bindings::~Bindings()
{
	delete m_instance;
}

Bindings* Bindings::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Bindings();
	}

	return m_instance;
}

void Bindings::BindMouse(MouseButton mb, const std::string& cmd)
{
    std::map<MouseButton, std::string>::iterator itr = m_mouseBinds.find(mb);

    if (itr != m_mouseBinds.end())
    {
        UnbindMouse(mb);
    }
    
    m_mouseBinds.insert(std::map<MouseButton, std::string>::value_type(mb, cmd));
    m_mouseWait[mb] = false;
}

void Bindings::UnbindMouse(MouseButton mb)
{
    std::map<MouseButton, std::string>::iterator itr;

	itr = m_mouseBinds.find(mb);
	if (itr == m_mouseBinds.end())
	{
		return;
	}

	m_mouseBinds.erase(itr);
}

void Bindings::ClickEvent(MouseButton button, int x, int y)
{
    if (m_mouseWait[button]) return;

	std::map<MouseButton, std::string>::iterator itr;

	itr = m_mouseBinds.find(button);

	if (itr == m_mouseBinds.end())
	{
		return;
	}

	CmdSys::Instance()->QueueCmd(itr->second);

	if (itr->second.at(0) != '+') m_mouseWait[button] = true;
	else
	{
		m_mouseHeldKey[button] = true;
	}
}

void Bindings::ReleaseEvent(MouseButton button, int x, int y)
{
    m_mouseHeldKey[button] = false;

	m_mouseWait[button] = false;

    // Handle '-' binds
    std::map<MouseButton, std::string>::iterator it;
    it = m_mouseBinds.find(button);

	if (it == m_mouseBinds.end())
	{
		return;
	}

    if (it->second.at(0) == '+')
    {
        std::string cmd = it->second;
        cmd.at(0) = '-';
        CmdSys::Instance()->QueueCmd(cmd);
    }
}

void Bindings::BindKey(unsigned char key, const std::string& cmd)
{
	std::map<char, std::string>::iterator itr = m_binds.find(key);

	if (itr != m_binds.end())
	{
		UnbindKey(key);
	}

	m_binds.insert(std::map<char, std::string>::value_type(key, cmd));
	m_waiting[(int)key] = false;
}

void Bindings::UnbindKey(unsigned char key)
{
	std::map<char, std::string>::iterator itr;

	itr = m_binds.find(key);
	if (itr == m_binds.end())
	{
		return;
	}

	m_binds.erase(itr);
}

void Bindings::KeyDown(unsigned char key, int x, int y)
{
    if (m_waiting[(int)key]) return;

	std::map<char, std::string>::iterator itr;

	itr = m_binds.find(key);

	if (itr == m_binds.end())
	{
		return;
	}


	if (itr->second.at(0) != '+') m_waiting[(int)key] = true;
	else
	{
		std::map<char, bool>::iterator it;
		it = m_heldKey.find(key);

		if (it != m_heldKey.end())
		{
			it->second = true;
		}
		else
		{
			m_heldKey[key] = true;
		}
	}
}

void Bindings::KeyUp(unsigned char key, int x, int y)
{
	std::map<char, bool>::iterator itr;
	itr = m_heldKey.find(key);

	if (itr != m_heldKey.end())
	{
		itr->second = false;
	}

	m_waiting[(int)key] = false;

    // Handle '-' binds
    std::map<char, std::string>::iterator it;
    it = m_binds.find(key);

	if (it == m_binds.end())
	{
		return;
	}

    if (it->second.at(0) == '+')
    {
        std::string cmd = it->second;
        cmd.at(0) = '-';
        CmdSys::Instance()->QueueCmd(cmd);
    }
}

void Bindings::SpecialDown(unsigned char key, int x, int y)
{

}

void Bindings::SpecialUp(unsigned char key, int x, int y)
{

}

void Bindings::DoKeyBind(unsigned char key)
{

    std::map<char, std::string>::iterator itr;
	itr = m_binds.find(key);

	if (itr == m_binds.end())
	{
		return;
	}

	CmdSys::Instance()->QueueCmd(itr->second);
}

const std::string Bindings::GetKeyBind(unsigned char key)
{
	std::map<char, std::string>::iterator itr;
	itr = m_binds.find(key);

	if (itr == m_binds.end())
	{
		return std::string("NULL");
	}

	return itr->second;
}

void Bindings::Update()
{
    if (m_heldKey.empty()) return;

	std::map<char, bool>::iterator it;

	for (it = m_heldKey.begin(); it != m_heldKey.end(); it++)
	{
		if (it->second) DoKeyBind(it->first);
	}
}
	
/**
 * Global functions
 *
 * Required for linking Binding system functions to cmdsys.
 */

void Bind_f()
{
    // e.g. 'bind' on its own
	if (CmdSys::Instance()->Argc() == 0)
    {
		return;
    }

	// e.g. 'bind w'
	if (CmdSys::Instance()->Argc() == 1)
	{
        char key = CmdSys::Instance()->Argv().at(0).at(0);
		std::string bind = Bindings::Instance()->GetKeyBind(key);
		
		if (bind == "NULL")
		{
			std::string tmp = "bind: ";
			std::string keystr = " ";
			keystr.at(0) = key; 
			tmp.append(keystr);
			tmp.append(" is unbound");
			return;
		}

		std::string tmp = "bind: ";
		std::string keystr = " ";
		keystr.at(0) = key; 
		tmp.append(keystr);
		tmp.append(" bound to ");
		tmp.append(bind);
        return;
	}

	// e.g. 'bind w +forward'
	// e.g. 'bind e cam_fov 100'
    if (CmdSys::Instance()->Argv().at(0).length() == 1 || CmdSys::Instance()->Argv().at(0) == "space")
    {
        char key = CmdSys::Instance()->Argv().at(0).at(0);
	    std::string bind;
	    for (size_t i = 1; i < CmdSys::Instance()->Argv().size(); i++)
	    {
		    bind.append(CmdSys::Instance()->Argv().at(i));
            bind.append(" ");
	    }
        if (CmdSys::Instance()->Argv().at(0) == "space")
        {
            Bindings::Instance()->BindKey(' ', bind);
        }
        else
        {
	        Bindings::Instance()->BindKey(key, bind);
        }
    }
    else /* Handle mouse binds */
    {
        MouseButton mb;
		if (CmdSys::Instance()->Argv().at(0) == "mouse1")
			mb = MOUSE_LEFT;
		if (CmdSys::Instance()->Argv().at(0) == "mouse2")
			mb = MOUSE_RIGHT;
		if (CmdSys::Instance()->Argv().at(0) == "mouse3")
			mb = MOUSE_MIDDLE;

        std::string bind;
        for (size_t i = 1; i < CmdSys::Instance()->Argv().size(); i++)
	    {
		    bind.append(CmdSys::Instance()->Argv().at(i));
            bind.append(" ");
	    }
        
        Bindings::Instance()->BindMouse(mb, bind);
    }
}


void Unbind_f()
{
    if (CmdSys::Instance()->Argc() == 0)
    {
		return;
    }

    if (CmdSys::Instance()->Argv().at(0).length() == 1)
        Bindings::Instance()->UnbindKey(CmdSys::Instance()->Argv().at(0).at(0));
    else if (CmdSys::Instance()->Argv().at(0) == "space")
        Bindings::Instance()->UnbindKey(' ');
    else
    {
        MouseButton mb;
        if (CmdSys::Instance()->Argv().at(0) == "mouse1")
            mb = MOUSE_LEFT;
        if (CmdSys::Instance()->Argv().at(0) == "mouse2")
            mb = MOUSE_RIGHT;
        if (CmdSys::Instance()->Argv().at(0) == "mouse3")
            mb = MOUSE_MIDDLE;

        Bindings::Instance()->UnbindMouse(mb);
    }
}