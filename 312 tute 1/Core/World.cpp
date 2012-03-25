#include "World.h"
#include "../Global/Global.h"
#include "../GameObjects/GameAssetFactory.h"
#include "../GameObjects/DynamicObject.h"
#include "../GameObjects/StaticObject.h"
#include "../GameObjects/TexturedParticle.h"
#include "../AI/HonirAI.h"
#include "../AI/HonirBossAI.h"
#include "../Weapons/Projectile.h"
#include "../Core/CollisionResponses.h"
#include "../Core/HUDSystem.h"

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
using namespace Honir::Core;
using namespace Honir::Global;
using namespace Honir::Physics;
using namespace Honir::GameObjects;
using namespace Honir::Terrain;
using namespace Honir::Collision;

// Global variables used in creation of "Flying NPCs"
static Model* shoot;
static float npc_radius;
static int wave_number;
static int health;

namespace Honir {
namespace Core {

World* World::m_instance = NULL;

// Defining a factory pointer to make code more readable later in the file
GameAssetFactory<GameObject>* factory = GameAssetFactory<GameObject>::Instance();

World::World()
{
	m_hf = NULL;
    m_state = Loading;
    m_timer.Init();
    m_musicID = -1;
    m_quit    = false;
    //m_musicPlaying = false;

	// Register world commands to cmd sys
	_cs->AddCmd("+forward", MvForward_f);
	_cs->AddCmd("+back", MvBack_f);
	_cs->AddCmd("+moveleft", MvLeft_f);
	_cs->AddCmd("+moveright", MvRight_f);
    _cs->AddCmd("-forward", UnMvForward_f);
	_cs->AddCmd("-back", UnMvBack_f);
	_cs->AddCmd("-moveleft", UnMvLeft_f);
	_cs->AddCmd("-moveright", UnMvRight_f);
	_cs->AddCmd("fireball", Fireball_f);
	_cs->AddCmd("+jump", Jump_f);
	_cs->AddCmd("clearballs", ClearBalls_f);
	_cs->AddCmd("createcheckpoint", Create_CheckPoint);
	_cs->AddCmd("revertcheckpoint", Revert_Checkpoint);
    _cs->AddCmd("quit", Quit_f);
	_cs->AddCmd("alljump", KrissKross);
	srand(time(NULL));
}

World::~World()
{
	m_player->RemovePhysicsFromWorld();
	delete m_player;
    delete m_instance;
	delete m_hf;
	delete m_ml;
	//delete m_level;
	m_modelMap.clear();
}

World* World::Instance()
{
    if (m_instance == NULL)
    {
        m_instance = new World();
    }

    return m_instance;
}

void World::Init()
{
	// Initialise settings for the Honir Graphics Renderer
	_hr->enable(Blend::B_BLEND);
	_hr->blendFunc(Blend::B_SRC_ALPHA, Blend::B_ONE_MINUS_SRC_ALPHA);
	_hr->enable(StateModifiers::SM_DEPTH_TEST);
	_hr->shadeModel(ShadeModels::SM_SMOOTH);
    _hr->setCursor(Cursors::CU_CURSOR_NONE);
	_hr->warpCursor(0, 0);

	// Register the GameObject Production Lines with the GameAssetFactory
	factory->Register(new ProductionLine<Player, GameObject>);
	factory->Register(new ProductionLine<StaticObject, GameObject>);
	factory->Register(new ProductionLine<DynamicObject, GameObject>);
    factory->Register(new ProductionLine<HonirAI, GameObject>);
	factory->Register(new ProductionLine<HonirBossAI, GameObject>);
	factory->Register(new ProductionLine<Projectile, GameObject>);

	// Initialise the Physics World
	_pe->InitialiseWorld(Vec3f(0.0f,-35.0f,0.0f));

	//_ce->GetWorld()->RegisterCollisionResponse("Player", "HeightField", Walking);
	//_ce->GetWorld()->RegisterCollisionResponse("DynamicObject", "HeightField", Bounce);
	//_ce->GetWorld()->RegisterCollisionResponse("Player", "DynamicObject", PushAway);
	_ce->GetWorld()->RegisterCollisionResponse("Projectile", "HonirAI", AITakeDamage);
	_ce->GetWorld()->RegisterCollisionResponse("Projectile", "Player", PlayerTakeDamage);
	_ce->GetWorld()->RegisterCollisionResponse("Projectile", "HonirBossAI", BossTakeDamage);
	_ce->GetWorld()->RegisterCollisionResponse("Projectile", "StaticObject", HitObstruction);
	//_ce->GetWorld()->RegisterCollisionResponse("Projectile", "HeightField", HitObstruction);

    // Initialise audio system
    _as->Init();

	m_menu = new MenuSystem();
	
	//m_level = new WaveLevel;

	WaveLevel::Instance()->Init();
	WaveLevel::Instance()->Load_level();

	m_ml = new WFModelLoader();

	// Initialise the cameras lookat requirements
	Vec3f pos(-40, 190, -50);
    Vec3f target(20, 150.0, 20.0);
    Vec3f up(0.0, 1.0, 0.0);
    
    m_camera.LookAt(pos, target, up);

    // Create the player object FIRST before any other objects, the player GameObject must be 1 for consistency
	// through the engine's inner-workings. The terrain object is set to 0.
	float width = 2.0f;		
	float height = 8.0f;
	float stepHeight = 0.75f;	// The height that the character can step up (like stairs)
	float moveSpeed = 250.0f;	
	float mass = 100.0f;
	Vec3f inertia(0.0f, 0.0f, 0.0f);
	float fallSpeed = 55.0f;
	float jumpSpeed = 25.0f;
	float jumpHeight = 5.0f;
	float maxSlope = 0.8727; // 50 degrees in radians

	GameObject* g = factory->Create("Player");
	SetPlayer(g);
	g->SetID(1);
	_gom->AddObject(m_player);
	PhysicsController* tempPC = _pe->GetWorld()->CreatePhysicsController(
											m_player->GetID(), width, height, moveSpeed,
											stepHeight, pos, target - pos, mass, inertia,
											fallSpeed, jumpSpeed, jumpHeight, maxSlope);

	_pe->GetWorld()->AddPhysicsController(tempPC);
	m_player->SetPhysicsInterface(tempPC);
	m_player->Initialise();

    /* Reset the coordinate system */
    m_camera.Perspective(89.0f, static_cast<float>(_window->width) / 
                         static_cast<float>(_window->height), 0.1f, 10000.0f);

	// Load all of the Game Assets data from the lua file
	LoadAssets();
    
    //MouseListener* ml = (MouseListener*)&m_camera;
    //g_mouseListeners.insert(ml);
    
	// Init World-related BASE bindings
    // This is the same no matter config file.
	_cs->QueueCmd("bind ` toggleconsole");

    // Play background music if successfully loaded
    if (m_musicID != -1)
    {
        _as->PlayMusic(m_musicID);
    }

    HUDSystem::Instance()->Init();
	
	
    
	std::string build_date = __DATE__;
	build_date += " ";
	build_date += __TIME__;

    _cn->Printf("Build: " + build_date);
	_cn->Printf("Honir Engine Demo v0.0.1");
	_cn->Printf("------------------------");

	m_state = Live;
	// Create an initial checkpoint at the start of the demo
	health = _wl->GetPlayer()->GetHealth();
	_gom->Create_CheckPoint();

    _hr->enableState(GL_FOG);
}

void World::LoadAssets()
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
    luaL_dofile(L, "resource/resources.lua");
    
