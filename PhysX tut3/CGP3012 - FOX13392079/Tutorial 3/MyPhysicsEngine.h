#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>
#include <math.h>

namespace PhysicsEngine
{
	using namespace std;

	// ==============
	// Level Counter
	// ==============
	static int LevelCount = 0;

	// ========
	// Colours
	// ========
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f), PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};

	// =============
	// Filter Group
	// =============
	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0		= (1 << 0),
			ACTOR1		= (1 << 1),
			ACTOR2		= (1 << 2)
			//add more if you need
		};
	};

	// ================
	// My Spring Walls
	// ================
	class SpringWalls
	{
		StaticBox* base;
		Box* top;
		vector<DistanceJoint*> springs;
		
	public:
		SpringWalls(const PxReal PosOrMin = PxReal(4.0f), const PxVec3 pose = PxVec3(-59.0f, 0.5f, 0.0f), const PxVec3& dimensionsBack = PxVec3(1.0f, 1.0f, 54.0f), PxReal stiffness = 7.0f, PxReal damping = 20.0f)
		{
			PxReal thickness = .1f;
			base = new StaticBox(PxTransform(PxVec3(pose)), PxVec3(dimensionsBack.x, dimensionsBack.y, dimensionsBack.z));
			top = new Box(PxTransform(PxVec3(pose.x + PosOrMin, pose.y, pose.z)), PxVec3(dimensionsBack.x, dimensionsBack.y, dimensionsBack.z), PxReal(1.0f));
			springs.resize(6);
			springs[0] = new DistanceJoint(base, PxTransform(PxVec3(pose.x, pose.y, pose.z + 22.0f)), top, PxTransform(PxVec3(-pose.x + PosOrMin, pose.y, pose.z + 22.0f)));
			springs[1] = new DistanceJoint(base, PxTransform(PxVec3(pose.x, pose.y, pose.z - 22.0f)), top, PxTransform(PxVec3(-pose.x + PosOrMin, pose.y, pose.z - 22.0f)));
			springs[2] = new DistanceJoint(base, PxTransform(PxVec3(pose.x, pose.y, pose.z + 14.0f)), top, PxTransform(PxVec3(-pose.x + PosOrMin, pose.y, pose.z + 14.0f)));
			springs[3] = new DistanceJoint(base, PxTransform(PxVec3(pose.x, pose.y, pose.z - 14.0f)), top, PxTransform(PxVec3(-pose.x + PosOrMin, pose.y, pose.z - 14.0f)));
			springs[4] = new DistanceJoint(base, PxTransform(PxVec3(pose.x, pose.y, pose.z + 5.0f)), top, PxTransform(PxVec3(-pose.x + PosOrMin, pose.y, pose.z + 5.0f)));
			springs[5] = new DistanceJoint(base, PxTransform(PxVec3(pose.x, pose.y, pose.z - 5.0f)), top, PxTransform(PxVec3(-pose.x + PosOrMin, pose.y, pose.z - 5.0f)));
			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
				springs[i]->Get()->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
			}
		}

		void AddToScene(Scene* scene)
		{
			scene->Add(base);
			scene->Add(top);
		}

		void Color(PxVec3 color, PxVec3 colortwo)
		{
			base->Color(color);
			top->Color(colortwo);
		}

		void Material(PxMaterial* material)
		{
			base->Material(material);
			top->Material(material);
		}

		~SpringWalls()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}

	};

	// ===============
	// Collison Class
	// ===============
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		bool trigger;
		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						LevelCount++;
						trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
					
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	// ======================================================================================================
	// Filter Shader - If I put a filter, it would bounce in the goal causing my Level boolean to mess up!!!
	// ======================================================================================================
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0, PxFilterObjectAttributes attributes1,	PxFilterData filterData1, PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;

		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
		}

		return PxFilterFlags();
	};

	// ===================
	// Custom Scene Class
	// ===================
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box, * box2;
		MySimulationEventCallback* my_callback;
		Rectangle* borderTop, *borderBot, *borderLeft, *borderRight, *Indicator2;
		StaticSphere* planet, * planet2;
		DynamSphere* meteor, *planet3, *Indicator;
		RevoluteJoint* indieJoint, *planetJoint;
		dSixJoint *d6Joint;
		Goal* newGoal;
		SpringWalls* SpringLeft, *SpringRight;
		Obstacle* obstacle1, * obstacle2;
		ObstacleTwo* obstacle3, *obstacle4;
	
	public:
		bool triggerBool = false;
		bool Winner = false;
		MyScene() : Scene() {};

		// ======================
		// Set the Visualisation
		// ======================
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			
		}

		// ==========================
		// Creating the Custom Scene
		// ==========================
		virtual void CustomInit() 
		{
			SetVisualisation();

			// ===================
			// Creating Materials
			// ===================
			PxMaterial* bouncyMat = CreateMaterial(0.0f, 0.0f, 1.0f);
			PxMaterial* SUPERFRICTION = CreateMaterial(0.0f, 0.1f, 0.0f);
			GetMaterial()->setDynamicFriction(0.0f);

			// ==========
			// Callbacks
			// ==========
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);

			// =======
			// Levels
			// =======
			switch (LevelCount)
			{
			case 0:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal();
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(-550.0f, 1.0f, -20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(-550.0f, 1.0f, -15.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				
				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);
				
				// =======
				// Joints
				// =======
				//planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.0f, 10.0f)));
				//planetJoint->DriveVelocity(PxReal(6.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);
				obstacle1->Material(bouncyMat);
				obstacle2->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				Add(planet);
				//Add(planet2);
				//Add(planet3);				
				Add(obstacle1);
				Add(obstacle2);
				//Add(obstacle3);
				//Add(obstacle4);			
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderTop);
				Add(borderLeft);
				Add(borderRight);
				break;
			case 1:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal();
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(0.0f, 0.0f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(0.0f, 1.0f, -20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(-550.0f, 1.0f, -15.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));

				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				//planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.0f, 10.0f)));
				//planetJoint->DriveVelocity(PxReal(6.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);
				obstacle1->Material(bouncyMat);
				obstacle2->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				Add(planet);
				Add(planet2);
				//Add(planet3);				
				//Add(obstacle1);
				//Add(obstacle2);
				//Add(obstacle3);
				//Add(obstacle4);			
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderTop);
				Add(borderLeft);
				Add(borderRight);
				break;
			case 2:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal();
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(15.0f, 1.0f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(-15.0f, 1.0f, -20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(-550.0f, 1.0f, -15.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));

				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				//planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.5f, 10.0f)));
				//planetJoint->DriveVelocity(PxReal(6.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);
				obstacle1->Material(bouncyMat);
				obstacle2->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				Add(planet);
				Add(planet2);
				//Add(planet3);
				//Add(obstacle1);
				//Add(obstacle2);
				Add(obstacle3);
				//Add(obstacle4);
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderLeft);
				Add(borderTop);
				Add(borderRight);
				break;
			case 3:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal();
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(500.0f, 1.0f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(550.0f, 1.0f, -20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.5f, 10.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(0.0f, 0.5f, 12.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, -5.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));


				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, -5.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.5f, 15.0f)));
				planetJoint->DriveVelocity(4.0f);
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				//Add(planet);
				//Add(planet2);
				Add(planet3);
				Add(obstacle1);
				//Add(obstacle2);
				//Add(obstacle3);
				//Add(obstacle4);
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderLeft);
				Add(borderTop);
				Add(borderRight);
				break;
			case 4:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal();
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(500.0f, 1.0f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(550.0f, 1.0f, -20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.5f, 10.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(15.0f, 0.5f, 15.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 15.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));


				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.5f, 15.0f)));
				planetJoint->DriveVelocity(PxReal(4.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);
				
				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				//Add(planet);
				//Add(planet2);
				Add(planet3);
				Add(obstacle1);
				Add(obstacle2);
				Add(obstacle3);
				//Add(obstacle4);
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderLeft);
				Add(borderTop);
				Add(borderRight);
				break;
			case 5:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal(PxVec3(25.0f, 0.5f, 50.0f));
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(40.0f, 1.0f, 25.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(550.0f, 1.0f, -20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.5f, 10.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));


				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.5f, 15.0f)));
				planetJoint->DriveVelocity(PxReal(3.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				Add(planet);
				//Add(planet2);
				Add(planet3);
				Add(obstacle1);
				//Add(obstacle2);
				//Add(obstacle3);
				//Add(obstacle4);
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderLeft);
				Add(borderTop);
				Add(borderRight);
				break;
			case 6:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal(PxVec3(0.0f, 0.5f, 50.0f));
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(0.0f, 1.0f, 30.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(550.0f, 1.0f, -20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.5f, 10.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(15.0f, 0.5f, 0.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));


				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 5.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.5f, 15.0f)));
				planetJoint->DriveVelocity(PxReal(-3.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				Add(planet);
				//Add(planet2);
				Add(planet3);
				//Add(obstacle1);
				//Add(obstacle2);
				Add(obstacle3);
				Add(obstacle4);
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderLeft);
				Add(borderTop);
				Add(borderRight);
				break;
			case 7:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal(PxVec3(-20.0f, 0.5f, 50.0f));
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(550.0f, 1.0f, 30.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(0.0f, 1.0f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.5f, 25.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(0.0f, 0.5f, -15.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(15.0f, 0.5f, -15.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, -15.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));


				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(-30.0f, 1.0f, 14.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.5f, 15.0f)));
				planetJoint->DriveVelocity(PxReal(-3.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				//Add(planet);
				Add(planet2);
				Add(planet3);
				//Add(obstacle1);
				//Add(obstacle2);
				Add(obstacle3);
				Add(obstacle4);
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderLeft);
				Add(borderTop);
				Add(borderRight);
				break;
			case 8:
				triggerBool = false;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal(PxVec3(0.0f, 0.5f, 50.0f));
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(20.0f, 1.0f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(-20.0f, 1.0f, -20.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.5f, 25.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(0.0f, 0.5f, -15.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(5.0f, 0.5f, -10.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-5.0f, 0.5f, 10.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));


				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.5f, 5.0f)));
				planetJoint->DriveVelocity(PxReal(-3.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				Add(planet);
				Add(planet2);
				Add(planet3);
				//Add(obstacle1);
				//Add(obstacle2);
				Add(obstacle3);
				Add(obstacle4);
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderLeft);
				Add(borderTop);
				Add(borderRight);
				break;
			case 9:
				triggerBool = false;
				Winner = true;

				// =================
				// Creating Objects
				// =================
				plane = new Plane();
				newGoal = new Goal(PxVec3(0.0f, 0.5f, 50.0f));
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
				planet = new StaticSphere(PxTransform(PxVec3(20.0f, 1.0f, 35.0f)), PxReal(2.0f), PxReal(1.0f));
				planet2 = new StaticSphere(PxTransform(PxVec3(-20.0f, 1.0f, 35.0f)), PxReal(2.0f), PxReal(1.0f));
				planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.5f, 25.0f)), PxReal(2.0f), PxReal(1.0f));
				obstacle1 = new Obstacle(PxTransform(PxVec3(12.0f, 0.5f, 0.0f)));
				obstacle2 = new Obstacle(PxTransform(PxVec3(-12.0f, 0.5f, 0.0f)));
				obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, -12.0f)));
				obstacle4 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 12.0f)));
				SpringRight = new SpringWalls();
				SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
				borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
				borderRight = new Rectangle(PxTransform(PxVec3(-65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
				borderLeft = new Rectangle(PxTransform(PxVec3(65.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));


				// =============
				// Setting Name
				// =============

				// ==================
				// Colouring Objects
				// ==================
				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				newGoal->Color(color_palette[1]);
				meteor->Color(color_palette[4]);
				planet->Color(color_palette[3]);
				planet2->Color(color_palette[3]);
				planet3->Color(color_palette[3]);
				obstacle1->Color(color_palette[3]);
				obstacle2->Color(color_palette[3]);
				obstacle3->Color(color_palette[3]);
				obstacle4->Color(color_palette[3]);
				SpringRight->Color(color_palette[5], color_palette[1]);
				SpringLeft->Color(color_palette[5], color_palette[1]);
				borderBot->Color(color_palette[5]);
				borderTop->Color(color_palette[5]);
				borderRight->Color(color_palette[5]);
				borderLeft->Color(color_palette[5]);

				// =======
				// Joints
				// =======
				planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, -19.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.5f, 10.0f)));
				planetJoint->DriveVelocity(PxReal(-3.0f));
				d6Joint = new dSixJoint(NULL, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)), meteor, PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				d6Joint->SetMotion(PxD6Axis::eX, PxD6Motion::eFREE);
				d6Joint->SetMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

				// =========
				// Triggers
				// =========
				newGoal->SetTrigger();

				// ==========
				// Materials
				// ==========
				SpringLeft->Material(bouncyMat);
				SpringRight->Material(bouncyMat);

				// =============
				// Add to Scene
				// =============
				Add(plane);
				newGoal->AddToScene(this);
				Add(meteor);
				Add(planet);
				Add(planet2);
				Add(planet3);
				Add(obstacle1);
				Add(obstacle2);
				//Add(obstacle3);
				Add(obstacle4);
				SpringRight->AddToScene(this);
				SpringLeft->AddToScene(this);
				Add(borderBot);
				Add(borderLeft);
				Add(borderTop);
				Add(borderRight);
				break;
			default:
				break;
			}

			/*
			//SetVisualisation();			

			//// ==========
			//// Materials
			//// ==========
			////PxMaterial* newMat = CreateMaterial(0.0f, 0.5f, 0.0f);
			//GetMaterial()->setDynamicFriction(0.0f);

			/////Initialise and set the customised event callback
			//my_callback = new MySimulationEventCallback();
			//px_scene->setSimulationEventCallback(my_callback);

			//plane = new Plane();
			//goal = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
			//planet = new StaticSphere(PxTransform(PxVec3(0.0f, 1.0f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
			//meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)));
			////tramp = new Trampoline(50.0f, 50.0f);
			//borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
			//borderRight = new Rectangle(PxTransform(PxVec3(-59.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
			//borderLeft = new Rectangle(PxTransform(PxVec3(59.0f, 0.5f, 0.0f)), PxVec3(5.0f, 1.0f, 54.0f), PxReal(5.0f));
			//borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
			////Indicator = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -40.0f)));

			////rectangle->Material(newMat);

			//plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));
			//goal->Color(color_palette[2]);
			//planet->Color(color_palette[3]);
			//meteor->Color(color_palette[4]);
			//borderBot->Color(color_palette[5]);
			//borderLeft->Color(color_palette[5]);
			//borderRight->Color(color_palette[5]);
			//borderTop->Color(color_palette[5]);
			////Indicator->Color(color_palette[6]);

			////joint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 0.5f, -50.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), Indicator, PxTransform(PxVec3(0.0f, 0.5f, -10.0f)));
			////joint->SetLimits(PxReal(PxPi/2), PxReal(-PxPi/2));

			//goal->SetTrigger(true);

			//Add(plane);
			//Add(goal);
			//Add(planet);
			//Add(meteor);
			//Add(borderBot);
			//Add(borderLeft);
			//Add(borderTop);
			//Add(borderRight);
			//Add(Indicator);
			//tramp->AddToScene(this);

			//// const PxVec3& dimensions=PxVec3(5.f,5.f,5.f), PxReal stiffness=1.f, PxReal damping=1.f
			//tramp = new Trampoline(PxVec3(2.0f, 2.0f, 2.0f), PxReal(20.0f), PxReal(10.0f));
			////box->Material(newMat);
			////set collision filter flags
			//// box->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1);
			////use | operator to combine more actors e.g.
			//// box->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1 | FilterGroup::ACTOR2);
			////don't forget to set your flags for the matching actor as well, e.g.:
			//// box2->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);
			//box->Name("Box1");
			//RevoluteJoint joint(box, PxTransform(PxVec3(0.f, 5.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))), box2, PxTransform(PxVec3(0.f, 10.f, 0.f)));
			//tramp->AddToScene(this);
			//joint two boxes together
			//the joint is fixed to the centre of the first box, oriented by 90 degrees around the Y axis
			//and has the second object attached 5 meters away along the Y axis from the first object.
			//RevoluteJoint joint(box, PxTransform(PxVec3(0.f,0.f,0.f),PxQuat(PxPi/2,PxVec3(0.f,1.f,0.f))), box2, PxTransform(PxVec3(0.f,5.f,0.f)));
			*/
		}

		// =======================
		// Custom udpate function
		// =======================
		virtual void CustomUpdate() 
		{
			AddGravity(planet, meteor);
			AddGravity(planet2, meteor);
			AddGravityDynamic(planet3, meteor);

			if(my_callback->trigger)
			{
				triggerBool = true;
			}
		}

		// =======================
		// Custom udpate function
		// =======================
		void getDistance(DynamSphere* indie, DynamSphere* meteor)
		{
			PxTransform planetPose = ((PxRigidBody*)indie->Get())->getGlobalPose();
			PxTransform meteorPose = ((PxRigidBody*)meteor->Get())->getGlobalPose();

			PxReal px = planetPose.p.x;
			PxReal pz = planetPose.p.z;
			PxReal mx = meteorPose.p.x;
			PxReal mz = meteorPose.p.z;

			PxReal x = PxAbs(px) - PxAbs(mx);
			PxReal y = PxAbs(pz) - PxAbs(mz);
			PxReal z = PxSqrt((x*x) + (y*y));
		}

		// =============================
		// Add Gravity to Static Actors
		// =============================
		void AddGravity(StaticSphere* planet, DynamSphere* satellite)
		{
			PxTransform planetPose = ((PxRigidBody*)planet->Get())->getGlobalPose();
			PxTransform meteorPose = ((PxRigidBody*)satellite->Get())->getGlobalPose();

			PxReal px = planetPose.p.x;
			PxReal pz = planetPose.p.z;
			PxReal mx = meteorPose.p.x;
			PxReal mz = meteorPose.p.z;

			PxReal x = PxAbs(px) - PxAbs(mx);
			PxReal y = PxAbs(pz) - PxAbs(mz);
			PxReal z = PxSqrt((x*x) + (y*y));

			if (z < 20)
			{
				if (mx > px)
				{
					((PxRigidBody*)satellite->Get())->addForce(PxVec3(-1.0, 0.0, 0.0) * 100);
				}
				if (mx < px)
				{
					((PxRigidBody*)satellite->Get())->addForce(PxVec3(1.0, 0.0, 0.0) * 100);
				}
				if (mz < pz)
				{
					((PxRigidBody*)satellite->Get())->addForce(PxVec3(0.0, 0.0, 1.0) * 100);
				}
				if (mz > pz)
				{
					((PxRigidBody*)satellite->Get())->addForce(PxVec3(0.0, 0.0, -1.0) * 100);
				}
			}
		}

		// ==============================
		// Add Gravity to Dynamic Actors
		// ==============================
		void AddGravityDynamic(DynamSphere* planet, DynamSphere* satellite)
		{
			PxTransform planetPose = ((PxRigidBody*)planet->Get())->getGlobalPose();
			PxTransform meteorPose = ((PxRigidBody*)satellite->Get())->getGlobalPose();

			PxReal px = planetPose.p.x;
			PxReal pz = planetPose.p.z;
			PxReal mx = meteorPose.p.x;
			PxReal mz = meteorPose.p.z;

			PxReal x = PxAbs(px) - PxAbs(mx);
			PxReal y = PxAbs(pz) - PxAbs(mz);
			PxReal z = PxSqrt((x*x) + (y*y));

			if (z < 20)
			{
				if (mx > px)
				{
					((PxRigidBody*)satellite->Get())->addForce(PxVec3(-1.0, 0.0, 0.0) * 100);
				}
				if (mx < px)
				{
					((PxRigidBody*)satellite->Get())->addForce(PxVec3(1.0, 0.0, 0.0) * 100);
				}
				if (mz < pz)
				{
					((PxRigidBody*)satellite->Get())->addForce(PxVec3(0.0, 0.0, 1.0) * 100);
				}
				if (mz > pz)
				{
					((PxRigidBody*)satellite->Get())->addForce(PxVec3(0.0, 0.0, -1.0) * 100);
				}
			}
		}

		/// An example use of key release handling
		void ExampleKeyReleaseHandler()
		{
			cerr << "I am realeased!" << endl;
		}

		/// An example use of key presse handling
		void ExampleKeyPressHandler()
		{
			cerr << "I am pressed!" << endl;
		}
	};
}
