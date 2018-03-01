#ifndef TorqueServer_H
#define TorqueServer_H
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>        // std::abs

#define TORQUE_SERVER_ID 25

class TorqueServer: public PacketEventAbstract{

private:

  PIDimp ** myPidObjects;    // array of PidServers - one for each joint
  int myPumberOfPidChannels;
  float num_samples = 200;
  float offsetTorques[3] = { 0.44629, 0.51972, 0.48689 }; // in Newtons
  float scaleTorque[3] = {178.5,-178.5,178.5};

public:
  // Packet ID needs to be set
   TorqueServer (PIDimp ** pidObjects, int numberOfPidChannels)
   : PacketEventAbstract( TORQUE_SERVER_ID)
	 {
	   myPidObjects = pidObjects;
	   myPumberOfPidChannels = numberOfPidChannels;
	 }

  //User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float * buffer);


};


#endif /* end of include guard: Pid_server */