    // Push vars onto stack
    lua_settop(L, 0);
    lua_getglobal(L, "mapSize");
	lua_getglobal(L, "heightMap");
	lua_getglobal(L, "lightMap");
    lua_getglobal(L, "detailMap");
	lua_getglobal(L, "lowestTile");
	lua_getglobal(L, "lowTile");
    lua_getglobal(L, "highTile");
    lua_getglobal(L, "highestTile");
	lua_getglobal(L, "scaleX");
	lua_getglobal(L, "scaleY");
	lua_getglobal(L, "scaleZ");
    lua_getglobal(L, "numNPCS");
	lua_getglobal(L, "npcModel");
	lua_getglobal(L, "npcRadius");
    lua_getglobal(L, "numStatics");
    lua_getglobal(L, "statModel");
	lua_getglobal(L, "statBoxSize");
    lua_getglobal(L, "bgMusic");
    lua_getglobal(L, "cfgFile");
	lua_getglobal(L, "splashText");
	lua_getglobal(L, "splashTexture");
	lua_getglobal(L, "title");
	lua_getglobal(L, "resetPosition");
	lua_getglobal(L, "saveCheckpoint");
	lua_getglobal(L, "loadCheckpoint");
	lua_getglobal(L, "quit");
    
    lua_getglobal(L, "skyboxFront");
	lua_getglobal(L, "skyboxLeft");
	lua_getglobal(L, "skyboxBack");
	lua_getglobal(L, "skyboxRight");
	lua_getglobal(L, "skyboxUp");
	lua_getglobal(L, "skyboxDown");

	
    // Check variable typing
    if (!lua_isnumber(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L, 3) || 
        !lua_isstring(L, 4) || !lua_isstring(L, 5) || !lua_isstring(L, 6) ||
        !lua_isstring(L, 7) || !lua_isstring(L, 8) || !lua_isnumber(L, 9) ||
		!lua_isnumber(L, 10) || !lua_isnumber(L, 11) || !lua_isnumber(L, 12) ||
		!lua_isstring(L, 13) || !lua_isnumber(L, 14) || !lua_isnumber(L, 15) ||
		!lua_isstring(L, 16) || !lua_isnumber(L, 17) || !lua_isstring(L, 18) ||
		!lua_isstring(L, 19) || !lua_isstring(L, 20) || !lua_isstring(L, 21) ||
		!lua_isstring(L, 22) || !lua_isstring(L, 23) || !lua_isstring(L, 24) ||
		!lua_isstring(L, 25) || !lua_isstring(L, 23))
     {
        std::cerr << "lua: incorrect types given in resources.lua"
            << std::endl;
        return;
    }

