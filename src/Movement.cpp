#include "Movement.h"
#include "Debug.h"

Movement::Movement() :
	controller_(nullptr),
	drive_(nullptr),
	frontLeft(nullptr),
	frontRight(nullptr),
	backLeft(nullptr),
	backRight(nullptr),
	ARCADE_DRIVE(nullptr),
	SPLIT_ARCADE_DRIVE(nullptr),
TANK_DRIVE(nullptr)
{
	NULL_DRIVE = new NullDrive();
	mode_ = NULL_DRIVE;
}

void Movement::init(int frontLeftPort, int frontRightPort, int backLeftPort, int backRightPort, DriveMode mode, Controller * controller) {
	controller_ = controller;

	if (frontLeft != nullptr) delete frontLeft;
	frontLeft = new Talon(frontLeftPort);
	if (frontRight != nullptr) delete frontRight;
	frontRight = new Talon(frontRightPort);
	if (backLeft != nullptr) delete backLeft;
	backLeft = new Talon(backLeftPort);
	if (backRight != nullptr) delete backRight;
	backRight = new Talon(backRightPort);

	if (drive_ != nullptr) delete drive_;
	drive_ = new frc::RobotDrive(frontLeft, backLeft, frontRight, backRight);

	if (ARCADE_DRIVE != nullptr) delete ARCADE_DRIVE;
	ARCADE_DRIVE = new ArcadeDrive(drive_, controller_);

	if (SPLIT_ARCADE_DRIVE != nullptr) delete SPLIT_ARCADE_DRIVE;
	SPLIT_ARCADE_DRIVE = new SplitArcadeDrive(drive_, controller_);

	if (TANK_DRIVE != nullptr) delete TANK_DRIVE;
	TANK_DRIVE = new TankDrive(drive_, controller_);

	changeDriveMode(mode);
}

Movement::Movement(int frontLeftPort, int frontRightPort, int backLeftPort, int backRightPort, DriveMode mode, Controller * controller) :
	controller_(controller)
{
	frontLeft = new Talon(frontLeftPort);
	frontRight = new Talon(frontRightPort);
	backLeft = new Talon(backLeftPort);
	backRight = new Talon(backRightPort);

	drive_ = new frc::RobotDrive(frontLeftPort, backLeftPort, frontRightPort, backRightPort);

	NULL_DRIVE = new NullDrive();
	ARCADE_DRIVE = new ArcadeDrive(drive_, controller_);
	SPLIT_ARCADE_DRIVE = new SplitArcadeDrive(drive_, controller_);
	TANK_DRIVE = new TankDrive(drive_, controller_);

	changeDriveMode(mode);
}

void Movement::update() {
	mode_->drive();
}

void Movement::changeDriveMode(DriveMode mode) {
	switch(mode) {
	case DriveMode::arcadeDrive:
		mode_ = ARCADE_DRIVE;
		break;
	case DriveMode::splitArcadeDrive:
		mode_ = SPLIT_ARCADE_DRIVE;
		break;
	case DriveMode::tankDrive:
		mode_ = TANK_DRIVE;
		break;
	default:
		mode_ = NULL_DRIVE;
		DebugLog::postDebugString("DriveMode has been set to an invalid value.");
		break;
	}
}

void Movement::changeDriveMode(std::string mode) {
	if (mode == "Arcade Drive") mode_ = ARCADE_DRIVE;
	if (mode == "Split Arcade Drive") mode_ = SPLIT_ARCADE_DRIVE;
	if (mode == "Tank Drive") mode_ = TANK_DRIVE;
	else {
		mode_ = NULL_DRIVE;
		DebugLog::postDebugString("DriveMode has been set to an invalid string.");
	}
}

Movement::~Movement() {
	delete NULL_DRIVE;
	if (ARCADE_DRIVE != nullptr) delete ARCADE_DRIVE;
	if (SPLIT_ARCADE_DRIVE != nullptr) delete SPLIT_ARCADE_DRIVE;
	if (TANK_DRIVE != nullptr) delete TANK_DRIVE;
	if (drive_ != nullptr) delete drive_;
	if (frontLeft != nullptr) delete frontLeft;
	if (frontRight != nullptr) delete frontRight;
	if (backLeft != nullptr) delete backLeft;
	if (backRight != nullptr) delete backRight;
}
