#ifndef SRC_MOVEMENT_H_
#define SRC_MOVEMENT_H_

#include "DriveComponents.h"
#include "Controller.h"

#include <Talon.h>
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
	void changeDriveMode(std::string mode);

	~Movement();
private:
	Controller * controller_;

	frc::RobotDrive * drive_;

	Talon *frontLeft, *frontRight, *backLeft, *backRight;

	NullDrive * NULL_DRIVE;
	ArcadeDrive * ARCADE_DRIVE;
	SplitArcadeDrive * SPLIT_ARCADE_DRIVE;
	TankDrive * TANK_DRIVE;

	DriveComponent * mode_;
};

#endif /* SRC_MOVEMENT_H_ */
