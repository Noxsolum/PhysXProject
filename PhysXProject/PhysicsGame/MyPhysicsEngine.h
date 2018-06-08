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
	static int LevelCount = 1;

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
						LevelCount = LevelCount + 1;
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

		//Method called when the contact by the filter shader is detected.
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
		virtual void onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) {}
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
		PxMaterial* bouncyMat;
		PxMaterial* SUPERFRICTION;
		
	
	public:
		bool triggerBool = false;
		bool Winner = false;
		MyScene() : Scene() {};

		void createLvl1();
		void createLvl2();
		void createLvl3();
		void createLvl4();
		void createLvl5();
		void createLvl6();
		void createLvl7();
		void createLvl8();
		void createLvl9();
		void createLvl10();

		void AddGravity(StaticSphere* planet, DynamSphere* satellite);
		void AddGravityDynamic(DynamSphere* planet, DynamSphere* satellite);
		void AddRepulsion(StaticSphere* planet, DynamSphere* satellite);
		void AddRepulsionDynamic(DynamSphere* planet, DynamSphere* satellite);

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
			bouncyMat = CreateMaterial(0.0f, 0.0f, 1.0f);
			SUPERFRICTION = CreateMaterial(0.0f, 0.1f, 0.0f);
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
			case 1:
				createLvl1();
				break;
			case 2:
				createLvl2();
				break;
			case 3:
				createLvl3();
				break;
			case 4:
				createLvl4();
				break;
			case 5:
				createLvl5();
				break;
			case 6:
				createLvl6();
				break;
			case 7:
				createLvl7();
				break;
			case 8:
				createLvl8();
				break;
			case 9:
				createLvl9();
				break;
			case 10:
				createLvl10();
				break;
			case 11:
				createLvl1();
				break;
			case 12:
				createLvl2();
				break;
			case 13:
				createLvl3();
				break;
			case 14:
				createLvl4();
				break;
			case 15:
				createLvl5();
				break;
			case 16:
				createLvl6();
				break;
			case 17:
				createLvl7();
				break;
			case 18:
				createLvl8();
				break;
			case 19:
				createLvl9();
				break;
			case 20:
				createLvl10();
				break;
			default:
				break;
			}
		}

		// =======================
		// Custom udpate function
		// =======================
		virtual void CustomUpdate() 
		{
			if (LevelCount < 11)
			{
				AddGravity(planet, meteor);
				AddGravity(planet2, meteor);
				AddGravityDynamic(planet3, meteor);
			}
			else if (LevelCount > 10)
			{
				AddRepulsion(planet, meteor);
				AddRepulsion(planet2, meteor);
				AddRepulsionDynamic(planet3, meteor);
			}

			if(my_callback->trigger)
			{
				triggerBool = true;
			}
		}
		// =======================
		// Custom update function
		// =======================
		//void getDistance(DynamSphere* indie, DynamSphere* meteor)
		//{
		//	PxTransform planetPose = ((PxRigidBody*)indie->Get())->getGlobalPose();
		//	PxTransform meteorPose = ((PxRigidBody*)meteor->Get())->getGlobalPose();
		//	PxReal px = planetPose.p.x;
		//	PxReal pz = planetPose.p.z;
		//	PxReal mx = meteorPose.p.x;
		//	PxReal mz = meteorPose.p.z;
		//	PxReal x = PxAbs(px) - PxAbs(mx);
		//	PxReal y = PxAbs(pz) - PxAbs(mz);
		//	PxReal z = PxSqrt((x*x) + (y*y));
		//}		
	};
}
