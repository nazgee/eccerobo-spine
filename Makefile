# CXX = arm-none-linux-gnueabi-gcc

TARGET = spine

CXXFLAGS = -O2 -g -Wall -fmessage-length=0 -std=c++0x \
	-DLOGLEVEL=0 \
	-I.

OBJS =	spine.o \
	cfg/Config.o \
	modbus/Modbus.o \
	misc/Logger.o \
	server/SpineServer.o \
	server/Handler.o \
	server/Wheels.o \
	server/HandlerWheels.o \
	server/HandlerModbus.o \
	server/HandlerFile.o

ifeq ($(ARCH),arm)
LIBS = -L/home/nazgee/Workspace/eclipse/libosock-dev/output-arm/lib
LIBS+= -L/home/nazgee/Workspace/sources/libmodbus/output/lib/
CXX = /home/nazgee/Workspace/angstrom/setup-scripts/build/tmp-angstrom_v2012_05-eglibc/sysroots/x86_64-linux/usr/bin/armv7a-angstrom-linux-gnueabi/arm-angstrom-linux-gnueabi-g++
CXXFLAGS += -I/home/nazgee/Workspace/sources/libmodbus/output/include/
CXXFLAGS += -I/home/nazgee/Workspace/eclipse/libosock-dev/output-arm/include/
else
CXXFLAGS += $(shell pkg-config --cflags libmodbus)
endif

LIBS += -lmodbus -losock-1.0


$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
