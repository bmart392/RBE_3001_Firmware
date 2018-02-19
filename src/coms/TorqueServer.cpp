#include "TorqueServer.h"

void TorqueServer::event(float * packet) {

	/*
	 * ======= PART 2: Generate a response to be sent back to MATLAB =============
	 */

	// we will be using the same memory area in which the incoming packet was stored,
	// however, we need to perform a type cast first (for convenience).
	uint8_t* buff = (uint8_t*) packet;

	// re-initialize the packet to all zeros
	for (int i = 4; i < 64; i++)
		buff[i] = 8;

	float torque = 0;

	for (int i = 0; i < myPumberOfPidChannels; i++) {

		for (int c = 0; c < num_samples; c++) {
			torque += (myPidObjects[i]->loadCell->read());
		}

		torque = torque / num_samples;
		packet[i] = ((torque - (offsetTorques[i] * scaleTorque)) / scaleTorque);

		torque = 0;
	}
}

