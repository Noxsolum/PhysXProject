#include "MyPhysicsEngine.h"

namespace PhysicsEngine
{
	void MyScene::createLvl1()
	{
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
		borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(61.0f, 1.0f, 5.0f), PxReal(5.0f));
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
	}

	void MyScene::createLvl2()
	{
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
	}

	void MyScene::createLvl3() 
	{
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
	}

	void MyScene::createLvl4()
	{
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
	}

	void MyScene::createLvl5()
	{
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
	}

	void MyScene::createLvl6()
	{
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
	}

	void MyScene::createLvl7()
	{
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
	}

	void MyScene::createLvl8()
	{
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
	}

	void MyScene::createLvl9()
	{
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
	}

	void MyScene::createLvl10()
	{
		triggerBool = false;
		if (LevelCount == 20)
		{
			Winner = true;
		}

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
	}

	void MyScene::createLvl11()
	{
		triggerBool = false;

		// =================
		// Creating Objects
		// =================
		plane = new Plane();
		newGoal = new Goal();
		meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
		planet = new StaticSphere(PxTransform(PxVec3(30.0f, 0.5f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
		planet2 = new StaticSphere(PxTransform(PxVec3(-30.0f, 0.5f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
		planet3 = new DynamSphere(PxTransform(PxVec3(-550.0f, 1.0f, -15.0f)), PxReal(2.0f), PxReal(1.0f));
		obstacle1 = new Obstacle(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		SpringRight = new SpringWalls();
		SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
		borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
		borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(61.0f, 1.0f, 5.0f), PxReal(5.0f));
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
		Add(obstacle3);
		//Add(obstacle4);			
		SpringRight->AddToScene(this);
		SpringLeft->AddToScene(this);
		Add(borderBot);
		Add(borderTop);
		Add(borderLeft);
		Add(borderRight);
	}

	void MyScene::createLvl12()
	{
		triggerBool = false;

		// =================
		// Creating Objects
		// =================
		plane = new Plane();
		newGoal = new Goal();
		meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
		planet = new StaticSphere(PxTransform(PxVec3(15.0f, 0.5f, 15.0f)), PxReal(2.0f), PxReal(1.0f));
		planet2 = new StaticSphere(PxTransform(PxVec3(-15.0f, 0.5f, -15.0f)), PxReal(2.0f), PxReal(1.0f));
		planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.0f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
		obstacle1 = new Obstacle(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		SpringRight = new SpringWalls();
		SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
		borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
		borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(61.0f, 1.0f, 5.0f), PxReal(5.0f));
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
		//planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.0f, 25.0f)));
		//planetJoint->DriveVelocity(PxReal(3.0f));
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
	}

	void MyScene::createLvl13()
	{
		triggerBool = false;

		// =================
		// Creating Objects
		// =================
		plane = new Plane();
		newGoal = new Goal();
		meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
		planet = new StaticSphere(PxTransform(PxVec3(550.0f, 0.5f, 10.0f)), PxReal(2.0f), PxReal(1.0f));
		planet2 = new StaticSphere(PxTransform(PxVec3(-550.0f, 0.5f, -10.0f)), PxReal(2.0f), PxReal(1.0f));
		planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.0f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
		obstacle1 = new Obstacle(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		SpringRight = new SpringWalls();
		SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
		borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
		borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(61.0f, 1.0f, 5.0f), PxReal(5.0f));
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
		planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.0f, 25.0f)));
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
		obstacle1->Material(bouncyMat);
		obstacle2->Material(bouncyMat);

		// =============
		// Add to Scene
		// =============
		Add(plane);
		newGoal->AddToScene(this);
		Add(meteor);
		//Add(planet);
		//Add(planet2);
		Add(planet3);
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
	}

	void MyScene::createLvl14()
	{
		triggerBool = false;

		// =================
		// Creating Objects
		// =================
		plane = new Plane();
		newGoal = new Goal();
		meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
		planet = new StaticSphere(PxTransform(PxVec3(15.0f, 0.5f, 10.0f)), PxReal(2.0f), PxReal(1.0f));
		planet2 = new StaticSphere(PxTransform(PxVec3(-15.0f, 0.5f, -10.0f)), PxReal(2.0f), PxReal(1.0f));
		planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.0f, 0.0f)), PxReal(2.0f), PxReal(1.0f));
		obstacle1 = new Obstacle(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		SpringRight = new SpringWalls();
		SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
		borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
		borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(61.0f, 1.0f, 5.0f), PxReal(5.0f));
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
		planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.0f, 19.0f)));
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
		obstacle1->Material(bouncyMat);
		obstacle2->Material(bouncyMat);

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
		Add(obstacle3);
		//Add(obstacle4);			
		SpringRight->AddToScene(this);
		SpringLeft->AddToScene(this);
		Add(borderBot);
		Add(borderTop);
		Add(borderLeft);
		Add(borderRight);
	}

	void MyScene::createLvl15()
	{
		if (LevelCount == 15)
		{
			Winner = true;
		}
		triggerBool = false;

		// =================
		// Creating Objects
		// =================
		plane = new Plane();
		newGoal = new Goal();
		meteor = new DynamSphere(PxTransform(PxVec3(0.0f, 0.5f, -50.0f)), PxReal(1.0f), PxReal(1.0f));
		planet = new StaticSphere(PxTransform(PxVec3(15.0f, 0.5f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
		planet2 = new StaticSphere(PxTransform(PxVec3(-15.0f, 0.5f, 20.0f)), PxReal(2.0f), PxReal(1.0f));
		planet3 = new DynamSphere(PxTransform(PxVec3(0.0f, 1.0f, -5.0f)), PxReal(2.0f), PxReal(1.0f));
		obstacle1 = new Obstacle(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle2 = new Obstacle(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		obstacle3 = new ObstacleTwo(PxTransform(PxVec3(0.0f, 0.5f, 0.0f)));
		obstacle4 = new ObstacleTwo(PxTransform(PxVec3(-15.0f, 0.5f, 0.0f)));
		SpringRight = new SpringWalls();
		SpringLeft = new SpringWalls(-4.0f, PxVec3(59.0f, 0.5f, 0.0f));
		borderBot = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, -59.0f)), PxVec3(59.0f, 1.0f, 5.0f), PxReal(5.0f));
		borderTop = new Rectangle(PxTransform(PxVec3(0.0f, 0.5f, 59.0f)), PxVec3(61.0f, 1.0f, 5.0f), PxReal(5.0f));
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
		planetJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 1.0f, -10.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), planet3, PxTransform(PxVec3(0.0f, 1.0f, 15.0f)));
		planetJoint->DriveVelocity(PxReal(6.0f));
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
		Add(planet3);				
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
	}

	// =============================
	// Add Gravity to Static Actors
	// =============================
	void MyScene::AddGravity(StaticSphere* planet, DynamSphere* satellite)
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
	void MyScene::AddGravityDynamic(DynamSphere* planet, DynamSphere* satellite)
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
	// Add Repulsion to Static Actors
	// ==============================
	void MyScene::AddRepulsion(StaticSphere* planet, DynamSphere* satellite)
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

		//((PxRigidBody*)satellite->Get())->addForce(PxVec3()*100);

		if (z < 20)
		{
			if (mx > px)
			{
				((PxRigidBody*)satellite->Get())->addForce(PxVec3(1.0, 0.0, 0.0) * 100);
			}
			if (mx < px)
			{
				((PxRigidBody*)satellite->Get())->addForce(PxVec3(-1.0, 0.0, 0.0) * 100);
			}
			if (mz < pz)
			{
				((PxRigidBody*)satellite->Get())->addForce(PxVec3(0.0, 0.0, -1.0) * 100);
			}
			if (mz > pz)
			{
				((PxRigidBody*)satellite->Get())->addForce(PxVec3(0.0, 0.0, 1.0) * 100);
			}
		}
	}

	// ===============================
	// Add Repulsion to Dynamic Actors
	// ===============================
	void MyScene::AddRepulsionDynamic(DynamSphere* planet, DynamSphere* satellite)
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
				((PxRigidBody*)satellite->Get())->addForce(PxVec3(1.0, 0.0, 0.0) * 100);
			}
			if (mx < px)
			{
				((PxRigidBody*)satellite->Get())->addForce(PxVec3(-1.0, 0.0, 0.0) * 100);
			}
			if (mz < pz)
			{
				((PxRigidBody*)satellite->Get())->addForce(PxVec3(0.0, 0.0, -1.0) * 100);
			}
			if (mz > pz)
			{
				((PxRigidBody*)satellite->Get())->addForce(PxVec3(0.0, 0.0, 1.0) * 100);
			}
		}
	}
}