#include <pspgu.h>
#include <pspgum.h>
#include <pspctrl.h>
#include <stdlib.h> // needed in order to have "exit" function @@@
#include <vector>
#include <psppower.h>

#include "Render.h"
#include "Test.h"
#include <box2d/Box2D.h>

//dt
#include "CTimer.h"

#include "main.h"
PSP_MODULE_INFO("Test2", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

namespace
{
	int32 testIndex = 0;
	int32 testSelection = 0;
	int32 testCount = 0;
	TestEntry* entry;
	Test* test;
	Settings settings;
	int32 width = 640;
	int32 height = 480;
	int32 framePeriod = 16;
	int32 mainWindow;
	float settingsHz = 60.0;
	float32 viewZoom = 1.0f;
	b2Vec2 viewCenter(0.0f, -10.0f);
	int tx, ty, tw, th;
	bool rMouseDown;
	int nMouse = 0;
	b2Vec2 lastp;

	bool run = true;
	SceCtrlData oldPad;

	float accumulator = 0.0f;
	float dt = (1.0f/60.0f);
	float msec = 1.0f;

	CTimer timer;

}

void Input()
{
	SceCtrlData pad;
	sceCtrlPeekBufferPositive(&pad, 1);

	rMouseDown = false;

	if((pad.Lx-128) > 32)
	{
		viewCenter.x -= 0.3f;
		if (nMouse == 1)
		{
			test->MouseMove(b2Vec2(-viewCenter.x,-viewCenter.y));
		}
	}

	if((pad.Lx-128) < -32)
	{
		viewCenter.x +=0.3f;
		if (nMouse == 1)
		{
			test->MouseMove(b2Vec2(-viewCenter.x,-viewCenter.y));
		}
	}

	if((pad.Ly-128) > 32)
	{
		viewCenter.y  += 0.3f;
		if (nMouse == 1)
		{
			test->MouseMove(b2Vec2(-viewCenter.x,-viewCenter.y));
		}
	}

	if((pad.Ly-128) < -32)
	{
		viewCenter.y -=0.3f;
		if (nMouse == 1)
		{
			test->MouseMove(b2Vec2(-viewCenter.x,-viewCenter.y));
		}

	}

	if (pad.Buttons & PSP_CTRL_SQUARE)
	{
		if (nMouse == 0)
		{
			rMouseDown = true;
			test->MouseDown(b2Vec2(-viewCenter.x,-viewCenter.y));
			nMouse = 1;
		}
		
	}else
	{
		if (nMouse == 1)
		{
			test->MouseUp(b2Vec2(-viewCenter.x,-viewCenter.y));
			nMouse = 0;
		}
	}

	if (pad.Buttons != oldPad.Buttons)
	{
		
		if (pad.Buttons & PSP_CTRL_CIRCLE)
		{

		}
		if (pad.Buttons & PSP_CTRL_TRIANGLE)
		{
			run = false;
		}
		if (pad.Buttons & PSP_CTRL_CROSS)
		{
			test->LaunchBomb();
		}
		if (pad.Buttons & PSP_CTRL_LTRIGGER)
		{
			--testSelection;
			if (testSelection < 0)
			{
				testSelection = testCount - 1;
			}
		}
		if (pad.Buttons & PSP_CTRL_RTRIGGER)
		{
			++testSelection;
			if (testSelection == testCount)
			{
				testSelection = 0;
			}
		}

	}

	oldPad = pad;
}

void SimulationLoop()
{
	Render::Instance()->Start();
	{
		// Move

		ScePspFVector3 move = { viewCenter.x, viewCenter.y, -20.0f};
		sceGumTranslate( &move );
	}

	settings.hz = settingsHz;
	test->Step(&settings);


	test->m_world->DrawDebugData();

	//mouse
	test->m_debugDraw.DrawSolidCircle(b2Vec2(-viewCenter.x,-viewCenter.y),0.3f,b2Vec2(0,0),b2Color(0,1,0));


	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();

	Render::Instance()->End();

	if (testSelection != testIndex)
	{
		testIndex = testSelection;
		delete test;
		entry = g_testEntries + testIndex;
		test = entry->createFcn();
		viewZoom = 1.0f;
		viewCenter.Set(0.0f, -10.0f);
		//Resize(width, height);
	}
}



int main(int argc, char **argv)
{
	SetupCallbacks();

	scePowerSetClockFrequency(333, 333, 166);
	//CGameEngine game;

	//init render engine
	Render::Instance()->Init();
	Render::Instance()->SetPerspective();

	testCount = 0;
	while (g_testEntries[testCount].createFcn != NULL)
	{
		++testCount;
	}

	testIndex = b2Clamp(testIndex, 0, testCount-1);
	testSelection = testIndex;

	entry = g_testEntries + testIndex;
	test = entry->createFcn();

	//count
	testCount = 0;
	TestEntry* e = g_testEntries;
	while (e->createFcn)
	{
		++testCount;
		++e;
	}

	//msec = (float)timer.GetDeltaTime( );

	// main loop
	while ( run )
	{
		Input();
		SimulationLoop();
		//msec = (float)timer.GetDeltaTime( );
	}


	sceGuTerm();			// Terminating the Graphics System
	sceKernelExitGame();	// Quits Application
	return 0;
}
