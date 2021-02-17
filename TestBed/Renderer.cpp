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

#include <pspgu.h>
#include <pspgum.h>
#include <pspctrl.h>
#include <stdlib.h> // needed in order to have "exit" function @@@
#include <vector>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>

#include "Renderer.h"


void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Vertex *points;
	points = (Vertex*)sceGuGetMemory((vertexCount+1) * sizeof(Vertex));

	for (int32 i = 0; i < vertexCount; ++i)
	{
		points[i].color =  GU_COLOR( color.r, color.g, color.b, 0.0f );
		points[i].x = vertices[i].x;
		points[i].y = vertices[i].y;
		points[i].z = 0.0f;
	}

	//again first object
	points[vertexCount].color =  GU_COLOR( color.r, color.g, color.b, 0.0f );
	points[vertexCount].x = vertices[0].x;
	points[vertexCount].y = vertices[0].y;
	points[vertexCount].z = 0.0f;

	sceGumDrawArray( GU_LINE_STRIP, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, (vertexCount+1), 0, points );
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Vertex *points1;
	points1 = (Vertex*)sceGuGetMemory(vertexCount * sizeof(Vertex));

	for (int32 i = 0; i < vertexCount; ++i)
	{
		points1[i].color =  GU_COLOR( 0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
		points1[i].x = vertices[i].x;
		points1[i].y = vertices[i].y;
		points1[i].z = 0.0f;
	}

	sceGumDrawArray( GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, vertexCount, 0, points1 );

	//outlines
	Vertex *points;
	points = (Vertex*)sceGuGetMemory((vertexCount+1) * sizeof(Vertex));

	for (int32 i = 0; i < vertexCount; ++i)
	{
		points[i].color =  GU_COLOR( color.r, color.g, color.b, 1.0f );
		points[i].x = vertices[i].x;
		points[i].y = vertices[i].y;
		points[i].z = 0.0f;
	}

	//again first object
	points[vertexCount].color =  GU_COLOR( color.r, color.g, color.b, 0.0f );
	points[vertexCount].x = vertices[0].x;
	points[vertexCount].y = vertices[0].y;
	points[vertexCount].z = 0.0f;

	sceGumDrawArray( GU_LINE_STRIP, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, (vertexCount+1), 0, points );
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;

	Vertex *points;
	points = (Vertex*)sceGuGetMemory((k_segments+1) * sizeof(Vertex));

	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * scTable[i];

		points[i].color =  GU_COLOR( color.r, color.g, color.b, 1.0f );
		points[i].x = v.x;
		points[i].y = v.y;
		points[i].z = 0.0f;
	}

	//again first object
	b2Vec2 v = center + radius * scTable[0];
	points[16].color =  GU_COLOR( color.r, color.g, color.b, 1.0f );
	points[16].x = v.x;
	points[16].y = v.y;
	points[16].z = 0.0f;

	sceGumDrawArray( GU_LINE_STRIP, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, (k_segments+1), 0, points );
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	const float32 k_segments = 16.0f;

	Vertex *points1;
	points1 = (Vertex*)sceGuGetMemory((k_segments) * sizeof(Vertex));

	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * scTable[i];

		points1[i].color =  GU_COLOR( color.r, color.g, color.b, 1.0f);
		points1[i].x = v.x;
		points1[i].y = v.y;
		points1[i].z = 0.0f;
	}
	sceGumDrawArray( GU_LINE_STRIP, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, k_segments, 0, points1 );

	//outlines
	Vertex *points;
	points = (Vertex*)sceGuGetMemory((k_segments+1) * sizeof(Vertex));

	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * scTable[i];

		points[i].color =  GU_COLOR( 0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
		points[i].x = v.x;
		points[i].y = v.y;
		points[i].z = 0.0f;
	}

	//again first object
	b2Vec2 v = center + radius * scTable[0];
	points[16].color =  GU_COLOR( color.r, color.g, color.b, 1.0f );
	points[16].x = v.x;
	points[16].y = v.y;
	points[16].z = 0.0f;

	sceGumDrawArray( GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, (k_segments+1), 0, points );

	//last line
	Vertex *points2;
	points2 = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));

	points2[0].color =  GU_COLOR( color.r, color.g, color.b, 1.0f );
	points2[0].x = v.x;
	points2[0].y = v.y;
	points2[0].z = 0.0f;

	points2[1].color =  GU_COLOR( color.r, color.g, color.b, 1.0f );
	points2[1].x = v.x;
	points2[1].y = v.y;
	points2[1].z = 0.0f;

	sceGumDrawArray( GU_LINES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 2, 0, points2 );
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	Vertex *points;
	points = (Vertex*)sceGuGetMemory(2 * sizeof(Vertex));

	points[0].color =  GU_COLOR( color.r, color.g, color.b, 0.0f );
	points[0].x = p1.x;
	points[0].y = p1.y;
	points[0].z = 0.0f;

	points[1].color =  GU_COLOR( color.r, color.g, color.b, 0.0f );
	points[1].x = p2.x;
	points[1].y = p2.y;
	points[1].z = 0.0f;

	sceGumDrawArray( GU_LINES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 2, 0, points );
}

void DebugDraw::DrawXForm(const b2XForm& xf)
{
	/*b2Vec2 p1 = xf.position, p2;
	const float32 k_axisScale = 0.4f;
	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(p1.x, p1.y);
	p2 = p1 + k_axisScale * xf.R.col1;
	glVertex2f(p2.x, p2.y);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(p1.x, p1.y);
	p2 = p1 + k_axisScale * xf.R.col2;
	glVertex2f(p2.x, p2.y);

	glEnd();*/
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{

	DrawSolidCircle(p, size, b2Vec2(0,0),color);
}

void DebugDraw::DrawString(int x, int y, const char *string, ...)
{
	/*char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.9f, 0.6f, 0.6f);
	glRasterPos2i(x, y);
	int32 length = (int32)strlen(buffer);
	for (int32 i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);*/
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	/*glColor3f(c.r, c.g, c.b);
	glBegin(GL_LINE_LOOP);
	glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
	glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
	glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
	glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
	glEnd();*/
}
