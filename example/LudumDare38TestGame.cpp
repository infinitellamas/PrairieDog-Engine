// LudumDare38TestGame.cpp : Defines the entry point for the console application.
//
#define DEBUGOUT

#include <thread>
#include <future>
#include <vector>
#include <iostream>
#include "Windows.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "Glyph.h"
#include "Entity.h"

Glyphset testGlyphset = { Glyph('[', b2Vec2(-1,0)),Glyph(']', b2Vec2(1,0)) }; // Create a glyphset (ie. anim frame)

Glyphset groundGS; // We will init this in the main func.

Entity testEntity = Entity(testGlyphset, b2Vec3(25, 5, 0)); // Create Entity from glyphset at some position
Entity groundEntity; // Same here, init in main func

// Common GameLoop Vars
bool running = true;

int main()
{
	for (int i = 0; i < 20; i++) {
		groundGS.push_back(Glyph('-', b2Vec2(i-10, 0))); // Make a long line for the ground
	}
	groundEntity = Entity(groundGS, b2Vec3(25, 15, 0));

	RenderManager rndrMgr;

	SoundManager sndMgr;
	sndMgr.addSound("res\\sounds\\tinkle.wav");

	InputManager inptMgr;
	inptMgr.listenForKey('w');
	inptMgr.listenForKey('a');
	inptMgr.listenForKey('s');
	inptMgr.listenForKey('d');
	inptMgr.listenForKey('q');

	PhysicsManager physMgr;
	physMgr.addRigidBody(&testEntity,b2_dynamicBody, 2.5, 0.5); 
	physMgr.getRigidBodyPtr(&testEntity)->SetFixedRotation(true);

	physMgr.addRigidBody(&groundEntity, b2_staticBody, 9.5, 0.5); 

	while (running) {
		std::this_thread::sleep_for(std::chrono::microseconds(1)); // So we dont kill something
		// Update key states for this frame.
		inptMgr.updateKeys();
		if (inptMgr.getKey('q').getKeyDown()) {
			running = false;
		}

		if (inptMgr.getKey('w').getKeyDown()) {
			physMgr.applyForce(&testEntity, b2Vec2(0, -1000));
			sndMgr.playSound("res\\sounds\\tinkle.wav");
		}
		if (inptMgr.getKey('s').getKeyHeld()) {
			testEntity.setGlyphset({ Glyph('/', {-1,0}),Glyph(' ',{ 0,0 }),Glyph('\\',{ 1,0 }) }); // Akin to crouching
		}
		else {
			testEntity.setGlyphset(testGlyphset);
		}
		if (inptMgr.getKey('a').getKeyHeld()) {
			physMgr.applyForce(&testEntity, b2Vec2(-200, 0));
		}
		if (inptMgr.getKey('d').getKeyHeld()) {
			physMgr.applyForce(&testEntity, b2Vec2(200, 0));
		}


		physMgr.stepPhysics();

		rndrMgr.RenderScene({ testEntity, groundEntity });
	}
    return 0;
}

