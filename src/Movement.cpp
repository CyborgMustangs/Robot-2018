/*
 * Movement.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: bateng
 */

#include "Movement.h"
#include "Debug.h"

Movement::Movement() : mode_(nullptr), controller_(nullptr), drive_(nullptr) {}

void Movement::init(int frontLeftPort, int frontRightPort, int backLeftPort, int backRightPort, DriveMode mode, Controller * controller) {
	controller_ = controller;
	if (drive_ != nullptr) delete drive_;
	drive_ = new frc::RobotDrive(frontLeftPort, backLeftPort, frontRightPort, backRightPort);
	drive_->SetSafetyEnabled(false);
	changeDriveMode(mode);
}

Movement::Movement(int frontLeftPort, int frontRightPort, int backLeftPort, int backRightPort, DriveMode mode, Controller * controller) :
	mode_(nullptr),
	controller_(controller)
{
	drive_ = new frc::RobotDrive(frontLeftPort, backLeftPort, frontRightPort, backRightPort);
	drive_->SetSafetyEnabled(false);
	changeDriveMode(mode);
}

void Movement::update() {
	mode_->drive();
}

void Movement::changeDriveMode(DriveMode mode) { //change to string so you can directly change from chooser
	if (mode_ != nullptr) delete mode_;
	switch(mode) {
	case DriveMode::arcadeDrive:
		mode_ = new ArcadeDrive(drive_, controller_);
		break;
	case DriveMode::splitArcadeDrive:
		mode_ = new SplitArcadeDrive(drive_, controller_);
		break;
	case DriveMode::tankDrive:
		mode_ = new TankDrive(drive_, controller_);
		break;
	default:
		mode_ = nullptr;
		DebugLog::postDebugString("DriveMode has been set to an invalid value.");
		break;
	}
}
Movement::~Movement() {
	if (drive_ != nullptr) delete drive_;
}
