TARGET = Box2DTest
OBJS = main.o Render.o Renderer.o Test.o TestEntries.o CTimer.o

PSPPATH = $(shell psp-config --psp-prefix)

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
#CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DTARGET_FLOAT32_IS_FIXED
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PSP_FW_VERSION = 401

LIBS =   -lz -lBox2d -lpspgum_vfpu -lpspgu -lm -lstdc++ -lpsprtc -lpspctrl -lpspvfpu -lpspsdk -lpsppower -lpspge
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Box2D Demo
PSP_EBOOT_ICON = icon.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