	int   mapSize	        = (int)lua_tonumber(L, 1);
	char* heightMap         = (char*)lua_tostring(L, 2);
	char* lightMap          = (char*)lua_tostring(L, 3);
	char* detailMap         = (char*)lua_tostring(L, 4);
	char* lowestTile        = (char*)lua_tostring(L, 5);
    char* lowTile	        = (char*)lua_tostring(L, 6);
    char* highTile          = (char*)lua_tostring(L, 7);
    char* highestTile       = (char*)lua_tostring(L, 8);
	float scaleX	        = (float)lua_tonumber(L, 9);
	float scaleY	        = (float)lua_tonumber(L, 10);
	float scaleZ	        = (float)lua_tonumber(L, 11);
	int   numNPCS           = (int)lua_tonumber(L, 12);
	char* npc_model	        = (char*)lua_tostring(L, 13);
	npc_radius              = (float)lua_tonumber(L, 14);
	int	  numStatics        = (int)lua_tonumber(L, 15);
	char* statModel         = (char*)lua_tostring(L, 16);
	float statBoxSize       = (float)lua_tonumber(L, 17);
    char* bgMusic           = (char*)lua_tostring(L, 18);
    char* cfgFile           = (char*)lua_tostring(L, 19);
	char* splashText		= (char*)lua_tostring(L, 20);
	char* splashTexture		= (char*)lua_tostring(L, 21);
	char* title			    = (char*)lua_tostring(L, 22);
	char* resetPosition     = (char*)lua_tostring(L, 23);
	char* saveCheckpoint	= (char*)lua_tostring(L, 24);
	char* loadCheckpoint    = (char*)lua_tostring(L, 25);
	char* quit				= (char*)lua_tostring(L, 26);
    char* skyboxF           = (char*)lua_tostring(L, 27);
    char* skyboxL           = (char*)lua_tostring(L, 28);
    char* skyboxB           = (char*)lua_tostring(L, 29);
    char* skyboxR           = (char*)lua_tostring(L, 30);
    char* skyboxU           = (char*)lua_tostring(L, 31);
    char* skyboxD           = (char*)lua_tostring(L, 32);

	// Load splash screen texture
    m_splashTex = quit;
    _tm->newTexture(m_splashTex, TextureTypes::TEX_2D, splashTexture, -1, -1, -1, -1);
	
	m_menu->SetTitle(title);
	m_menu->AddFunction(resetPosition, ResetPos_f);
    m_menu->AddFunction(saveCheckpoint, Create_CheckPoint);
    m_menu->AddFunction(loadCheckpoint, Revert_Checkpoint);
	m_menu->AddFunction(quit, Quit_f);
    
    // Temp pointers used in intialisation of the GameObjects
	GameObject* tempGO;
	PhysicsRigidObject* tempPO;

	//Terrain heightfield init
	m_hf = new HeightField();
	m_hf->SetID(0);		// Terrain will always be GameObject ID = 0;
	
    m_hf->Load_LightMap(lightMap,mapSize);
	if(m_hf->Load_HeightMap(heightMap, mapSize, scaleX, scaleY, scaleZ))
	{
		m_hf->Load_tile( LOWEST_TILE,  lowestTile );
		m_hf->Load_tile( LOW_TILE,     lowTile );
		m_hf->Load_tile( HIGH_TILE,    highTile );
		m_hf->Load_tile( HIGHEST_TILE, highestTile );
		m_hf->Load_detail_map(detailMap);
		m_hf->Initialise_Terrain();
	}

	_gom->AddObject(m_hf);

	// Terrain collision shape creation and inclusion. It is defined by the vertex array that creates the
	// heightfield. Not every vertex is registered because that would sap performance but there are still
	// enough to create a strong approximation to the shape.
    tempPO = _pe->GetWorld()->CreateTerrainRigidObject(m_hf->GetID(), m_hf->Get_char_array(), m_hf->m_terrain_size, m_hf->min_height, m_hf->max_height, m_hf->Get_Y_scale());
    std::cout << "MaxHeight: " << m_hf->max_height << std::endl;
    _pe->GetWorld()->AddPhysicsRigidObject(tempPO);
	m_hf->SetPhysicsInterface(tempPO);

	// Limit the amount of NPCs that can be created
	if(numNPCS > 20)
		numNPCS = 20;

	// Load in the WaveFront Model/s
	m_modelMap["statModel"] = new Model();
	m_modelMap["npcModel"] = new Model();
	//m_ml->LoadModel(statModel, *m_modelMap["statModel"]);
	m_modelMap["statModel"] = m_ml->Get_Model(statModel);
	//m_ml->LoadModel(npc_model, *m_modelMap["npcModel"]);
	m_modelMap["npcModel"] = m_ml->Get_Model(npc_model);
	shoot = m_modelMap["npcModel"];
	m_player->ActiveWeapon()->Initialise(20.0f, 20.0f, shoot);

	// Add static objects
	for(int i = 0; i < numStatics; i++)
	{
		tempGO = factory->Create("StaticObject");
		_gom->AddObject(tempGO);
		tempPO = _pe->GetWorld()->CreateBoxRigidObject(tempGO->GetID(), statBoxSize, statBoxSize, statBoxSize,
					Vec3f((float)(rand() % 30 + 10), 69.0f * scaleY, (float)(rand() % 30 - 35)),
					0, Vec3f(0,0,0));

		_pe->GetWorld()->AddPhysicsRigidObject(tempPO);
		tempGO->SetPhysicsInterface(tempPO);
		tempGO->SetModel(m_modelMap["statModel"]);
	}

