#include "PhysicsManager.h"


PhysicsManager::PhysicsManager()
{
	_world = std::make_unique<b2World>(b2Vec2(0.0f, 0.0f));
}

PhysicsManager::PhysicsManager(const PhysicsManager &obj) {
	_world = std::make_unique<b2World>(b2Vec2(0.0f, 0.0f));
}

void PhysicsManager::addRigidBody(Entity* e, b2BodyType type, float size_x, float size_y) {
	// Create body def
	b2BodyDef* entityBodyDef = new b2BodyDef;
	entityBodyDef->type = type;
	entityBodyDef->position.Set(e->getPos().x / 100, e->getPos().y / 100);
	entityBodyDef->allowSleep = false;
	entityBodyDef->fixedRotation = true;
	entityBodyDef->angle = 0;

	// Add body to world
	b2Body* entityBody = _world->CreateBody(entityBodyDef);
	_rbodies.push_back({ e, entityBody });

	//Make the fixture
	b2PolygonShape entityBox;
	entityBox.SetAsBox(size_x / 100,size_y / 100);
	entityBody->CreateFixture(&entityBox, 1.0f);
	entityBody->SetUserData(e);

}

void PhysicsManager::applyForce(Entity* e, b2Vec2 force) {
	for (unsigned int i = 0; i < _rbodies.size(); i++) {
		if (_rbodies.at(i).ent_ptr == e) {
			_rbodies.at(i).body_ptr->ApplyForce(force, b2Vec2(0, 0), true);
		}
	}
}

b2Body* PhysicsManager::getRigidBodyPtr(Entity* e) {
	for (unsigned int i = 0; i < _rbodies.size(); i++) {
		if (_rbodies.at(i).ent_ptr == e) {
			return _rbodies.at(i).body_ptr;
		}
	}
	return nullptr;
}

void PhysicsManager::stepPhysics() {
	_world->Step(1.0f / 20.0f, 6, 2);
	//Update all visual entity positions
	for (unsigned int k = 0; k < _rbodies.size(); k++) {

		float x_pos = _rbodies.at(k).body_ptr->GetPosition().x * 100;
		float y_pos = _rbodies.at(k).body_ptr->GetPosition().y * 100;
		float z_pos = _rbodies.at(k).ent_ptr->getPos().z;
		Entity* cur_ent = _rbodies.at(k).ent_ptr;
		cur_ent->setPos(b2Vec3(x_pos, y_pos, z_pos));

	}
}

b2World* PhysicsManager::getWorld() {
	return _world.get();
}

PhysicsManager::~PhysicsManager()
{
}
