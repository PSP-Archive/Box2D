TARGET_LIB = libBox2d.a
OBJS = Collision\b2BroadPhase.o \
Collision\b2CollideCircle.o \
Collision\b2CollidePoly.o \
Collision\b2Collision.o \
Collision\b2Distance.o \
Collision\b2PairManager.o \
Collision\b2TimeOfImpact.o \
Collision\Shapes\b2CircleShape.o \
Collision\Shapes\b2EdgeShape.o \
Collision\Shapes\b2PolygonShape.o \
Collision\Shapes\b2Shape.o \
Common\b2BlockAllocator.o \
Common\b2Math.o \
Common\b2Settings.o \
Common\b2StackAllocator.o \
Common\PspMath.o \
Dynamics\b2Body.o \
Dynamics\b2ContactManager.o \
Dynamics\b2Island.o \
Dynamics\b2World.o \
Dynamics\b2WorldCallbacks.o \
Dynamics\Contacts\b2CircleContact.o \
Dynamics\Contacts\b2Contact.o \
Dynamics\Contacts\b2ContactSolver.o \
Dynamics\Contacts\b2EdgeAndCircleContact.o \
Dynamics\Contacts\b2PolyAndCircleContact.o \
Dynamics\Contacts\b2PolyAndEdgeContact.o \
Dynamics\Contacts\b2PolyContact.o \
Dynamics\Controllers\b2BuoyancyController.o \
Dynamics\Controllers\b2ConstantAccelController.o \
Dynamics\Controllers\b2ConstantForceController.o \
Dynamics\Controllers\b2Controller.o \
Dynamics\Controllers\b2GravityController.o \
Dynamics\Controllers\b2TensorDampingController.o \
Dynamics\Joints\b2DistanceJoint.o \
Dynamics\Joints\b2GearJoint.o \
Dynamics\Joints\b2Joint.o \
Dynamics\Joints\b2LineJoint.o \
Dynamics\Joints\b2MouseJoint.o \
Dynamics\Joints\b2PrismaticJoint.o \
Dynamics\Joints\b2PulleyJoint.o \
Dynamics\Joints\b2RevoluteJoint.o

PSPSDK = $(shell psp-config --pspsdk-path)
PSPPATH = $(shell psp-config --psp-prefix)

INCDIR = $(PSPPATH)/include
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
#CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DTARGET_FLOAT32_IS_FIXED
ASFLAGS = $(CFLAGS)

include $(PSPSDK)/lib/build.mak