    m_musicID = _as->LoadSound(bgMusic);
    std::cout << "loading music: " << bgMusic << std::endl;

    // Execute config file given in lua script
    std::string execcfg = "exec ";
    execcfg.append(cfgFile);
    _cs->QueueCmd(execcfg);

    // Load skybox images
	_tm->newTexture("skyboxF", TextureTypes::TEX_2D, skyboxF, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureZoomFilters::TEX_NEAREST, TextureZoomFilters::TEX_NEAREST);
	_tm->newTexture("skyboxL", TextureTypes::TEX_2D, skyboxL, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureZoomFilters::TEX_NEAREST, TextureZoomFilters::TEX_NEAREST);
	_tm->newTexture("skyboxB", TextureTypes::TEX_2D, skyboxB, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureZoomFilters::TEX_NEAREST, TextureZoomFilters::TEX_NEAREST);
	_tm->newTexture("skyboxR", TextureTypes::TEX_2D, skyboxR, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureZoomFilters::TEX_NEAREST, TextureZoomFilters::TEX_NEAREST);
	_tm->newTexture("skyboxU", TextureTypes::TEX_2D, skyboxU, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureZoomFilters::TEX_NEAREST, TextureZoomFilters::TEX_NEAREST);
	_tm->newTexture("skyboxD", TextureTypes::TEX_2D, skyboxD, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureWrapping::TEX_CLAMP_TO_EDGE, TextureZoomFilters::TEX_NEAREST, TextureZoomFilters::TEX_NEAREST);

