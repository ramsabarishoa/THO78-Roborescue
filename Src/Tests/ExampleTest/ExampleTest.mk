CXX 		+= 
CXXFLAGS	+= 
INCLUDES 	+= 
LDLIBS		+= 
LDFLAGS		+= 
MODULES		+= $(QUADCOPTER_MODULE) 
MODULES		+= $(MAVLINK_EXCHANGER_MODULE)
MODULES		+= $(MAVLINK_LIB)
MODULES		+= $(SERIAL_PORT_MODULE)


SRC 		+= Src/Tests/ExampleTest/Main.cpp