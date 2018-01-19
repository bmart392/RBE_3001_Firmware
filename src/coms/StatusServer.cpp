#include "StatusServer.h"

void StatusServer::event(float * packet){

 // cast packet
	uint8_t * buff =(uint8_t *) packet;

	/**
	   * The following loop reads sensor data (encoders ticks, joint velocities and
	   * force readings) and writes it in the response packet.
	   */
	  for(int i = 1; i < myPumberOfPidChannels + 1; i++)
	    {
	      float position = myPidObjects[i]->GetPIDPosition();
	      float velocity = myPidObjects[i]->getVelocity();
	      float torque   = myPidObjects[i]->loadCell->read();

	      packet[(i*3)+0] = position;
	      packet[(i*3)+1] = velocity;
	      packet[(i*3)+2] = torque;
	    }
 // set values back to Buffer
}
