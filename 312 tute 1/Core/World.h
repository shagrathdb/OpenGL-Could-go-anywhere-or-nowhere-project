/**
 * @class World
 * @brief Game world class.
 *
 * Loads and initialises game data, creates game objects, and defines
 * the main game loop.
 * 
 * @author Simon Manning
 * @version 0.a
 * @date 13-04-2011
 */

#ifndef _WORLD_H_
#define _WORLD_H_

#include <lua.hpp>
#include <string>
#include <map>

#include "../GameObjects/Player.h"
#include "../Input/MouseListener.h"
#include "GameState.h"
#include "Camera.h"
#include "Timer.h"
#include "../Terrain/heightfield.h"
#include "../Model/mloader.h"
#include "../../testonly/simon_terrain.h"
#include "../Core/MenuSystem.h"
#include "../Collision/CollisionData.h"
#include "../Level/Level.h"
#include "../Level/WaveLevel.h"
#include "../Animation/Fluid.h"


using namespace Honir::Input;
using namespace Honir::GameObjects;
using namespace Honir::Terrain;
using namespace Honir::ModelLoader;
using namespace Honir::Collision;

namespace Honir {
namespace Core {

class World : public MouseListener
{
  public:  
    /** Destructor */
    ~World();

    /** Initialisation function: called after window is created */
    void Init();

    /** Main game loop & windowing API idlefunc callback. */
    void Loop();

    /** Loads and creates game assets from Lua scripts using GameAssetFactory. */
    void LoadAssets();

    /** Performs game state logic. */
    void UpdateState();

	/** Gets the instance */
	static World* Instance();

    /**
     * Sets world game state.
     *
     * @param state GameState.
     */
    void SetState(GameState state) { m_state = state; }

    /** 
     * Returns frame-time from world's Timer.
     */
    float GetFrameTime();

    /**
     * Returns current game state.
     */
    GameState GetState();

	/**
	 * Returns Player object pointer
	 */
	Player* GetPlayer();

	HeightField* GetTerrain();

	/**
	 * Sets the World's Player object pointer
	 */
	void SetPlayer(GameObject* player);

	/**
	 * Window resize callback
	 */
	void Resize(int width, int height);

    /**
     * Player has called quit, so draw splash and wait for mouse click.
     */
    void QuitGame();

    /**
     * Get mouse clicks via MouseListener base class for quitting
     */
    void ClickEvent(MouseButton mb, int x, int y);

    /**
     * Draws exit splash screen
     */
    void DrawSplash();

	void GenerateSmoke();

    void DrawSkybox();

	void DrawFluid();

	void DeathStar();


  private:
    /** Singleton constructor */
    World();
    static World* m_instance;

	//Level* m_level;

    GameState m_state;
    Timer     m_timer;
    int       m_musicID;
    //bool      m_musicPlaying;

    Camera    m_camera;
    Player*   m_player;
	
	HeightField* m_hf;
	WFModelLoader* m_ml;
	map<string, Model*> m_modelMap;

	MenuSystem*	m_menu;

    std::string m_splashTex;
	bool        m_quit;
};

} // namespace Core
} // namespace Honir

/** Global functions for registering to CmdSys */
void Quit_f();

void MvForward_f();
void MvBack_f();
void MvLeft_f();
void MvRight_f();
void UnMvForward_f();
void UnMvBack_f();
void UnMvLeft_f();
void UnMvRight_f();

void Fireball_f();
void Jump_f();
void ClearBalls_f();
void ResetPos_f();
void Create_CheckPoint();
void Revert_Checkpoint();

/** Debug functions used in collision responses */
void KrissKross();
void Walking(CollisionData* cd);
void Bounce(CollisionData* cd);
void PushAway(CollisionData* cd);

#endif
