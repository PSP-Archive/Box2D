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

#ifndef RENDER_H
#define RENDER_H

#include <box2d/Box2D.h>

struct b2AABB;

static b2Vec2 scTable[] = {b2Vec2(1,0 ),b2Vec2(0.923f,0.382f ),b2Vec2(0.707f,0.707f),b2Vec2(0.382f,0.923f),b2Vec2(0,1 ),b2Vec2(-0.382f,0.923f ),b2Vec2(-0.707f,0.707f),b2Vec2(-0.923f,0.382f ),b2Vec2(-1,0 ),b2Vec2(-0.923f,-0.382f ),b2Vec2(-0.707f,-0.707f),b2Vec2(-0.382f,-0.923f ),b2Vec2(0,-1 ),b2Vec2(0.382f,-0.923f ),b2Vec2(0.707f,-0.707f),b2Vec2(0.923f,-0.382f )};

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class DebugDraw : public b2DebugDraw
{
public:

	typedef struct {
		unsigned int color;
		float x, y, z;
	} Vertex;

	

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	void DrawXForm(const b2XForm& xf);

	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

	void DrawString(int x, int y, const char* string, ...); 

	void DrawAABB(b2AABB* aabb, const b2Color& color);

	void DrawLine(const b2Vec2& p1,const b2Vec2& p2);
};


#endif
