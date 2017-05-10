#pragma once
#include "Entity.h"
#include "Box2D\Box2D.h"
#include <vector>

class PhysicsManager
{
public:
	PhysicsManager();
	PhysicsManager(const PhysicsManager &obj);
	void addRigidBody(Entity* e, b2BodyType type, float size_x, float size_y);
	void applyForce(Entity* e, b2Vec2 force);
	b2Body* getRigidBodyPtr(Entity* e);
	void stepPhysics();
	b2World* getWorld();
	~PhysicsManager();
private:
	typedef struct {Entity* ent_ptr;b2Body* body_ptr;} Ent_Body_pair;
	std::vector<Ent_Body_pair> _rbodies;
	std::unique_ptr<b2World> _world;
};

