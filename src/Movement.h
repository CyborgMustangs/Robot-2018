/*
 * Movement.h
 *
 *  Created on: Oct 31, 2017
 *      Author: bateng
 */

#ifndef SRC_MOVEMENT_H_
#define SRC_MOVEMENT_H_

#include "DriveComponents.h"
#include "Controller.h"

#include <RobotDrive.h>

enum class DriveMode {
	tankDrive,
	arcadeDrive,
	splitArcadeDrive,
};

class Movement {
public:
	Movement();
	void init(int frontLeftPort, int frontRightPort, int backLeftPort, int backRightPort, DriveMode mode, Controller * controller);
	Movement(int frontLeftPort, int frontRightPort, int backLeftPort, int backRightPort, DriveMode mode, Controller * controller);
	void update();

	void changeDriveMode(DriveMode mode);

	~Movement();
private:
	frc::RobotDrive * drive_;
	DriveComponent * mode_;
	Controller * controller_;
};

#endif /* SRC_MOVEMENT_H_ */
