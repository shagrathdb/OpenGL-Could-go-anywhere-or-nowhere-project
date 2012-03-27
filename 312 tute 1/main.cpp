#include <stdlib.h>
#include <math.h>
#include "includes.h"
#include "Input\InputListeners.h"
#include "Core\Camera.h"
#include "PhysicsObject\PhysicsObjManager.h"
#include "PhysicsObject\ProjectilePhysicsObj.h"
#include "Player\Player.h"
#include "Weapons\BallShooter.h"
#include "Weapons\RhombicDodecahedronShooter.h"
#include "3DModel\Cuboid.h"
#include "3DeeModel\ModelFactory.h"

#include "3DeeModel\ThreeDeeModel.h"

#include "ShaderUtilities\//ShaderManager\//ShaderManager.h"
#include "ShaderUtilities\UniformVarFactory\UniformVarFactory.h"
#include "ShaderUtilities\ShaderType\GLSLProgram.h"
#include "ShaderUtilities\ShaderMode.h"
#include "ShaderUtilities\ShaderFactory\ShaderFactory.h"

#include "3DModel\Ball.h"

#include "Utility\ImpVector2.h"

#include <iostream>

Vector2<float> yay;

int switchit = 0;

float offset = 0;

Camera camera1;
Vec3f init_pos(0, 1.0f, 10);
Vec3f init_target(0, 1.0f,  -1);
Vec3f init_up(0,1,0);

Player player1;

ThreeDeeModel* testVBO;
ThreeDeeModel* deadworld;
ThreeDeeModel* wardroid;
ThreeDeeModel* rocket;
BallModel globe;
//Vec3f light_po(250.0f, 1.0f, 10.0f);

Vec3f light_pos(200.0f, 5.0f, 0.0f);

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	camera1.Perspective(90, ratio, 0.1f, 10000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	Camera::SetScreenCoords(w,h);
}

unsigned int ID = 0;
bool physupdate = false;
float disp = 0.1;
Cuboid cube(0.5,2,0.5);
void renderScene(void) 
{
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glEnable(GL_TEXTURE_2D);

	

	


	//glEnable(GL_LIGHT0);
	Bindings::Instance()->Update();
	CmdSys::Instance()->ExecBuffer();

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	camera1.Update(true);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(camera1.GetPM());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(camera1.GetVM());
	//cube.Render();
	
	wardroid->Render();
	testVBO->Render();
	deadworld->Render();

	static bool done = false;

	if(!done)
	{
		testVBO->Translate(Vec3f(0,3,-15));
		wardroid->Translate(Vec3f(0,3,-15));
		wardroid->Rotate(-90,Vec3f(0,1,0));
		wardroid->Scale(Vec3f(1,3,1));
		//testVBO->Scale(Vec3f(3,3,3));
		done = true;
	}



	deadworld->Rotate(0.1,Vec3f(0,1,0));
	
	
	
	PhysicsObjManager::Instance()->Update();
	
	player1.Update(camera1.GetPos(),camera1.GetTgt());
	
	static Texture tex("textures/wdworld/granite_256x256.png");

	static bool loaded = false;

	if(!loaded)
	{
		tex.Load_Texture();
		loaded = true;
	}

	//glPushMatrix();glBindTexture(GL_TEXTURE_2D, tex.Get_texhandle());
	ShaderManager::Instance()->Disable_shader("point");
	//ShaderManager::Instance()->Disable_shader("point");
	// Draw ground
	////ShaderManager::Instance()->Disable_shader(0);

	
	
	/*glBegin(GL_QUADS);
		glNormal3f(0,0,1);
		//glTexCoord2f(0,0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-5, 1.0f, 0);
		//glTexCoord2f(0,1);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(5, 0.0f,  0);
		//glTexCoord2f(1,1);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(5, 11.0f, 0);
		//glTexCoord2f(1,0);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-5, 11.0f, 0);
		
	glEnd();*/
	
	/*glPushMatrix();
	glTranslated(0,-5,0);
	glBegin(GL_TRIANGLES);
		glNormal3f(0,1,0);
		glTexCoord2f(0,0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-50, 0.0f, -50);
		glNormal3f(0,1,0);
		glTexCoord2f(0,1);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-50, 0.0f,  50);
		glNormal3f(0,1,0);
		glTexCoord2f(1,0);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( 50, 0.0f, -50);
		
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0,1,0);
		glTexCoord2f(0,1);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-50, 0.0f,  50);
		glTexCoord2f(1,1);
		glNormal3f(0,1,0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f( 50, 0.0f,  50);
		glTexCoord2f(1,0);
		glNormal3f(0,1,0);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f( 50, 0.0f, -50);
		
	glEnd();

	glPopMatrix();

	*/

	glPushMatrix();
	glTranslated(0,0,6);


	ShaderManager::Instance()->Enable_shader("simple");
	glTranslated(0,-4,0);
	glRotated(45,0,1,0);
	glBindTexture(GL_TEXTURE_2D,tex.Get_texhandle());
	glutSolidCube(3);
	glPopMatrix();

	const int size = 2048;
    if (!ID) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 1440, 900, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    } else {
        glBindTexture(GL_TEXTURE_2D, ID);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 1440, 900, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        int w = (int) 1440;
        int h = (int) 900;
		w = w < size ? w : (int) size;
        h = h < size ? h : (int) size;
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, w, h, 0);
    }
	//glEnable(GL_TEXTURE_2D);
	////ShaderManager::Instance()->Enable_shader(0);
	//glBindTexture(GL_TEXTURE_2D,ID);
	
	
	//glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ShaderManager::Instance()->Enable_shader("brick");
	PhysicsObjManager::Instance()->Render_all();
	
	ShaderManager::Instance()->Enable_shader("heat");
	glPushMatrix();
	glTranslated(0,-2.6,6);

	glRotated(-90,1,0,0);

	glutSolidCone(1.0,2.5,10,10);

	glTranslated(-1,0,0);
	glutSolidCone(0.75,2.0,10,10);
	glTranslated(2,0,0);
	glutSolidCone(0.75,2.0,10,10);

	ShaderManager::Instance()->Disable_shader("heat");

	

	ShaderManager::Instance()->Enable_shader("simple");
	glTranslated(0,-4,0);

	glPopMatrix();

	offset-=0.01;

	if(offset<0)
	{
		offset = 6.2831;
	}

	ShaderManager::Instance()->Disable_shader("heat");


	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(light_pos.x,light_pos.y,light_pos.z);
	globe.Render();
	glPopMatrix();


	

    glutSwapBuffers();
	glFlush();

	//light_pos.x-=disp;
	
	//light_pos.y-=disp;

	if(light_pos.x<=-5)
	{
		disp*=-1;
	}

	if(light_pos.x>=6)
	{
		disp*=-1;
	}
	
} 

