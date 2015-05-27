#include "CPIConnector.h"

CPIConnector::CPIConnector(uint16_t id) : DeviceId(id){}

void CPIConnector::onMessage(mavlink_ralcp_t & function){
	switch (function.Function){
		case LIDAR_COMMAND_FUNCTIONS::LIDAR_INIT:
			messages.push(mavlink_ralcp_t{COMMAND_DESTINATION::LIDAR, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::LIDAR_INIT });
			break;

		case LIDAR_COMMAND_FUNCTIONS::LIDAR_GETDEVICE:
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::LIDAR_GETDEVICE, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::LIDAR_GETDEVICE });
			break;

		case LIDAR_COMMAND_FUNCTIONS::RECEIVELINE:
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::RECEIVELINE, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::RECEIVELINE});
			break;

		case LIDAR_COMMAND_FUNCTIONS::RECIEVERPM:
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::RECIEVERPM, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::RECIEVERPM});
			break;

		case LIDAR_COMMAND_FUNCTIONS::SENDRPM:
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::SENDRPM, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::SENDRPM });
			break;

		case LIDAR_COMMAND_FUNCTIONS::START:
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::START, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::START });
			break;

		case LIDAR_COMMAND_FUNCTIONS::STOP:
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::STOP, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::STOP });
			break;

		case LIDAR_COMMAND_FUNCTIONS::SENDROSBEEPOSITION:
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::SENDROSBEEPOSITION, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::SENDROSBEEPOSITION });
			break;

		case LIDAR_COMMAND_FUNCTIONS::SENDROSBEEFLANK:
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::SENDROSBEEFLANK, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::SENDROSBEEFLANK });
			break;

		default:
			std::cout << "initialize Lidar" << std::endl;
			messages.push(mavlink_ralcp_t{ LIDAR_COMMAND_FUNCTIONS::LIDAR_INIT, COMMAND_DESTINATION::COMMAND_DESTINATION_ENUM_END, LIDAR_COMMAND_FUNCTIONS::LIDAR_INIT });
			break;
	}

}
