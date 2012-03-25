#include "MenuSystem.h"
#include "../Global/Global.h"

#include <iostream>

using namespace Honir::Global;

namespace Honir {
namespace Core {

MenuSystem::MenuSystem()
{
    Init();
}

MenuSystem::MenuSystem(int width, int height)
{
    Init();
    m_width  = width;
    m_height = height;
}

MenuSystem::~MenuSystem()
{
    //
}

void MenuSystem::Init()
{
    // Signifies to KeysListener system to ignore repeating keys
    m_ignoreRepeat = true;

    m_width     = 500;
    m_height    = 500;
    m_active    = false;
    m_selection = m_funcs.end();
    m_selectIndex = 0;

    m_prompt    = "---> ";
    m_gap       = "     ";
}

void MenuSystem::Process()
{
    if (!m_active) return;

    DrawBase();

    if (m_title.size() == 0) return;
    
    int centreX = _window->width / 2;
	int centreY = _window->height / 2;
	Vec2f temp = _fr->GetFontExtents(m_title, "Inconsolata");

    int posX = centreX - (temp.x / 2);
	int posY = centreY - (m_height / 2) + (temp.y + 10) ; //+ temp.y;

    // Draw title
	_hr->colour(1.0, 1.0, 1.0, 1.0);
    Vec2f size = _fr->RenderText(m_title, "Inconsolata", posX, posY, 0.0f);
    posY += (size.y * 3);
	posX = centreX - (m_width / 2) + (_window->width / 128);
    if (m_funcs.empty()) return;

    std::map<std::string, Fn_t>::iterator itr = m_order.at(0);

    // Draw each menu selection string
    for (int i = 0; i < m_order.size(); i++)
    {
        std::string temp = "";

        if (m_selection == m_order[i])
        {
			temp.append(m_prompt);
        }
        else
        {
            temp.append(m_gap);
        }

        temp.append(m_order[i]->first);

        _fr->RenderText(temp, "Inconsolata", posX, posY, 0.0f);
        posY += (size.y + 5);
    }
}

void MenuSystem::KeyDown(unsigned char key, int, int)
{
	if (!m_active)
    {
		if ((int)key == 27) m_active = true;
        return;
    }

    if ((int)key == 27) m_active = false;
    
    if ((int)key == 13 && m_selection != m_funcs.end())
    {
        m_selection->second();
        m_active = false;
    }
}

void MenuSystem::SpecialDown(unsigned char key, int, int)
{
	if (!m_active) return;
    if (m_funcs.empty()) return;

    if (key == GLUT_KEY_UP)
    {
		if (m_selection == m_order[0]) return;

        m_selectIndex--;
        m_selection = m_order[m_selectIndex];
    }

    if (key == GLUT_KEY_DOWN)
    {
		if (m_selection == m_order[m_order.size() - 1]) return;

        m_selectIndex++;
        m_selection = m_order[m_selectIndex];
    }
}

void MenuSystem::DrawBase()
{
    int centreX = _window->width  / 2;
    int centreY = _window->height / 2;

	_hr->matrixMode(MatrixModes::MM_PROJECTION);
	_hr->pushMatrix();
	_hr->loadIdentity();
	_hr->ortho2d(0.0f, static_cast<float>(_window->width), 0.0f, 
            static_cast<float>(_window->height));
    
	_hr->matrixMode(MatrixModes::MM_MODELVIEW);
	_hr->pushMatrix();
	_hr->loadIdentity();

	_hr->disable(StateModifiers::SM_DEPTH_TEST);

    _hr->blendFunc(Blend::B_SRC_ALPHA, Blend::B_ONE_MINUS_SRC_ALPHA);
    _hr->enable(StateModifiers::SM_BLEND);

	_hr->colour(0.0, 0.0, 0.0, 0.70f);

	_hr->translate(centreX, centreY, 0.0);
	_hr->scale(m_width / 2, m_height / 2, 0.0);
	_hr->begin(ObjectTypes::POLYGON);
		_hr->vertex2f(1.0f, 1.0f);
		_hr->vertex2f(-1.0f, 1.0f);
		_hr->vertex2f(-1.0f, -1.0f);
		_hr->vertex2f(1.0f, -1.0f);
    _hr->end();
	
    _hr->disable(StateModifiers::SM_BLEND);
	_hr->enable(StateModifiers::SM_DEPTH_TEST);
	_hr->popMatrix();
	_hr->matrixMode(MatrixModes::MM_PROJECTION);
	_hr->popMatrix();
}

void MenuSystem::SetTitle(std::string n)
{
    m_title = n;
}

void MenuSystem::AddFunction(std::string name, Fn_t func)
{
    // Check selection isn't already registered first
    std::map<std::string, Fn_t>::iterator itr = m_funcs.find(name);
    if (itr != m_funcs.end())
    {
        std::cerr << "MenuSystem: selection already registered" << std::endl;
        return;
    }
    
    // Command not registered, so add to map
    m_funcs.insert(std::map<std::string, Fn_t>::value_type(name, func));
    m_order.push_back(m_funcs.find(name));
    // If we don't have a selection yet, set it to this one
    if (m_selection == m_funcs.end())
    {
        itr = m_funcs.find(name);
        m_selection = itr;
        m_selectIndex = 0;
    }
}

void MenuSystem::SetDimensions(int width, int height)
{
    m_width  = width;
    m_height = height;
}
}
}