float mspeed = 0.25;

void MvForward()
{
	camera1.Move(mspeed);
}

void UnMvForward()
{
	camera1.Move(0.0);
}

void MvReverse()
{
	camera1.Move(-mspeed);
}

void UnMvReverse()
{
	camera1.Move(0.0);
}

void MvStrfLeft()
{
	camera1.Strafe(-mspeed);
}

void UnMvStrfLeft()
{
	camera1.Strafe(0.0);
	physupdate = true;
}

void MvStrfRight()
{
	camera1.Strafe(mspeed);
}

void UnMvStrfRight()
{
	camera1.Strafe(0.0);
}

void Exit()
{
	exit(0);
}

void Fire()
{
	player1.Attack();

}

void Changeto1()
{
	player1.Change_weapon(0);
}

void Changeto2()
{
	player1.Change_weapon(1);
}

void Sprint()
{
	mspeed=2;
}

void UnSprint()
{
	mspeed=0.25;
}

int woo = 0;
void switchRender()
{
	switch(woo)
	{
	case 0:
		testVBO->Shader_Switch(ON);
		//testVBO->Set_DrawStyle(WIREFRAME);
		woo++;
		break;
	case 1:
		testVBO->Shader_Switch(OFF);
		//testVBO->Set_DrawStyle(POLYGONAL);
		woo++;
		break;
	case 2:
		woo = 0;
		break;
	default:
		woo = 0;
		break;
	}
}

void initCmds()
{
	CmdSys::Instance()->AddCmd("+forward", MvForward);
	CmdSys::Instance()->AddCmd("-forward", UnMvForward);
	CmdSys::Instance()->AddCmd("+reverse", MvReverse);
	CmdSys::Instance()->AddCmd("-reverse", UnMvReverse);
	CmdSys::Instance()->AddCmd("+strfleft", MvStrfLeft);
	CmdSys::Instance()->AddCmd("-strfleft", UnMvStrfLeft);
	CmdSys::Instance()->AddCmd("+strfright", MvStrfRight);
	CmdSys::Instance()->AddCmd("-strfright", UnMvStrfRight);
	CmdSys::Instance()->AddCmd("+exit", Exit);
	CmdSys::Instance()->AddCmd("+fire", Fire);
	CmdSys::Instance()->AddCmd("-fire", Fire);
	CmdSys::Instance()->AddCmd("+fires", Fire);
	CmdSys::Instance()->AddCmd("+changeto1", Changeto1);
	CmdSys::Instance()->AddCmd("+changeto2", Changeto2);
	CmdSys::Instance()->AddCmd("+sprint", Sprint);
	CmdSys::Instance()->AddCmd("-sprint", UnSprint);

	CmdSys::Instance()->AddCmd("+switchrender", switchRender);

	Bindings::Instance()->BindKey('w',"+forward");
	Bindings::Instance()->BindKey('s',"+reverse");
	Bindings::Instance()->BindKey('a',"+strfleft");
	Bindings::Instance()->BindKey('d',"+strfright");
	Bindings::Instance()->BindKey(27,"+exit");
	Bindings::Instance()->BindMouse(MOUSE_LEFT,"+fires");
	Bindings::Instance()->BindKey(' ',"+fires");
	Bindings::Instance()->BindKey('1',"+changeto1");
	Bindings::Instance()->BindKey('2',"+changeto2");
	Bindings::Instance()->BindMouse(MOUSE_RIGHT,"+switchrender");
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(0,0);

	camera1.LookAt(init_pos,init_target,init_up);

	player1.Pick_up_weapon(new BallShooter);
	player1.Pick_up_weapon(new RhombicDodecahedronShooter);

	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Create light components
	float ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuseLight[] = { 1.0f, 1.0f, 1.0, 1.0f };
	float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);*/


	
																	
}

