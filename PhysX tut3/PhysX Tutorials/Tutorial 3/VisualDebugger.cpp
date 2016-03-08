#include "VisualDebugger.h"
#include <vector>
#include "Extras\Camera.h"
#include "Extras\Renderer.h"
#include "Extras\HUD.h"

namespace VisualDebugger
{
	using namespace physx;

	enum RenderMode
	{
		DEBUG,
		NORMAL,
		BOTH
	};

	enum HUDState
	{
		EMPTY = 0,
		HELP = 1,
		PAUSE = 2,
		WINSCREEN = 3
	};

	//function declarations
	void KeyHold();
	void KeySpecial(int key, int x, int y);
	void KeyRelease(unsigned char key, int x, int y);
	void KeyPress(unsigned char key, int x, int y);

	void motionCallback(int x, int y);
	void mouseCallback(int button, int state, int x, int y);
	void exitCallback(void);

	void RenderScene();
	void ToggleRenderMode();
	void HUDInit();


	///simulation objects
	Camera* camera;
	PhysicsEngine::MyScene* scene;
	PxReal delta_time = 1.f/60.f;
	PxReal gForceStrength = 20;
	RenderMode render_mode = NORMAL;
	const int MAX_KEYS = 256;
	bool key_state[MAX_KEYS];
	bool hud_show = true;
	HUD hud;
	PxReal leftToRight = 0;
	bool disableMove = false;
	PxReal velocity = 1;

	//Init the debugger
	void Init(const char *window_name, int width, int height)
	{
		///Init PhysX
		PhysicsEngine::PxInit();
		scene = new PhysicsEngine::MyScene();
		scene->Init();

		///Init renderer
		Renderer::BackgroundColor(PxVec3(150.f/255.f,150.f/255.f,150.f/255.f));
		Renderer::SetRenderDetail(40);
		Renderer::InitWindow(window_name, width, height);
		Renderer::Init();

		camera = new Camera(PxVec3(0.0f, 100.0f, -5.0f), PxVec3(0.0f, -90.0f, PxPi), 5.0f);

		//initialise HUD
		HUDInit();

		///Assign callbacks
		//render
		glutDisplayFunc(RenderScene);

		//keyboard
		glutKeyboardFunc(KeyPress);
		glutSpecialFunc(KeySpecial);
		glutKeyboardUpFunc(KeyRelease);

		//mouse
		glutMouseFunc(mouseCallback);
		glutMotionFunc(motionCallback);

		//exit
		atexit(exitCallback);

		//init motion callback
		motionCallback(0,0);
	}

	void HUDInit()
	{
		// ===============
		// initialise HUD
		// ===============

		//add an empty screen
		hud.AddLine(EMPTY, "");
		//add a help screen
		//hud.AddLine(HELP, " Simulation");
		//hud.AddLine(HELP, "    F9 - select next actor");
		//hud.AddLine(HELP, "    F10 - pause");
		//hud.AddLine(HELP, "    F12 - reset");

		// Instructions
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "                                                               Instructions!");
		hud.AddLine(HELP, "                                                             F5 - help on/off");
		hud.AddLine(HELP, "                                           Right Arrow, Left Arrow - Aim Left or Right!");
		hud.AddLine(HELP, "                                        Top Arrow, Bottom Arrow - Add or Remove Velocity!");
		hud.AddLine(HELP, "                Hold Space once you have selected the direction and amount of velocity you want!");
		hud.AddLine(HELP, "                                                    Press F11 to reset the ball!");
		//hud.AddLine(HELP, "    F6 - shadows on/off");
		//hud.AddLine(HELP, "    F7 - render mode");
		//hud.AddLine(HELP, " Camera");
		//hud.AddLine(HELP, "    W,S,A,D,Q,Z - forward,backward,left,right,up,down");
		//hud.AddLine(HELP, "    mouse + click - change orientation");
		//hud.AddLine(HELP, "    F8 - reset view");
		//hud.AddLine(HELP, " Force (applied to the selected actor)");
		//hud.AddLine(HELP, "    I,K,J,L,U,M - forward,backward,left,right,up,down");

