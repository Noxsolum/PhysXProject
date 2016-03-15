#pragma once

#include "PhysicsEngine.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	// =============
	// Plane Object
	// =============
	class Plane : public StaticActor
	{
	public:
		//A plane with default paramters: XZ plane centred at (0,0,0)
		Plane(PxVec3 normal=PxVec3(0.f, 1.f, 0.f), PxReal distance=0.f) 
			: StaticActor(PxTransformFromPlaneEquation(PxPlane(normal, distance)))
		{
			CreateShape(PxPlaneGeometry());
		}
	};

	// =====================
	// Static Sphere Object
	// =====================
	class StaticSphere : public StaticActor
	{
	public:
		//a sphere with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m
		// - denisty: 1kg/m^3
		StaticSphere(const PxTransform& pose = PxTransform(PxIdentity), PxReal radius = 1.f, PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxSphereGeometry(radius), density);
		}
	};

	// ======================
	// Dynamic Sphere Object
	// ======================
	class DynamSphere : public DynamicActor
	{
	public:
		//a sphere with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m
		// - denisty: 1kg/m^3
		DynamSphere(const PxTransform& pose=PxTransform(PxIdentity), PxReal radius=1.f, PxReal density=1.f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxSphereGeometry(radius), density);
		}
	};

	// ===================
	// Dynamic Box Object
	// ===================
	class Box : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Box(const PxTransform& pose=PxTransform(PxIdentity), PxVec3 dimensions=PxVec3(.5f,.5f,.5f), PxReal density=1.0f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	// ==================
	// Static Box Object
	// ==================
	class StaticBox : public StaticActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		StaticBox(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.0f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	// ========================
	// Static Rectangle Object
	// ========================
	class Rectangle : public StaticActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Rectangle(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(3.0f, 0.5f, 0.1f), PxReal density = 1.0f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	// ===============
	// Trigger Object
	// ===============
	class Goal
	{
		Rectangle* back, *left, *right;
	public:
		Goal(const PxVec3 pose = PxVec3(0.0f, 0.5f, 50.0f), const PxVec3& dimensionsBack = PxVec3(4.0f, 0.5f, 0.25f), const PxVec3& dimensionsSides = PxVec3(0.25, 0.5f, 2.0f))
		{
			back = new Rectangle(PxTransform(PxVec3(pose.x, pose.y, pose.z)), PxVec3(dimensionsBack), PxReal(1.0f));
			left = new Rectangle(PxTransform(PxVec3(pose.x + 4.2f, pose.y, pose.z - 1.75)), PxVec3(dimensionsSides), PxReal(1.0f));
			right = new Rectangle(PxTransform(PxVec3(pose.x - 4.2f, pose.y, pose.z - 1.75)), PxVec3(dimensionsSides), PxReal(1.0f));
		}

		void AddToScene(Scene* scene)
		{
			scene->Add(back);
			scene->Add(left);
			scene->Add(right);
		}

		void SetTrigger()
		{
			back->SetTrigger(true);
		}

		void Color(PxVec3 color)
		{
			back->Color(color);
			left->Color(color);
			right->Color(color);
		}
	};

	// ====================
	// Compound Object One
	// ====================
	class Obstacle : public StaticActor
	{
		StaticBox* topLeft, *topRight, *botLeft, *botRight;
	public:
		Obstacle(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(2.0f, 2.0f, 2.0f), PxReal density = 1.0f) : StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(pose.p.x + 7.0f, pose.p.y, pose.p.z + 7.0f)));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(pose.p.x - 7.0f, pose.p.y, pose.p.z + 7.0f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(pose.p.x + 7.0f, pose.p.y, pose.p.z - 7.0f)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(pose.p.x - 7.0f, pose.p.y, pose.p.z - 7.0f)));
		}
	};

	// ====================
	// Compound Object Two
	// ====================
	class ObstacleTwo : public StaticActor
	{
		StaticBox* topLeft, *topRight, *botLeft, *botRight;
	public:
		ObstacleTwo(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(2.0f, 2.0f, 2.0f), PxReal density = 1.0f) : StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(pose.p.x + 9.9f, pose.p.y, pose.p.z)));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(pose.p.x, pose.p.y, pose.p.z + 9.9f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(pose.p.x, pose.p.y, pose.p.z - 9.9f)));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(pose.p.x - 9.9f, pose.p.y, pose.p.z)));
		}
	};

	// ============================
	// Distance Joint with Springs
	// ============================
	class DistanceJoint : public Joint
	{
	public:
		DistanceJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = (PxJoint*)PxDistanceJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
			((PxDistanceJoint*)joint)->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED, true);
			Damping(1.0f);
			Stiffness(1.0f);
		}

		void Stiffness(PxReal value)
		{
			((PxDistanceJoint*)joint)->setStiffness(value);
		}

		PxReal Stiffness()
		{
			return ((PxDistanceJoint*)joint)->getStiffness();		
		}

		void Damping(PxReal value)
		{
			((PxDistanceJoint*)joint)->setDamping(value);
		}

		PxReal Damping()
		{
			return ((PxDistanceJoint*)joint)->getDamping();
		}
	};

	// ===============
	// Revolute Joint
	// ===============
	class RevoluteJoint : public Joint
	{
	public:
		RevoluteJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = PxRevoluteJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION,true);
		}

		void DriveVelocity(PxReal value)
		{
			//wake up the attached actors
			PxRigidDynamic *actor_0, *actor_1;
			((PxRevoluteJoint*)joint)->getActors((PxRigidActor*&)actor_0, (PxRigidActor*&)actor_1);
			if (actor_0)
			{
				if (actor_0->isSleeping())
					actor_0->wakeUp();
			}
			if (actor_1)
			{
				if (actor_1->isSleeping())
					actor_1->wakeUp();
			}
			((PxRevoluteJoint*)joint)->setDriveVelocity(value);
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		}

		PxReal DriveVelocity()
		{
			return ((PxRevoluteJoint*)joint)->getDriveVelocity();
		}

		void SetLimits(PxReal lower, PxReal upper)
		{
			((PxRevoluteJoint*)joint)->setLimit(PxJointAngularLimitPair(lower, upper));
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}
	};

	// ===========
	// My D6Joint
	// ===========
	class dSixJoint : public Joint
	{
	public:
		dSixJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = PxD6JointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
		}

		void SetMotion(PxD6Axis::Enum Axis, PxD6Motion::Enum free)
		{
			((PxD6Joint*)joint)->setMotion(Axis, free);
		}
	};
}