    lua_close(L);
}

void World::Loop()
{
	static int frameCount = 0;
    static int totalFrames = 0;
    static int lastTime = _hr->getState(StateModifiers::SM_ELAPSED_TIME);
    static int fpsCountTime = _hr->getState(StateModifiers::SM_ELAPSED_TIME);
    static int thisTime;

    thisTime = _hr->getState(StateModifiers::SM_ELAPSED_TIME);

    // Ensure 125Hz maximum (i.e. 125 FPS cap)
    if (thisTime - lastTime < 8) return;

    // For checking FPS. FPS = frameCount here
    if (thisTime - fpsCountTime >= 1000)
    {
        frameCount = 0;
        fpsCountTime = thisTime;
    }

    lastTime = thisTime;
    frameCount++;
    totalFrames++;
	
    // Update timer function
	m_timer.Update();

    _hr->clear(Colour(0.62f, 0.93f, 1.0f, 1.0f));
	_hr->fog(Colour(0.8f, 0.8f, 0.8f, 0.4f), 0.25f, 50.0f, 300.0f);
    _hr->pushMatrix();
    DrawSkybox();
    _hr->popMatrix();
    
	//level stuff
	
	if(frameCount%10==0)
	{
		WaveLevel::Instance()->Update();

		if(WaveLevel::Instance()->Level_is_won())
		{
			// DO SOME SPLASH SCREEN AND END THE GAME
		}
	}
	
	

	//end level stuff

    

    // Update world state
    UpdateState();

    // If user has chosen to quit, draw splash and wait for mouse click
    if (m_state == Quit)
    {
        //Draw splash screen here
        DrawSplash();
        _hr->swapBuffers();
        return;
    }

	// Set the camera's position to the player's position
    m_camera.SetPos(m_player->GetPhysicsController()->GetPositionVector());
    
    // Set the Player's forward vector (look vector) to the camera's view
	m_player->GetPhysicsController()->SetForwardVec(Camera::GetView());
    //m_player->GetPhysicsController()->Move(NONE, 0.008);
	m_camera.Update(true);

	// Load camera matrices
	_hr->matrixMode(MatrixModes::MM_PROJECTION);
	_hr->loadMatrix(m_camera.GetPM());
	_hr->matrixMode(MatrixModes::MM_MODELVIEW);
	_hr->loadMatrix(m_camera.GetVM());
	
    _ce->GetWorld()->DetectAllCollisions();
	_ce->GetWorld()->ResolveAllCollisions();

	// Update systems
	_bn->Update();
	_cs->ExecBuffer();
	_gom->UpdateAllObjects();
	_as->Update();
    if (frameCount % 30 == 0) _ai->UpdateAgents();
    if (totalFrames % 400 == 0) 
    {
         _ai->Clean(); // Clean dead AI agents
    }
	_gom->RenderAllObjects();

	Vec3f cam_pos = Camera::GetPos();
	Vec3f strafe = _wl->GetPlayer()->GetPhysicsController()->GetStrafeVec();
	Vec3f forward = _wl->GetPlayer()->GetPhysicsController()->GetForwardVec();
	Vec3f up = forward.Cross(strafe);

	GenerateSmoke();
	DrawFluid();
	    
    // If timer is too fast, safe to assume we're capping FPS to 125
    // So use that Hz to step forward, otherwise (if FPS is dropping),
    // correct time is still used.
    if (m_timer.FrameTime() < 0.008)
    {
        _pe->GetWorld()->StepWorldForward(0.008);
    }
    else
    {
        _pe->GetWorld()->StepWorldForward(m_timer.FrameTime());
    }

	if (totalFrames % 30 == 0) _gom->DeleteDeadObjects();

	DeathStar();

	//	Particle rendering - must be done last of all the game world objects
	_pm->UpdateParticles(Point(cam_pos.x, cam_pos.y, cam_pos.z), up);

    HUDSystem::Instance()->Render();
	// Console rendering
	_cn->Render();
    // Menu processing
	m_menu->Process();

    _hr->swapBuffers();
}

void World::UpdateState()
{
    // Menu has higher precedence over console
    if (_cn->IsEnabled() && m_menu->IsActive())
    {
        _cn->Toggle();
    }

    if (_cn->IsEnabled() && !m_quit)
    {
        m_state = InConsole;
        return;
    }
    
    if (m_menu->IsActive() && !WaveLevel::Instance()->Level_is_won())
    {
        m_state = InMenu;
        return;
    }

    if (m_quit)
    {
        m_state = Quit;
        return;
    }

    if (WaveLevel::Instance()->Level_is_won() || _wl->GetPlayer()->GetHealth() <= 0)
    {
        if (_wl->GetPlayer()->GetHealth() <= 0)
        {
            HUDSystem::Instance()->LostGame();
        }
        else
        {
            HUDSystem::Instance()->WonGame();
        }
        m_menu->Activate();
        m_state = FinishedGame;
        return;
    }

    // If none of these, we're live
    m_state = Live;
}

GameState World::GetState()
{
    return m_state;
}

Player* World::GetPlayer()
{
	return m_player;
}

HeightField* World::GetTerrain()
{
	return m_hf;
}

void World::SetPlayer(GameObject* player)
{
	m_player = static_cast<Player*>(player);
}

void World::DrawSkybox()
{
	_hr->matrixMode(MatrixModes::MM_MODELVIEW);
    //glMatrixMode(GL_MODELVIEW);
    const float BoxSize = 10.0f;
    float m[4][4];
	static Texture* texSkybox[6];
	static bool loaded = false;

	_hr->pushMatrix();
    //glPushMatrix();
	_hr->getFloat(MatrixModes::MODELVIEW_MATRIX, m[0]);
    //glGetFloatv(GL_MODELVIEW_MATRIX, m[0]);
    m[3][0] = 0; m[3][1] = 0; m[3][2] = 0;
	_hr->loadMatrix(m[0]);
	//glLoadMatrixf(m[0]);

	if(!loaded)
	{
		_tm->getTexture("skyboxF", texSkybox[0]);
		_tm->getTexture("skyboxL", texSkybox[1]);
		_tm->getTexture("skyboxB", texSkybox[2]);
		_tm->getTexture("skyboxR", texSkybox[3]);
		_tm->getTexture("skyboxU", texSkybox[4]);
		_tm->getTexture("skyboxD", texSkybox[5]);

		loaded = true;
	}

    /// Temporarily disable depth testing
	_hr->disable(StateModifiers::SM_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);
    //glDepthMask(0);
	_hr->enable(TextureTypes::TEX_2D);
    //glEnable(GL_TEXTURE_2D);
    _hr->disable(StateModifiers::SM_CULL_FACE);
   
	/// Front
	texSkybox[0]->enableAndBind();
	_hr->begin(ObjectTypes::QUADS);
    //glBegin(GL_QUADS);
        _hr->texCoord2f(0.0, 0.0);
        _hr->vertex3f(BoxSize / 2, -BoxSize / 2, -BoxSize / 2);
        _hr->texCoord2f(1.0, 0.0);
        _hr->vertex3f(-BoxSize / 2, -BoxSize / 2, -BoxSize / 2);
        _hr->texCoord2f(1.0, 1.0);
        _hr->vertex3f(-BoxSize / 2, BoxSize / 2, -BoxSize / 2);
        _hr->texCoord2f(0.0, 1.0);
        _hr->vertex3f(BoxSize / 2, BoxSize / 2, -BoxSize / 2);
	_hr->end();

    /// Left
	texSkybox[1]->enableAndBind();
	_hr->begin(ObjectTypes::QUADS);
	//glBegin(GL_QUADS);
		_hr->texCoord2f(0.0, 0.0);
        _hr->vertex3f(BoxSize / 2, -BoxSize / 2, BoxSize / 2);
		_hr->texCoord2f(1.0, 0.0);
        _hr->vertex3f(BoxSize / 2, -BoxSize / 2, -BoxSize / 2);
		_hr->texCoord2f(1.0, 1.0);
        _hr->vertex3f(BoxSize / 2, BoxSize / 2, -BoxSize / 2);
		_hr->texCoord2f(0.0, 1.0);
        _hr->vertex3f(BoxSize / 2, BoxSize / 2, BoxSize / 2);
    _hr->end();

    /// Back
    texSkybox[2]->enableAndBind();
    _hr->begin(ObjectTypes::QUADS);
	//glBegin(GL_QUADS);
        _hr->texCoord2f(0.0, 0.0);
        _hr->vertex3f(-BoxSize / 2, -BoxSize /2, BoxSize / 2);
        _hr->texCoord2f(1.0, 0.0);
        _hr->vertex3f(BoxSize / 2, -BoxSize / 2, BoxSize / 2);
        _hr->texCoord2f(1.0, 1.0);
        _hr->vertex3f(BoxSize / 2, BoxSize / 2, BoxSize / 2);
        _hr->texCoord2f(0.0, 1.0);
        _hr->vertex3f(-BoxSize / 2, BoxSize / 2, BoxSize / 2);
    _hr->end();

    /// Right
    texSkybox[3]->enableAndBind();
    _hr->begin(ObjectTypes::QUADS);
        glNormal3f(0.0f, 0.0f, 20.0f);
        _hr->texCoord2f(0.0, 0.0);
        _hr->vertex3f(-BoxSize / 2, -BoxSize /2, -BoxSize / 2);
        _hr->texCoord2f(1.0, 0.0);
        _hr->vertex3f(-BoxSize / 2, -BoxSize / 2, BoxSize / 2);
        _hr->texCoord2f(1.0, 1.0);
        _hr->vertex3f(-BoxSize / 2, BoxSize / 2, BoxSize / 2);
        _hr->texCoord2f(0.0, 1.0);
        _hr->vertex3f(-BoxSize / 2, BoxSize / 2, -BoxSize / 2);
    _hr->end();


    texSkybox[4]->enableAndBind();
    _hr->begin(ObjectTypes::QUADS);
        glNormal3f(-20.0f, 0.0f, 0.0f);
        _hr->texCoord2f(0.0, 0.0);
        _hr->vertex3f(-BoxSize / 2, BoxSize / 2, -BoxSize / 2);
        _hr->texCoord2f(1.0, 0.0);
        _hr->vertex3f(-BoxSize / 2, BoxSize / 2, BoxSize / 2);
        _hr->texCoord2f(1.0, 1.0);
        _hr->vertex3f(BoxSize / 2, BoxSize / 2, BoxSize / 2);
        _hr->texCoord2f(0.0, 1.0);
        _hr->vertex3f(BoxSize / 2, BoxSize / 2, -BoxSize / 2);
    _hr->end();

    /// Down
    texSkybox[5]->enableAndBind();
    _hr->begin(ObjectTypes::QUADS);
        glNormal3f(20.0f, 0.0f, 0.0f);
        _hr->texCoord2f(0.0, 0.0);
        _hr->vertex3f(-BoxSize / 2, -BoxSize / 2, -BoxSize / 2);
        _hr->texCoord2f(1.0, 0.0);
        _hr->vertex3f(-BoxSize / 2, -BoxSize / 2, BoxSize / 2);
        _hr->texCoord2f(1.0, 1.0);
        _hr->vertex3f(BoxSize / 2, -BoxSize / 2, BoxSize / 2);
        _hr->texCoord2f(0.0, 1.0);
        _hr->vertex3f(BoxSize / 2, -BoxSize / 2, -BoxSize / 2);
    _hr->end();

	_hr->disable(TextureTypes::TEX_2D);
	
    //glDisable(GL_TEXTURE_2D);
    /// Re-enable depth testing
    //glDepthMask(1);
    _hr->enable(StateModifiers::SM_DEPTH_TEST);
	//glEnable(GL_DEPTH_TEST);
	_hr->popMatrix(); 
    //glPopMatrix();
}

void World::Resize(int width, int height)
{
	float ratio;
    
    /* Prevent divide by zero */
	if (height == 0) { height = 1; }
    
	/* Get aspect ratio of new window size */
	ratio = 1.0f * width / height;
	
	_hr->matrixMode(MatrixModes::MM_PROJECTION);
	_hr->loadIdentity();

	_hr->viewport(0, 0, width, height);

    /* Calculate horizontal fov */
    float fov = 90.0f * ((float)height / (float)width);

    m_camera.Perspective(fov, ratio, 0.1f, 10000.0f);
	
	_hr->matrixMode(MatrixModes::MM_MODELVIEW);

	_window->width = width;
	_window->height = height; 

    Camera::SetScreenCoords(_window->width, _window->height);
}

void World::QuitGame()
{
    m_quit = true;
}

void World::ClickEvent(MouseButton mb, int x, int y)
{
    if (mb == MOUSE_LEFT && m_quit)
    {
        exit(0);
    }
}

void World::DrawSplash()
{
    Texture* tx;
    _tm->getTexture(m_splashTex, tx);
    tx->enableAndBind();

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


	_hr->translate(centreX, centreY, 0.0);
    _hr->scale(512 / 2, 512 / 2, 0.0);
	_hr->begin(ObjectTypes::POLYGON);
        _hr->texCoord2f(1.0f, 1.0f);
        _hr->vertex2f(1.0f, 1.0f);
        _hr->texCoord2f(0.0f, 1.0f);
		_hr->vertex2f(-1.0f, 1.0f);
        _hr->texCoord2f(0.0f, 0.0f);
		_hr->vertex2f(-1.0f, -1.0f);
        _hr->texCoord2f(1.0f, 0.0f);
		_hr->vertex2f(1.0f, -1.0f);
    _hr->end();
    tx->Disable();
	
	_hr->enable(StateModifiers::SM_DEPTH_TEST);
	_hr->popMatrix();
	_hr->matrixMode(MatrixModes::MM_PROJECTION);
	_hr->popMatrix();
}

void  World::GenerateSmoke()
{
	static int frame_count = -1;

	if(frame_count > 60 || frame_count == -1)
	{
		// If it's the first frame, we need to create texture, otherwise not.
        if (frame_count == -1)
        {
            _tm->newTexture("smoke_particle", TextureTypes::TEX_2D, "resource/Data/smoke.png", -1, -1, -1, -1);
            _tm->newTexture("fire_particle", TextureTypes::TEX_2D, "resource/Data/fire.png", -1, -1, -1, -1);
        }

		Vec3f pos(-99.1652, 35.0, -21.9997); //volcano location
		Vec3f velocity(0.0, 0.25, 0.0);			//3m/s up
		Vec3f gravity (0.05, 0.0, 0.05);			
		Vec3f up(0.0, 1.0, 0.0);				//straight up
		float lifetime = 25.0;					//alive for 25 seconds (50 was bit overkill, lagging fps);

		Texture* texture;
		_tm->getTexture("smoke_particle", texture);
        Texture* fire;
        _tm->getTexture("fire_particle", fire);

		float size = 10.0;
		float rotation = 1.0 * (rand() / double(RAND_MAX));
		float scale = 0.005;

        Vec3f firegrav(0.0, 0.07, 0.0);

		TexturedParticle* tp = new TexturedParticle(pos, velocity, gravity, up, lifetime, texture, size, rotation, scale);
		_pm->AddParticle(tp);
        TexturedParticle* tp2 = new TexturedParticle(pos, Vec3f(0,0,0), firegrav, up, 6.5, fire, size, rotation, 0.006);
        _pm->AddParticle(tp2);
		frame_count = 0;
	}
	else
	{
		frame_count++;
	}
}

void World::DrawFluid()
{
	static bool loaded = false;
	static Fluid* fluid = NULL;
	static int disturbance = 0;
	static Texture* tex = NULL;

	if(!loaded)
	{
		fluid = new Fluid(100,100, 0.3, 1.0/60.0, 3.0, 0.2);
		loaded = true;
		_tm->newTexture("lava", TextureTypes::TEX_2D, "resource/textures/lava.jpg", TextureWrapping::TEX_REPEAT, TextureWrapping::TEX_REPEAT, -1, -1);
		_tm->getTexture("lava", tex);
	}
	disturbance++;

	if(disturbance > 500)
	{
		fluid->Disturb();
		disturbance = 0;
	}

	static float x = 0;
	static float y = 0;

	x+=0.00036;
	y-=0.00021;

	_hr->disable(Graphics::SM_CULL_FACE);
	_hr->pushMatrix();
		_hr->translate(-110, 30, -35);
		_hr->rotate(90, 1,0,0);
			tex->enableAndBind();
			_hr->matrixMode(MatrixModes::MM_TEXTURE);
			_hr->pushMatrix();
			_hr->loadIdentity();
			_hr->translate(x, y, 0);
				fluid->Draw();
			_hr->popMatrix();
	_hr->matrixMode(MatrixModes::MM_MODELVIEW);
	_hr->popMatrix();
	_hr->enable(Graphics::SM_CULL_FACE);

	Vec3f pos =  m_player->GetPhysicsController()->GetPositionVector();
}

void World::DeathStar()
{
	if (m_state == FinishedGame) return;

    Vec3f death_star_pos = Vec3f(-97.0f, 25.0f, -22.0f);
	float death_star_radius = 12.0f;
	
	Vec3f player_pos = _wl->GetPlayer()->GetPhysicsController()->GetPositionVector();

	if((player_pos - death_star_pos).Magnitude() < death_star_radius)
		if(_wl->GetPlayer()->IsAlive())
			_wl->GetPlayer()->ApplyDamage(_wl->GetPlayer()->GetHealth());
}

} // namespace Core
} // namespace Honir

