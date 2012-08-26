CXX = /home/nazgee/Workspace/angstrom/setup-scripts/build/tmp-angstrom_v2012_05-eglibc/sysroots/x86_64-linux/usr/bin/armv7a-angstrom-linux-gnueabi/arm-angstrom-linux-gnueabi-g++

MODBUS_DIR = /home/nazgee/Workspace/sources/libmodbus/output
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 \
	-I./ \
	-I$(MODBUS_DIR)/include

OBJS =		motord.o cfg/Config.o modbus/Modbus.o
LIBS = -L$(MODBUS_DIR)/lib -lmodbus

TARGET =	motord

$(TARGET):	$(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $(TARGET)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
