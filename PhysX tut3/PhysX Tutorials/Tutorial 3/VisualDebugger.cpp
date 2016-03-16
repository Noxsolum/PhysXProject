#include "VisualDebugger.h"
#include <vector>
#include "Extras\Camera.h"
#include "Extras\Renderer.h"
#include "Extras\HUD.h"

namespace VisualDebugger
{
	using namespace physx;
	using namespace std;

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
		WINSCREEN = 3,
		INDICATOR = 4,
		NEXTLEVEL = 5
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
	PxReal delta_time = 1.f / 60.f;
	PxReal gForceStrength = 20;
	RenderMode render_mode = NORMAL;
	const int MAX_KEYS = 256;
	bool key_state[MAX_KEYS];
	bool hud_show = true;
	HUD hud;
	float leftToRight = 0;
	int direction = leftToRight * 10;
	bool disableMove = true;
	int velocity = 0;
	std::string velocityOut = "Velocity: " + std::to_string(velocity);
	std::string directionOut = "Direction: " + std::to_string(direction);

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

		camera = new Camera(PxVec3(0.0f, 105.0f, -5.0f), PxVec3(0.0f, -90.0f, PxPi), 5.0f);

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

	// ===============
	// initialise HUD
	// ===============
	void HUDInit()
	{
		// =================
		// Empty HUD Screen
		// =================
		hud.AddLine(EMPTY, "");

		// =============
		// Instructions
		// =============
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "                                                        Instructions!");		
		hud.AddLine(HELP, "                              Add Velocity: Top Arrow / Remove Velocity: Bottom Arrow");
		hud.AddLine(HELP, "         Postive Direction: Left - Left Arrow / Negative Direction: Right - Right Arrow");
		hud.AddLine(HELP, "       Hold Space once you have selected the direction and amount of velocity you want!");
		hud.AddLine(HELP, "                                              Press F11 to reset the ball!");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, "                                                         F5 - To Begin!");

		// =============
		// Pause Screen
		// =============
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "   Simulation paused. Press F10 to continue.");

		// ==========
		// Indicator
		// ==========
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, "");
		hud.AddLine(INDICATOR, velocityOut);
		hud.AddLine(INDICATOR, directionOut);

		// ===========
		// Next Level 
		// ===========
		hud.AddLine(NEXTLEVEL, "");
		hud.AddLine(NEXTLEVEL, "");
		hud.AddLine(NEXTLEVEL, "");
		hud.AddLine(NEXTLEVEL, "          Level Complete!");
		hud.AddLine(NEXTLEVEL, "     Press F4 to Continue!");

		// ===========
		// Win Screen
		// ===========
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "");
		hud.AddLine(WINSCREEN, "                You Win!!");
		hud.AddLine(WINSCREEN, "              Well Done!!");

		// ==========
		// Font Size
		// ==========
		hud.FontSize(0.020f);
		hud.FontSize(0.06f, NEXTLEVEL);
		hud.FontSize(0.06f, WINSCREEN);
		hud.FontSize(0.025f, 4);

		// ===========
		// Font Color
		// ===========
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
			else if (scene->triggerBool && scene->Winner == false)
			{
				hud.ActiveScreen(NEXTLEVEL);
			}
			else if (scene->triggerBool && scene->Winner == true)
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
			hud.ActiveScreen(INDICATOR);
			if (scene->triggerBool)
			{
				hud_show = true;
			}
		}

		//render HUD
		hud.Render();

		// =======================================
		// Dynamic HUD for Direction and Velocity
		// =======================================
		hud.Clear();
		HUDInit();
		int direction = leftToRight * 10;
		velocityOut = "   Velocity: " + std::to_string(velocity);
		directionOut = "   Direction: " + std::to_string(direction);

		//finish rendering
		Renderer::Finish();

		//perform a single simulation step
		scene->Update(delta_time);
	}

	// ===========================================
	// User Defined Keyboard Handlers - Key Press
	// ===========================================
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

	// =============================================
	// User Defined Keyboard Handlers - Key Release
	// =============================================
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

	// ==========================================
	// User Defined Keyboard Handlers - Key Hold
	// ==========================================
	void UserKeyHold(int key)
	{
	}

	// ===========================
	// handle camera control keys
	// ===========================
	/*
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
	} */
	
	// =======================
	// Handling the space bar
	// =======================
	void ForceInput(int key)
	{	
		if (!scene->GetSelectedActor())
			return;

		switch (toupper(key))
		{
		case ' ':
			disableMove = true;
			scene->GetSelectedActor()->setLinearVelocity(PxVec3(leftToRight, 0, 1) * velocity);
			break;
		default:
			break;
		}
	}

	// ====================
	// Handle Special Keys
	// ====================
	void KeySpecial(int key, int x, int y)
	{
		switch (key)
		{
		// ============================
		// Turn off HUD and Begin Game
		// ============================
		case GLUT_KEY_F5:
			disableMove = false;
			hud_show = !hud_show;
			break;
		// ==================
		// Shadows On or Off
		// ==================
		case GLUT_KEY_F6:
			Renderer::ShowShadows(!Renderer::ShowShadows());
			break;
		// ===================
		// Toggle Render Mode
		//====================
		case GLUT_KEY_F7:
			ToggleRenderMode();
			break;
		// ==================
		// Reset Camera View
		// ==================
		case GLUT_KEY_F8:
			camera->Reset();
			break;
		// ==================
		// Toggle Scene Pause
		// ==================
		case GLUT_KEY_F10:
			scene->Pause(!scene->Pause());
			break;
		// ===============
		// Reset the Ball
		// ===============
		case GLUT_KEY_F11:
			disableMove = false;
			scene->GetSelectedActor()->setGlobalPose(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)));
			scene->GetSelectedActor()->putToSleep();
			scene->GetSelectedActor()->clearForce();
			scene->GetSelectedActor()->clearTorque();
			break;
		// ==================
		// Refresh the Scene
		// ==================
		case GLUT_KEY_F4:
			//reset scene
			scene->Reset();
			leftToRight = 0;
			velocity = 0;
			disableMove = false;
			hud_show = false;
			break;
		// ======================
		// Setting the Direction
		// ======================
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
		// ======================
		// Setting the Velocity
		// ======================
		case GLUT_KEY_UP:
			while (velocity < 100 && disableMove == false)
			{
				velocity++;
				cout << "Velocity: " << velocity << endl;
				break;
			}
			break;
		case GLUT_KEY_DOWN:
			while (disableMove == false && velocity > 0)
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
				//CameraInput(i);
				ForceInput(i);
				UserKeyHold(i);
			}
		}
	}

	//mouse handling
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

