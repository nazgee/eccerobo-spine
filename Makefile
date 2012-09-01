# CXX = arm-none-linux-gnueabi-gcc

CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++0x \
	-DLOGLEVEL=0 \
	-I./ \
	$(shell pkg-config --cflags libmodbus)

OBJS =	spine.o \
	cfg/Config.o \
	modbus/Modbus.o \
	misc/Logger.o \
	misc/Interruptible.o


LIBS = $(shell pkg-config --libs libmodbus) -losock-1.0

TARGET =	spine

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
