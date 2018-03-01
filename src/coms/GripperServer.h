/*
 * GripperServer.h
 *
 *  Created on: Feb 24, 2018
 *      Author: arschueler
 */

#ifndef SRC_COMS_GRIPPERSERVER_H_
#define SRC_COMS_GRIPPERSERVER_H_

#include <PacketEvent.h>
#include "Servo.h"
#include <cmath>        // std::abs

#define GRIPPPER_SERVER_ID 13

class GripperServer : public PacketEventAbstract
{
private:
// This is the gripper servo instantiation that goes into the server constructor.
Servo* myServo;
int currentPosition = 0; // Initialize to the closed position.
int wantedPosition = 0;

public:
	GripperServer (Servo* aServo) : PacketEventAbstract( GRIPPPER_SERVER_ID )
	{
		myServo = aServo;
		myServo->calibrate(0.001, 9);
	}

	  //User function to be called when a packet comes in
	  // Buffer contains data from the packet coming in at the start of the function
	  // User data is written into the buffer to send it back
	  void event(float * buffer);
};

#endif /* SRC_COMS_GRIPPERSERVER_H_ */
