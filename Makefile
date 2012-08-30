# CXX = arm-none-linux-gnueabi-gcc

CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++0x \
	-DLOGLEVEL=0 \
	-I./ \
	$(shell pkg-config --cflags libmodbus)

OBJS =		motord.o cfg/Config.o modbus/Modbus.o \
	misc/Logger.o \
	misc/Interruptible.o \
	sockets/Handler.o \
	sockets/Socket.o \
	sockets/Server.o \
	EchoHandler.o

LIBS = $(shell pkg-config --libs libmodbus)

TARGET =	motord

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