// Definitions for functions to be used in CmdSys

void Quit_f()
{
    _wl->QuitGame();
}

// These functions register a movement step with the Player's controller. There were
// issues in that the frametime provided by the Timer class was too small (error?) due
// to a rapid framerate and the Player is not moving enough between frames resulting in
// a VERY slow movement speed. We have now set the movement time so as to make the speed
// less frustrating but this issue will need to be resolved eventually.

void MvForward_f()
{	
	_wl->GetPlayer()->GetPhysicsController()->Move(FORWARD, true);
}

void MvBack_f()
{
	_wl->GetPlayer()->GetPhysicsController()->Move(BACKWARD, true);
}

void MvLeft_f()
{
	_wl->GetPlayer()->GetPhysicsController()->Move(LEFT, true);
}

void MvRight_f()
{
	_wl->GetPlayer()->GetPhysicsController()->Move(RIGHT, true);
}

void UnMvForward_f()
{	
	_wl->GetPlayer()->GetPhysicsController()->Move(FORWARD, false);
}

void UnMvBack_f()
{
	_wl->GetPlayer()->GetPhysicsController()->Move(BACKWARD, false);
}

void UnMvLeft_f()
{
	_wl->GetPlayer()->GetPhysicsController()->Move(LEFT, false);
}

void UnMvRight_f()
{
	_wl->GetPlayer()->GetPhysicsController()->Move(RIGHT, false);
}

