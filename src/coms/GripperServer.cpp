/*
 * GripperServer.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: arschueler
 */

#include "GripperServer.h"

void GripperServer::event(float * buffer)
{

	// we will be using the same memory area in which the incoming packet was stored,
	// however, we need to perform a type cast first (for convenience).
	uint8_t* buff = (uint8_t*) buffer;

	/*
	*	Gripper : The first element in the 15x1 array is either a 1 or a 0.
	*	If the gripper receives a 0, the gripper opens. If the gripper
	*	receives a 1, the gripper closes.
	*
	*/

	wantedPosition = buffer[0];

if (wantedPosition == 0)
	{
		for(int i=30; i<70; i++)
		{
			myServo->write(i/100.0);
			wait(0.01);
		}
		currentPosition = wantedPosition;
	}
	else // if (wantedPosition == 1)
	{
		for(int i=70; i>30; i--)
		{
			myServo->write(i/100.0);
			wait(0.01);
		}
		currentPosition = wantedPosition;
	}

	// re-initialize the packet to all zeros
	for (int i = 4; i < 64; i++)
		buff[i] = 0;

	// Send back the position
	buffer[0] = currentPosition;


}