float frequency = 20;
float speed = 10;
float fade = 0.85;

void main(int argc, char **argv) 
{

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1440,900);
	glutCreateWindow("Three Dee Warudo - Tutorial");

	initCmds();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutPassiveMotionFunc(MouseMotion);
	glutMotionFunc(MouseMotion);
	glutMouseFunc(MouseClick);
	glutKeyboardFunc(KeyDn);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SKeyDn);
	glutSpecialUpFunc(SKeyUp);



	glutIgnoreKeyRepeat(1);
	

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	glewInit();

	WFModelFactory::Instance()->Set_Resource_loc("3DeeModel/","textures/wdworld/");



	ShaderMode::Instance()->Set_ShaderMode(GLSL);
	testVBO = new ThreeDeeModel("wardroid.obj");testVBO->Set_Shader("point");
	deadworld = new ThreeDeeModel("deadworld.obj");deadworld->Set_Shader("point");
	wardroid = new ThreeDeeModel("wardroid.obj");wardroid->Set_Shader("point");
	rocket = new ThreeDeeModel("rocket.obj");rocket->Set_Shader("simple");
	ShaderFactory* _SF = ShaderFactory::Instance();
	ShaderManager* _SM = ShaderManager::Instance();
	UniformVarFactory* _UVF = UniformVarFactory::Instance();

	_SM->Add_Shader_program("point",_SF->Create("Shaders/point_light.vert","Shaders/point_light.frag"));

	_SM->Set_Shader_uni_var("point",
		_UVF->Create("LightPos",&light_pos));
	_SM->Set_Shader_uni_var("point",
	_UVF->Create("Brightness",new float(3.0f)));
	/*_SM->Set_Shader_uni_var(0,
	_UVF->Create("BaseColor",new Vec3f(1.0f,0.4f,1.0f)));*/
	/*_SM->Set_Shader_uni_var(0,
	_UVF->Create("MixRatio",new float(1.0f)));
	_SM->Set_Shader_uni_var(0,
	_UVF->Create("EnvMap",new float(4.0f)));*/
	
	_SM->Add_Shader_program("brick",_SF->Create("Shaders/brick.vert","Shaders/brick.frag"));

	_SM->Set_Shader_uni_var("brick",
	_UVF->Create("BrickColor",new Vec3f(1.0f, 1.0f, 1.0f)));
	_SM->Set_Shader_uni_var("brick",
	_UVF->Create("MortarColor",new Vec3f(0.0f, 1.0f, 1.0f)));
	_SM->Set_Shader_uni_var("brick",
	_UVF->Create("BrickSize",new Vector2<float>(0.30f,0.15f)));
	_SM->Set_Shader_uni_var("brick",
	_UVF->Create("BrickPct",new Vector2<float>(0.90f, 0.85f)));
	/*_SM->Set_Shader_uni_var(1, 
	_UVF->Create("LightPosition",&light_pos));*/

	_SM->Add_Shader_program("simple",_SF->Create("Shaders/simpletex.vert","Shaders/simpletex.frag"));

	_SM->Add_Shader_program("heat",_SF->Create("Shaders/heathaze.vert","Shaders/heathaze.frag"));
	_SM->Set_Shader_uni_var("heat",
	_UVF->Create("FrameBuffer",&ID));
	_SM->Set_Shader_uni_var("heat",
	_UVF->Create("FrameWidth",new float(2048)));
	_SM->Set_Shader_uni_var("heat",
	_UVF->Create("FrameHeight",new float(2048)));
	_SM->Set_Shader_uni_var("heat",
	_UVF->Create("Frequency",&frequency));
	_SM->Set_Shader_uni_var("heat",
	_UVF->Create("Speed",&speed));
	_SM->Set_Shader_uni_var("heat",
	_UVF->Create("Fade",&fade));
	_SM->Set_Shader_uni_var("heat",
	_UVF->Create("Offset",&offset));
	// enter GLUT event processing cycle
	glutMainLoop();
}