void Fireball_f()
{	
	_wl->GetPlayer()->ActiveWeapon()->Attack(0.65, _wl->GetPlayer()->GetPhysicsController()->GetPositionVector() + (_wl->GetPlayer()->GetPhysicsController()->GetForwardVec() * 6.0f), 5.0f, 75.0f);
}

void Jump_f()
{
	_wl->GetPlayer()->GetPhysicsController()->Jump();
}

void ClearBalls_f()
{	
	// Clears all of the Dynamic "balls" from the GameAssetManager
	std::vector<GameObject*> objects = _gom->GetAllObjects();

	for(int i = 0; i < (int)objects.size(); i++)
	{
		if(objects[i]->GetObjectType() == "DynamicObject")
		{
			_gom->DeleteObject(objects[i]);
		}
	}
}

void ResetPos_f()
{
	// Reset the position of the Player (and the camera) to the starting point
	Vec3f pos(-40, 190, -50);
	_wl->GetPlayer()->GetPhysicsController()->SetPositionVector(pos);
}

void Create_CheckPoint()
{
	health = _wl->GetPlayer()->GetHealth();
	_gom->Create_CheckPoint();
	wave_number = WaveLevel::Instance()->Get_wave_num();
}

void Revert_Checkpoint()
{
    // Resolve all collisions first
    _ce->GetWorld()->ResolveAllCollisions();
    // STL vector to be used before the Checkpoint has been reloaded
	vector<GameObject*> pre_reset_allObjects = _gom->GetAllObjects();
	vector<GameObject*>::iterator i;
	Player* tempP;
	DynamicObject* tempDO;
	StaticObject* tempSO;
	const char* tempString;

	// Go through each GameObject and remove its Physics component from the PhysicsWorld
	for(i = pre_reset_allObjects.begin(); i != pre_reset_allObjects.end(); i++)
	{
		(*i)->RemovePhysicsFromWorld();
	}

    // Clear the AI AgentManager
    _ai->Clear();

	// Load in the previous Checkpoint
	_gom->Revert_Checkpoint();

	// Add the world terrain object to the manager
	_gom->AddObject(_wl->GetTerrain());

	// STL vector to be used after the Checkpoint reload
	std::vector<GameObject*> post_reset_allObjects = _gom->GetAllObjects();

    HUDSystem::Instance()->NotWonGame();
    HUDSystem::Instance()->NotLostGame();

    _wl->SetState(InMenu);
	
	// ReInitialise the Player stuff
	_wl->SetPlayer(GameObjectManager::Instance()->GetThisObject(1));
	_wl->GetPlayer()->Initialise();
	_wl->GetPlayer()->ActiveWeapon()->Initialise(20.0f, 20.0f, shoot);
    _wl->GetPlayer()->SetHealth(health);

	// Iterate through the GameObjects and re-insert their Physics components to the Physics world
	for(i = post_reset_allObjects.begin(); i != post_reset_allObjects.end(); i++)
	{
		(*i)->AddPhysicsToWorld();

		if(((*i)->GetObjectType() == "HonirAI") || ((*i)->GetObjectType() == "HonirBossAI"))
		{
			HonirAI* tempAI = static_cast<HonirAI*>(*i);
			tempAI->Initialise();
            // Create units agents and set them up
            _ai->AddAgent(tempAI);
		}
	}

	WaveLevel::Instance()->Set_wave_num(wave_number);

	// Create this checkpoint - which has the exact same information as the checkpoint just reloaded -
	// so that we can reload a checkpoint multiple times in a row without prompting a new save
	health = _wl->GetPlayer()->GetHealth();
	_gom->Create_CheckPoint();
}

