#include "Movement.h"
#include "ButtonMap.h"
#include "Debug.h"

#include <array>

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
	frontLeft->SetInverted(true); //TODO
	if (frontRight != nullptr) delete frontRight;
	frontRight = new Talon(frontRightPort);
	frontRight->SetInverted(true);
	if (backLeft != nullptr) delete backLeft;
	backLeft = new Talon(backLeftPort);
	backLeft->SetInverted(true);
	if (backRight != nullptr) delete backRight;
	backRight = new Talon(backRightPort);
	backRight->SetInverted(true);

	if (drive_ != nullptr) delete drive_;
	drive_ = new frc::RobotDrive(frontLeft, backLeft, frontRight, backRight);

	initDriveModes();

	changeDriveMode(mode);
}

Movement::Movement(int frontLeftPort, int frontRightPort, int backLeftPort, int backRightPort, DriveMode mode, Controller * controller) :
	controller_(controller),
	ARCADE_DRIVE(nullptr),
	SPLIT_ARCADE_DRIVE(nullptr),
	TANK_DRIVE(nullptr)
{
	frontLeft = new Talon(frontLeftPort);
	frontRight = new Talon(frontRightPort);
	backLeft = new Talon(backLeftPort);
	backRight = new Talon(backRightPort);

	drive_ = new frc::RobotDrive(frontLeftPort, backLeftPort, frontRightPort, backRightPort);

	NULL_DRIVE = new NullDrive();

	initDriveModes();

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

void Movement::initDriveModes() {
	//arcade drive
	if (ARCADE_DRIVE != nullptr) delete ARCADE_DRIVE;
	std::array<const Controller::Axis *, 2> axes = {
			&controller_->getAxis(X360::Axis::LStickY),
			&controller_->getAxis(X360::Axis::LStickX) };
	std::array<const Controller::Button *, 4> buttons = {
			&controller_->getButton(X360::Button::LB),
			&controller_->getButton(X360::Button::RB),
			&controller_->getButton(X360::Button::L3),
			&controller_->getButton(X360::Button::R3) };
	ARCADE_DRIVE = new ArcadeDrive(drive_, axes, buttons);

	//split arcade drive
	if (SPLIT_ARCADE_DRIVE != nullptr) delete SPLIT_ARCADE_DRIVE;
	axes[1] = &controller_->getAxis(X360::Axis::RStickX);
	SPLIT_ARCADE_DRIVE = new ArcadeDrive(drive_, axes, buttons);

	//tank drive
	if (TANK_DRIVE != nullptr) delete TANK_DRIVE;
	axes[1] = &controller_->getAxis(X360::Axis::RStickY);
	TANK_DRIVE = new TankDrive(
			drive_,
			axes,
			{buttons[0], buttons[1]}
	);
}
