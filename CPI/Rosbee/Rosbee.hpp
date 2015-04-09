#include <queue>
#include "CPIBoundaryObject.hpp"
#include "RosbeeCommand.hpp"
#include "Socket.hpp"
class Rosbee : public CPIBoundaryObject
{
public:
	Rosbee(Socket s) : CPIBoundaryObject(s){}
	void sendCommand(Command cmd) override;
	void receivedCommands(Command cmd);
	void init();
	void getRequirementStatus();
	void startMission();
    void sendWaypoint();
	void getRequest();
	void stopMission();
	void abortMission();
    void sonarInterupt();
	void sendAck();
	void BatteryStatus();
    void sendInterrupt();
    void getDevice();

	~Rosbee();
	
};
