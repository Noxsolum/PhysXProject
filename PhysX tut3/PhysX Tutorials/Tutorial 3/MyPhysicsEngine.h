#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>
#include <math.h>

namespace PhysicsEngine
{
	using namespace std;
	//public bool triggerBool = false;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};

	//pyramid vertices
	static PxVec3 pyramid_verts[] = {PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose=PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs),end(pyramid_trigs)), pose)
		{
		}
	};

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

	///An example class showing the use of springs (distance joints).
	class Trampoline
	{
		vector<DistanceJoint*> springs;
		StaticBox* bottom;
		Box* top;

	public:
		Trampoline(PxReal x, PxReal z, const PxVec3& dimensions = PxVec3(5.f,5.f,5.f), PxReal stiffness = 100.0f, PxReal damping = 100.0f)
		{
			PxReal thickness = .1f;
			bottom = new StaticBox(PxTransform(PxVec3(x, thickness, z)),PxVec3(dimensions.x, thickness, dimensions.z));
			top = new Box(PxTransform(PxVec3(x, dimensions.y+thickness, z)),PxVec3(dimensions.x, thickness, dimensions.z));
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,-dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,-dimensions.z)));
			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
				springs[i]->Get()->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
			}
		}

		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		~Trampoline()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
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
						cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						
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

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
//		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
//			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box, * box2;
		MySimulationEventCallback* my_callback;
		Trampoline* tramp;
		Rectangle* rectangle;
		StaticSphere* planet;
		DynamSphere* meteor;
		DynamSphere* Indicator;
		RevoluteJoint* joint;
		int Level = 0;

		
	public:
		bool triggerBool = false;
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene() {};

		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();
			switch (Level)
			{
			case 0:
				// ==========
				// Materials
				// ==========
				//PxMaterial* newMat = CreateMaterial(0.0f, 0.5f, 0.0f);
				GetMaterial()->setDynamicFriction(0.0f);

				///Initialise and set the customised event callback
				my_callback = new MySimulationEventCallback();
				px_scene->setSimulationEventCallback(my_callback);

				plane = new Plane();
				rectangle = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				planet = new StaticSphere(PxTransform(PxVec3(0.0f, 1.0f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)));
				tramp = new Trampoline(50.0f, 50.0f);
				//Indicator = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -40.0f)));

				//rectangle->Material(newMat);

				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				rectangle->Color(color_palette[2]);
				planet->Color(color_palette[3]);
				meteor->Color(color_palette[4]);
				//Indicator->Color(color_palette[5]);

				//joint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 0.5f, -50.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), Indicator, PxTransform(PxVec3(0.0f, 0.5f, -10.0f)));
				//joint->SetLimits(PxReal(PxPi/2), PxReal(-PxPi/2));

				rectangle->SetTrigger(true);

				Add(plane);
				Add(rectangle);
				Add(planet);
				Add(meteor);
				tramp->AddToScene(this);
				//Add(Indicator);
				break;
			case 1:
				// ==========
				// Materials
				// ==========
				//PxMaterial* newMat = CreateMaterial(0.0f, 0.5f, 0.0f);
				GetMaterial()->setDynamicFriction(0.0f);

				///Initialise and set the customised event callback
				my_callback = new MySimulationEventCallback();
				px_scene->setSimulationEventCallback(my_callback);

				plane = new Plane();
				rectangle = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
				planet = new StaticSphere(PxTransform(PxVec3(0.0f, 1.0f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
				meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)));
				tramp = new Trampoline(50.0f, 50.0f);
				//Indicator = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -40.0f)));

				//rectangle->Material(newMat);

				plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
				rectangle->Color(color_palette[2]);
				planet->Color(color_palette[3]);
				meteor->Color(color_palette[4]);
				//Indicator->Color(color_palette[5]);

				//joint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 0.5f, -50.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), Indicator, PxTransform(PxVec3(0.0f, 0.5f, -10.0f)));
				//joint->SetLimits(PxReal(PxPi/2), PxReal(-PxPi/2));

				rectangle->SetTrigger(true);

				Add(plane);
				Add(rectangle);
				Add(planet);
				Add(meteor);
				tramp->AddToScene(this);
				//Add(Indicator);
				break;
			default:
				break;
			}
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
			//rectangle = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 50.0f)));
			//planet = new StaticSphere(PxTransform(PxVec3(0.0f, 1.0f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
			//meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)));
			//tramp = new Trampoline(50.0f, 50.0f);
			////Indicator = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -40.0f)));

			////rectangle->Material(newMat);

			//plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));
			//rectangle->Color(color_palette[2]);
			//planet->Color(color_palette[3]);
			//meteor->Color(color_palette[4]);
			////Indicator->Color(color_palette[5]);

			////joint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 0.5f, -50.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), Indicator, PxTransform(PxVec3(0.0f, 0.5f, -10.0f)));
			////joint->SetLimits(PxReal(PxPi/2), PxReal(-PxPi/2));

			//rectangle->SetTrigger(true);

			//Add(plane);
			//Add(rectangle);
			//Add(planet);
			//Add(meteor);
			//tramp->AddToScene(this);
			////Add(Indicator);

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
			
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
			AddGravity(planet, meteor);
			if (my_callback->trigger)
			{
				triggerBool = true;
				Level++;
			}
		}

		///Gravity for an object
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
					((PxRigidBody*)meteor->Get())->addForce(PxVec3(-1.0, 0.0, 0.0) * 100);
				}
				if (mx < px)
				{
					((PxRigidBody*)meteor->Get())->addForce(PxVec3(1.0, 0.0, 0.0) * 100);
				}
				if (mz < pz)
				{
					((PxRigidBody*)meteor->Get())->addForce(PxVec3(0.0, 0.0, 1.0) * 100);
				}
				if (mz > pz)
				{
					((PxRigidBody*)meteor->Get())->addForce(PxVec3(0.0, 0.0, -1.0) * 100);
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