		// Pause Screen
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "   Simulation paused. Press F10 to continue.");

		// Win Screen
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "       YOU WIN!");
		//set font size for all screens
		hud.FontSize(0.018f);
		hud.FontSize(0.1f, 3);
		//set font color for all screens
		hud.Color(PxVec3(0.f,0.f,0.f));
	}

	//Start the main loop
	void Start()
	{ 
		glutMainLoop(); 
	}

	//Render the scene and perform a single simulation step
	void RenderScene()
	{
		//handle pressed keys
		KeyHold();
		PxReal leftToRight = 0;

		//start rendering
		Renderer::Start(camera->getEye(), camera->getDir());

		if ((render_mode == DEBUG) || (render_mode == BOTH))
		{
			Renderer::Render(scene->Get()->getRenderBuffer());
		}

		if ((render_mode == NORMAL) || (render_mode == BOTH))
		{
			std::vector<PxActor*> actors = scene->GetAllActors();
			if (actors.size())
				Renderer::Render(&actors[0], (PxU32)actors.size());
		}

		//adjust the HUD state
		if (hud_show)
		{
			if (scene->Pause())
			{
				hud.ActiveScreen(PAUSE);
			}
			else if (scene->triggerBool)
			{
				hud.ActiveScreen(WINSCREEN);
			}
			else
			{
				hud.ActiveScreen(HELP);
			}
		}
		else
		{
			hud.ActiveScreen(EMPTY);
			if (scene->triggerBool)
			{
				hud_show = true;
			}
		}

		//render HUD
		hud.Render();

		//finish rendering
		Renderer::Finish();

		//perform a single simulation step
		scene->Update(delta_time);
	}

	//user defined keyboard handlers
	void UserKeyPress(int key)
	{
		switch (toupper(key))
		{
		//implement your own
		case 'R':
			scene->ExampleKeyPressHandler();
			break;
		default:
			break;
		}
	}

	void UserKeyRelease(int key)
	{
		switch (toupper(key))
		{
		//implement your own
		case 'R':
			scene->ExampleKeyReleaseHandler();
			break;
		default:
			break;
		}
	}

	void UserKeyHold(int key)
	{
	}

	//handle camera control keys
	void CameraInput(int key)
	{
		switch (toupper(key))
		{
		case 'W':
			camera->MoveForward(delta_time);
			break;
		case 'S':
			camera->MoveBackward(delta_time);
			break;
		case 'A':
			camera->MoveLeft(delta_time);
			break;
		case 'D':
			camera->MoveRight(delta_time);
			break;
		case 'Q':
			camera->MoveUp(delta_time);
			break;
		case 'Z':
			camera->MoveDown(delta_time);
			break;
		default:
			break;
		}
	}

	//handle force control keys
	void ForceInput(int key)
	{	
		if (!scene->GetSelectedActor())
			return;

		switch (toupper(key))
		{
			// Force controls on the selected actor
		case 'I': //forward
			scene->GetSelectedActor()->addForce(PxVec3(0, 0, 1)*gForceStrength);
			cout << "up";
			break;
		case 'K': //backward
			scene->GetSelectedActor()->addForce(PxVec3(0, 0, -1)*gForceStrength);
			break;
		case 'J': //left
			scene->GetSelectedActor()->addForce(PxVec3(1, 0, 0)*gForceStrength);
			break;
		case 'L': //right
			scene->GetSelectedActor()->addForce(PxVec3(-1, 0, 0)*gForceStrength);
			break;
		case 'U': // Top Left
			scene->GetSelectedActor()->addForce(PxVec3(2, 0, 1)*gForceStrength);
			break;
		case 'O': // Top Right
			scene->GetSelectedActor()->addForce(PxVec3(-0.5, 0, 0)*gForceStrength);
			break;
		case ' ':
			disableMove = true;
			scene->GetSelectedActor()->addForce(PxVec3(leftToRight, 0, 1) * velocity);
			break;
		default:
			break;
		}
	}
	

	///handle special keys
	void KeySpecial(int key, int x, int y)
	{
		bool AddOne = true;
		//simulation control
		switch (key)
		{
			//display control
		case GLUT_KEY_F5:
			//hud on/off
			hud_show = !hud_show;
			break;
		case GLUT_KEY_F6:
			//shadows on/off
			Renderer::ShowShadows(!Renderer::ShowShadows());
			break;
		case GLUT_KEY_F7:
			//toggle render mode
			ToggleRenderMode();
			break;
		case GLUT_KEY_F8:
			//reset camera view
			camera->Reset();
			break;

			//simulation control
		case GLUT_KEY_F9:
			//select next actor
			scene->SelectNextActor();
			break;
		case GLUT_KEY_F10:
			//toggle scene pause
			scene->Pause(!scene->Pause());
			break;
		case GLUT_KEY_F11:
			//resect scene
			disableMove = false;
			scene->GetSelectedActor()->setGlobalPose(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)));
			scene->GetSelectedActor()->putToSleep();
			scene->GetSelectedActor()->clearForce();
			scene->GetSelectedActor()->clearTorque();
			break;
		case GLUT_KEY_F12:
			//resect scene
			disableMove = false;
			scene->Reset();
			break;
		case GLUT_KEY_LEFT:
			while (leftToRight < 2 && disableMove == false)
			{
				leftToRight = leftToRight + 0.1;
				cout << "Direction: " << leftToRight << endl;
				break;
			}
			break;
		case GLUT_KEY_RIGHT:
			while (leftToRight > -2 && disableMove == false)
			{

				leftToRight = leftToRight - 0.1;
				cout << "Direction: " << leftToRight << endl;
				break;
			}
			break;
		case GLUT_KEY_UP:
			while (disableMove == false)
			{
				velocity++;
				cout << "Velocity: " << velocity << endl;
				break;
			}
			break;
		case GLUT_KEY_DOWN:
			while (disableMove == false)
			{
				velocity--;
				cout << "Velocity: " << velocity << endl;
				break;
			}
			break;
		default:
			break;
		}
	}

	//handle single key presses
	void KeyPress(unsigned char key, int x, int y)
	{
		//do it only once
		if (key_state[key] == true)
			return;

		key_state[key] = true;

		//exit
		if (key == 27)
			exit(0);

		UserKeyPress(key);
	}

	//handle key release
	void KeyRelease(unsigned char key, int x, int y)
	{
		key_state[key] = false;
		UserKeyRelease(key);
	}

	//handle holded keys
	void KeyHold()
	{
		for (int i = 0; i < MAX_KEYS; i++)
		{
			if (key_state[i]) // if key down
			{
				CameraInput(i);
				ForceInput(i);
				UserKeyHold(i);
			}
		}
	}

	///mouse handling
	int mMouseX = 0;
	int mMouseY = 0;

	void motionCallback(int x, int y)
	{
		int dx = mMouseX - x;
		int dy = mMouseY - y;

		camera->Motion(dx, dy, delta_time);

		mMouseX = x;
		mMouseY = y;
	}

	void mouseCallback(int button, int state, int x, int y)
	{
		mMouseX = x;
		mMouseY = y;
	}

	void ToggleRenderMode()
	{
		if (render_mode == NORMAL)
			render_mode = DEBUG;
		else if (render_mode == DEBUG)
			render_mode = BOTH;
		else if (render_mode == BOTH)
			render_mode = NORMAL;
	}

	///exit callback
	void exitCallback(void)
	{
		delete camera;
		delete scene;
		PhysicsEngine::PxRelease();
	}
}