void KrissKross()
{
	vector<GameObject*> objects = _gom->GetAllObjects();
	vector<GameObject*>::iterator i;
	DynamicObject* tempDO;

	for(i = objects.begin(); i != objects.end(); i++)
	{
		if((*i)->GetObjectType() == "DynamicObject")
		{
			tempDO = static_cast<DynamicObject*>(*i);
			tempDO->GetPhysicsRigidObject()->ApplyForce(Vec3f(0.0f, 20.0f, 0.0f));
		}
	}
}

void Walking(CollisionData* cd)
{
	cout << "Walking on sunshine" << endl;
	cout << cd->objectA->GetObjectType() << endl;
	cout << cd->objectB->GetObjectType() << endl;
	cout << cd->position.x << "," << cd->position.y << "," << cd->position.z << endl;
}

void Bounce(CollisionData* cd)
{
	DynamicObject* tempDO;

    if(cd->objectA->GetObjectType() == "DynamicObject")
	{
		tempDO = static_cast<DynamicObject*>(cd->objectA);
	}
	else
	{
		tempDO = static_cast<DynamicObject*>(cd->objectB);
	}

	tempDO->GetPhysicsRigidObject()->ApplyForce(Vec3f(0.0f, 0.3f, 0.0f));
}

void PushAway(CollisionData* cd)
{
	DynamicObject* tempDO;
	Player* playa;
	Vec3f temp;

    if(cd->objectA->GetObjectType() == "Player")
	{
		tempDO = static_cast<DynamicObject*>(cd->objectB);
		playa = static_cast<Player*>(cd->objectA);
	}
	else
	{
		tempDO = static_cast<DynamicObject*>(cd->objectA);
		playa = static_cast<Player*>(cd->objectB);
	}

	temp = tempDO->GetPhysicsRigidObject()->GetPositionVector() - playa->GetPhysicsController()->GetPositionVector();
	tempDO->GetPhysicsRigidObject()->ApplyForce(temp * 0.3);
}
