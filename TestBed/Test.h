/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef TEST_H
#define TEST_H

#include <box2d/Box2D.h>
#include "Renderer.h"

#define	RAND_LIMIT	32767

/// Random number in range [-1,1]
inline float32 RandomFloat()
{
	float32 r = (float32)(rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = 2.0f * r - 1.0f;
	return r;
}

/// Random floating point number in range [lo, hi]
inline float32 RandomFloat(float32 lo, float32 hi)
{
	float32 r = (float32)(rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = (hi - lo) * r + lo;
	return r;
}

class Test;
struct Settings;

typedef Test* TestCreateFcn();

struct Settings
{
	Settings() :
hz(60.0f),
velocityIterations(5),
positionIterations(5),
drawStats(0),
drawShapes(1),
drawJoints(1),
drawCoreShapes(0),
drawAABBs(0),
drawOBBs(0),
drawPairs(0),
drawContactPoints(0),
drawContactNormals(0),
drawContactForces(0),
drawFrictionForces(0),
drawCOMs(0),
enableWarmStarting(1),
enableTOI(1),
pause(0),
singleStep(0)
{}

float32 hz;
int32 velocityIterations;
int32 positionIterations;
int32 drawShapes;
int32 drawJoints;
int32 drawCoreShapes;
int32 drawAABBs;
int32 drawOBBs;
int32 drawPairs;
int32 drawContactPoints;
int32 drawContactNormals;
int32 drawContactForces;
int32 drawFrictionForces;
int32 drawCOMs;
int32 drawStats;
int32 enableWarmStarting;
int32 enableTOI;
int32 pause;
int32 singleStep;
};

struct TestEntry
{
	const char *name;
	TestCreateFcn *createFcn;
};

extern TestEntry g_testEntries[];
// This is called when a joint in the world is implicitly destroyed
// because an attached body is destroyed. This gives us a chance to
// nullify the mouse joint.
class DestructionListener : public b2DestructionListener
{
public:
	void SayGoodbye(b2Shape* shape) { B2_NOT_USED(shape); }
	void SayGoodbye(b2Joint* joint);

	Test* test;
};

class BoundaryListener : public b2BoundaryListener	
{
public:
	void Violation(b2Body* body);

	Test* test;
};

const int32 k_maxContactPoints = 2048;

class ContactListener : public b2ContactListener
{
public:
	void Add(const b2ContactPoint* point);
	void Persist(const b2ContactPoint* point);
	void Remove(const b2ContactPoint* point);

	Test* test;
};

enum ContactState
{
	e_contactAdded,
	e_contactPersisted,
	e_contactRemoved,
};

struct ContactPoint
{
	b2Shape* shape1;
	b2Shape* shape2;
	b2Vec2 normal;
	b2Vec2 position;
	b2Vec2 velocity;
	b2ContactID id;
	ContactState state;
};

class Test
{
public:

	Test();
	virtual ~Test();

	void SetTextLine(int32 line) { m_textLine = line; }
	void DrawTitle(int x, int y, const char *string);
	virtual void Step(Settings* settings);
	virtual void Keyboard(unsigned char key) { B2_NOT_USED(key); }
	void ShiftMouseDown(const b2Vec2& p);
	virtual void MouseDown(const b2Vec2& p);
	virtual void MouseUp(const b2Vec2& p);
	void MouseMove(const b2Vec2& p);
	void LaunchBomb();
	void LaunchBomb(const b2Vec2& position, const b2Vec2& velocity);

	void SpawnBomb(const b2Vec2& worldPt);
	void CompleteBombSpawn(const b2Vec2& p);


	// Let derived tests know that a joint was destroyed.
	virtual void JointDestroyed(b2Joint* joint) { B2_NOT_USED(joint); }
	virtual void BoundaryViolated(b2Body* body) { B2_NOT_USED(body); }


	friend class DestructionListener;
	friend class BoundaryListener;
	friend class ContactListener;

	b2AABB m_worldAABB;
	ContactPoint m_points[k_maxContactPoints];
	int32 m_pointCount;
	DestructionListener m_destructionListener;
	BoundaryListener m_boundaryListener;
	ContactListener m_contactListener;
	DebugDraw m_debugDraw;
	int32 m_textLine;
	b2World* m_world;
	b2Body* m_bomb;
	b2MouseJoint* m_mouseJoint;
	b2Vec2 m_bombSpawnPoint;
	bool m_bombSpawning;
	b2Vec2 m_mouseWorld;
};

#endif
