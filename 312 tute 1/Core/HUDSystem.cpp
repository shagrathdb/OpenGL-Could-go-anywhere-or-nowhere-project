#include "HUDSystem.h"
#include "../AI/LuaHelper.h"
#include "../Global/Global.h"
#include <sstream>

using namespace Honir::Global;

HUDSystem* HUDSystem::m_instance = NULL;

HUDSystem::HUDSystem()
{
    m_wonGame = false;
    m_lostGame = false;
}

HUDSystem::~HUDSystem()
{
    delete m_instance;
}

HUDSystem* HUDSystem::Instance()
{
    if (m_instance == NULL)
    {
        m_instance = new HUDSystem();
    }

    return m_instance;
}

void HUDSystem::Init()
{
    // Open Lua
    lua_State *L = lua_open();
    if (L == NULL)
    {
        std::cout << "Lua: failed to lua_open()." << std::endl;
        return;
    }
    luaL_openlibs(L);

    // Run script
    luaL_dofile(L, "resource/HUD/crosshair.lua");
    
    std::string xhFile = PopLuaString(L, "crosshairImage");

	lua_close(L);

    _tm->newTexture("crosshair", TextureTypes::TEX_2D, xhFile, -1, -1, -1, -1);

    _fr->RegisterFont("resource/fonts/Inconsolata.otf", 50, "HUDScoreFont");

    Vec2f sc;
    sc.x = 0.0f;
    sc.y = 0.0f;
    std::string score = "999";
    std::string health = "health  ";
    std::string win = "YOU WON THE GAME!";
    m_numExtents = _fr->GetFontExtents(score, "HUDScoreFont");
    m_winLoc = _fr->GetFontExtents(win, "HUDScoreFont");
    sc = _fr->GetFontExtents(health, "Inconsolata");

    m_scoreLblLoc.x = _window->width - m_numExtents.x - 5 - sc.x - 5;
    m_scoreLblLoc.y = _window->height - 5;

    m_scoreLoc.x = _window->width - m_numExtents.x - 5;
    m_scoreLoc.y = _window->height - 5;

    m_healthLblLoc.x = 5.0f;
    m_healthLblLoc.y = _window->height - 5;

    m_winLoc.x = (_window->width / 2) - (m_winLoc.x / 2);
    m_winLoc.y = m_winLoc.y + 8;
}

void HUDSystem::Render()
{
	_hr->disable(StateModifiers::SM_CULL_FACE);
    // Draw base overlay
    DrawBase();

    std::string score;
    std::string health;
    std::stringstream out;
    std::stringstream out2;
    int i;
    i = _wl->GetPlayer()->GetScore();
    out << i;
    score = out.str();
    i = _wl->GetPlayer()->GetHealth();
    out2 << i;
    health = out2.str();

    // Draw player health
    Vec2f pos = _fr->RenderText("health  ", "Inconsolata", m_healthLblLoc.x, m_healthLblLoc.y, 0.0f);

    pos.x = pos.x + 5;

    pos = _fr->RenderText(health, "HUDScoreFont", m_healthLblLoc.x + pos.x, m_healthLblLoc.y, 0.0f);

    pos = _fr->RenderText("score  ", "Inconsolata", m_scoreLblLoc.x, m_scoreLblLoc.y, 0.0f);

    pos.x = pos.x + 5;

    pos = _fr->RenderText(score, "HUDScoreFont", m_scoreLblLoc.x + pos.x, m_scoreLblLoc.y, 0.0f);

    if (m_wonGame)
    {
        _fr->RenderText("YOU WON THE GAME!", "HUDScoreFont", m_winLoc.x, m_winLoc.y, 0.0f);
    }
    else if (m_lostGame)
    {
        _fr->RenderText("YOU LOST THE GAME", "HUDScoreFont", m_winLoc.x, m_winLoc.y, 0.0f);
    }

    Texture* tx;
    _tm->getTexture("crosshair", tx);

    int cenX = _window->width / 2;
    int cenY = _window->height / 2;

	_hr->blendFunc(Blend::B_SRC_ALPHA, Blend::B_ONE_MINUS_SRC_ALPHA);
    _hr->enable(StateModifiers::SM_BLEND);
    
    _hr->matrixMode(MatrixModes::MM_PROJECTION);
	_hr->pushMatrix();
	_hr->loadIdentity();
	_hr->ortho2d(0.0f, static_cast<float>(_window->width), 0.0f, 
            static_cast<float>(_window->height));
    
    _hr->matrixMode(MatrixModes::MM_MODELVIEW);
    _hr->pushMatrix();
	_hr->loadIdentity();
    _hr->disable(StateModifiers::SM_DEPTH_TEST);
	
	tx->enableAndBind();
    _hr->begin(ObjectTypes::POLYGON);
        _hr->texCoord2f(0.0f, 0.0f);
        _hr->vertex2f(cenX - 20, cenY - 20);
        _hr->texCoord2f(0.0f, 1.0f);
        _hr->vertex2f(cenX - 20, cenY + 20);
        _hr->texCoord2f(1.0f, 1.0f);
        _hr->vertex2f(cenX + 20, cenY + 20);
        _hr->texCoord2f(1.0f, 0.0f);
        _hr->vertex2f(cenX + 20, cenY - 20);
    _hr->end();
    tx->Disable();

	_hr->disable(StateModifiers::SM_BLEND);

    _hr->enable(StateModifiers::SM_DEPTH_TEST);
	_hr->popMatrix();
	_hr->matrixMode(MatrixModes::MM_PROJECTION);
	_hr->popMatrix();
}

void HUDSystem::DrawBase()
{
    // doesnt work.. sighFU
}