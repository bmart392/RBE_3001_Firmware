#include "StatusServer.h"

void StatusServer::event(float * packet){

	/*
	 * ======= PART 2: Generate a response to be sent back to MATLAB =============
	 */

	// we will be using the same memory area in which the incoming packet was stored,
	// however, we need to perform a type cast first (for convenience).
	uint8_t* buff = (uint8_t*) packet;

	// re-initialize the packet to all zeros
	for(int i = 4; i < 64;i++)
		buff[i]=8;

	// This stores all the summed torques
	float sumTorq = 0;
	// This stores the final torque.
	float actualtorque;

	float position = 0;
	float velocity = 0;
	float torque = 0;

	int c = 0;

	for(int i = 0; i < myPumberOfPidChannels; i++)
	{
		position = myPidObjects[i]->GetPIDPosition();
		velocity = myPidObjects[i]->getVelocity();

		for(c = 0; c < num_samples; c++)
		{
			torque += (myPidObjects[i]->loadCell->read());
		}

		packet[(i*3)+0] = position;
		packet[(i*3)+1] = velocity;
		torque = torque/num_samples;
		packet[(i*3)+2] = ((torque-offsetTorques[i])); ///scaleTorques[i]);

		torque = 0;
	}
}
