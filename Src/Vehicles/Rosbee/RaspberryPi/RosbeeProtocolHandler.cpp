#include "RosbeeProtocolHandler.h"
#include "RosbeeClient.h"
#include "PositionController.h"
#include "RosbeeDriver.h"
#include <thread>
#include "mavlink_commands/mavlink_commands/mavlink.h"
#include <iostream>
#include "Parser.h"

RosbeeProtocolHandler::RosbeeProtocolHandler(RosbeeClient &nRosClient,
		PositionController &nPosContr,
		RosbeeDriver &nRosDriver
):
rosClient{&nRosClient},
posCont{&nPosContr},
rosDriver{&nRosDriver},
thread{&RosbeeProtocolHandler::run,this}
{
	thread.detach();
}


void RosbeeProtocolHandler::run(){
	unsigned char function;
	unsigned long long payload;
	mavlink_command_long_t packet;
	init();

	while(true){
		rosClient->waitReceiveMessage(packet);

		switch(packet.command){
		case ROSBEE_COMMAND_FUNCTIONS::SENDWAYPOINT:
			driveToWaypoint(payload);
			break;
		}
		sleep(1);
	}
}


void RosbeeProtocolHandler::init(){
	short newX = static_cast<short>(posCont->getX());
	short newY = static_cast<short>(posCont->getY());
	short newAngle = static_cast<short>(posCont->getAngle());

	long long waypoint = 0;

	waypoint |= Parser::bitCast<long long>(newX) << 48;
	waypoint |= Parser::bitCast<long long>(newY) << 32;
	waypoint |= Parser::bitCast<long long>(newAngle) << 16;

	std::cout << "Starting handshake with server... ";
	std::cout.flush();
	rosClient->sendInit(newX, newY, newAngle);

	unsigned char function;
	unsigned long long payload;
	while(true){
		rosClient->waitReceiveMessage(function,payload);
		if(function == ROSBEE_COMMAND_FUNCTIONS::ACKNOWLEDGE ){
			break;
		}
	}
	std::cout << "Done" << std::endl;

}


void RosbeeProtocolHandler::driveToWaypoint(const mavlink_command_long_t &payload){

	int x = payload.param1;
	int y = payload.param2;

	short status = 0;
	std::cout << "Payload: " << payload << std::endl;
	std::cout << "Waypoint received: " << x << ", " << y << std::endl;

	if(!rosDriver->driveToWaypoint(x,y)){
		status = 1;
	}

	short newX = static_cast<short>(posCont->getX());
	short newY = static_cast<short>(posCont->getY());
	short newAngle = static_cast<short>(posCont->getAngle());


	std::cout << "Waypoint reached: (" << newX << ", " << newY << ") " << "r = " << newAngle <<std::endl;

	long long waypoint = 0;
	rosClient->requestWaypoint(newX, newY, newAngle, status);
//	waypoint |= Parser::bitCast<long long>(newX) << 48;
//	waypoint |= Parser::bitCast<long long>(newY) << 32;
///	waypoint |= Parser::bitCast<long long>(newAngle) << 16;
//	waypoint |= Parser::bitCast<long long>(status) << 0;

//	rosClient->sendMessage(ROSBEE_COMMAND_FUNCTIONS::ACKNOWLEDGE, waypoint);
}





