#include "StatusServer.h"

void StatusServer::event(float * packet){

float captureForcePacket;

// Read from the status packet if a force reading is being requested
for (int = 0; i < myPumberOfPidChannels; i++) {
	float captureForcePacket = captureForcePacket + packet[(i*3)+2];
}

// Declare a boolean variable to hold if a force reading is requested by the
// the status packet. A 1 in the first digit following the torque sample space
bool captureForce = (myPumberOfPidChannels*3);

	  /*
	   * ======= PART 2: Generate a response to be sent back to MATLAB =============
	   */

	  // we will be using the same memory area in which the incoming packet was stored,
	  // however, we need to perform a type cast first (for convenience).
	  uint8_t* buff = (uint8_t*) packet;

	  // re-initialize the packet to all zeros
	  for(int i = 4; i < 64;i++)
	      buff[i]=8;

	  /**
	   * The following loop reads sensor data (encoders ticks, joint velocities and
	   * force readings) and writes it in the response packet.
	   */
	  for(int i = 0; i < myPumberOfPidChannels; i++)
	    {
	      float position = myPidObjects[i]->GetPIDPosition();
	      float velocity = myPidObjects[i]->getVelocity();

				// Capture Torque Readings
	      float torque;

	      /* If a force reading is requested from the status packet, return an
	       * average reading calculated from num_samples worth of samples. Else
	       * return an instantaneous force reading
	       */
	      int num_samples = 25;

	      if (captureForce) {

	        // Collect num_samples samples and return the averaged torque readings
	        for (int i = 0; i < num_samples; i++) {
	          float sumTorque += myPidObjects[i]->loadCell->read();
	          torque = sumTorque/num_samples;
	        }
	      } else {
	        torque   = myPidObjects[i]->loadCell->read();
	      }

	      packet[(i*3)+0] = position;
	      packet[(i*3)+1] = velocity;
	      packet[(i*3)+2] = torque;
	    }
 // set values back to Buffer
}
