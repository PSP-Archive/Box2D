#ifndef Render_H
#define Render_H

#include <pspgu.h>
#include <pspgum.h>
#include <pspctrl.h>
#include <stdlib.h> // needed in order to have "exit" function @@@
#include <vector>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

class Render
{
public:

	void *dList;		// display List, used by sceGUStart
	void *fbp0;

	

	static Render* Instance() {
		return &m_Render;
	}

	static Render m_Render;

	void Init()
	{
		dList = malloc( 262144 ); 
		fbp0  = 0;

		// Init GU
		sceGuInit();
		sceGuStart( GU_DIRECT, dList );
		// Set Buffers
		sceGuDrawBuffer( GU_PSM_8888, fbp0, BUF_WIDTH );
		sceGuDispBuffer( SCR_WIDTH, SCR_HEIGHT, (void*)0x88000, BUF_WIDTH);
		sceGuDepthBuffer( (void*)0x110000, BUF_WIDTH);

		sceGuOffset( 2048 - (SCR_WIDTH/2), 2048 - (SCR_HEIGHT/2));
		sceGuViewport( 2048, 2048, SCR_WIDTH, SCR_HEIGHT);
		sceGuDepthRange( 65535, 0);

		// Set Render States
		sceGuScissor( 0, 0, SCR_WIDTH, SCR_HEIGHT);
		sceGuEnable( GU_SCISSOR_TEST );
		sceGuDepthFunc( GU_GEQUAL );
		sceGuEnable( GU_DEPTH_TEST );
		sceGuFrontFace( GU_CW );
		sceGuShadeModel( GU_SMOOTH );
		sceGuAlphaFunc(GU_GREATER,0,0xff);
		sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);

		sceGuTexMode(GU_PSM_8888,0,0,0);
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
		sceGuTexFilter(GU_NEAREST,GU_NEAREST);
		sceGuTexWrap(GU_CLAMP,GU_CLAMP);
		sceGuTexScale(1,1);
		sceGuTexOffset(0,0);

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuDisplay(GU_TRUE);

		//for analog pad
		sceCtrlSetSamplingCycle(0);
		sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
		// finish

		pspDebugScreenInit();

		
	}

	void SetOrtho()
	{
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();

		sceGumOrtho(0,480,272,0, -250, 250); 

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		sceGuClearColor( GU_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) ); 
		sceGuClearDepth(0);	

		sceGumMatrixMode(GU_MODEL);
	}

	void SetPerspective()
	{
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();

		sceGumPerspective( 75.0f, 16.0f/9.0f, 0.5f, 1000.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		sceGuClearColor( GU_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) ); 
		sceGuClearDepth(0);	

		sceGumMatrixMode(GU_MODEL);
	}

	void Start()
	{
		sceGuStart( GU_DIRECT, dList );
		sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
		sceGumLoadIdentity();
	}

	void ShowFPS(char fpsDisplay[100])
	{
		pspDebugScreenSetOffset( (int)fbp0 );
		pspDebugScreenSetXY( 0, 0 );
		pspDebugScreenPrintf( fpsDisplay );

	}

	void End()
	{
		fbp0 = sceGuSwapBuffers();
	}

};


#endif

