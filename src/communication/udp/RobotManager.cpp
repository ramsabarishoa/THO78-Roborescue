#include "RobotManager.h"
RobotManager * RobotManager::instance = nullptr;

RobotManager * RobotManager::get(){
	if(instance == nullptr){
		instance = new RobotManager;
	}


	return instance;
}

Rosbee * RobotManager::createRosbee(Socket & s){
	try{
	Rosbee * rosbee = new Rosbee(s);
}catch(std::exception &ex){
	std::cout << ex.what();
}
	//robots.push_back(rosbee);
	return nullptr;

}

