/*
 * DriveComponents.h
 *
 *  Created on: Oct 31, 2017
 *      Author: bateng
 */

#ifndef SRC_DRIVECOMPONENTS_H_
#define SRC_DRIVECOMPONENTS_H_

#include "ButtonMap.h"
#include "Controller.h"

#include "Debug.h"

#include <RobotDrive.h>

class DriveComponent {
public:
	DriveComponent(frc::RobotDrive * drive, Controller * controller) : drive_(drive), controller_(controller) {}
	virtual void drive() = 0;
	virtual ~DriveComponent() {}
protected:
	Controller * controller_;
	frc::RobotDrive * drive_;
};

class ArcadeDrive : public DriveComponent {
public:
	ArcadeDrive(frc::RobotDrive * drive, Controller * controller) : DriveComponent(drive, controller), gear_(3), rotGear_(3) {
		DebugLog::postDebugString("Arcade Drive Initialized");
	}
	void drive() {
		double vel = -controller_->getAxis(X360::Axis::LStickY).getState();
		double rot = -controller_->getAxis(X360::Axis::LStickX).getState();

		if (controller_->getButton(X360::Button::LB).wasPressed()) {
			if (--gear_ < minGear_) gear_ = minGear_;
		}
		else if (controller_->getButton(X360::Button::RB).wasPressed()) {
			if (++gear_ > maxGear_) gear_ = maxGear_;
		}
		vel *= (double)(gear_) / (double)(maxGear_);
		if (vel < -1.0) vel = -1.0;
		else if (vel > 1.0) vel = 1.0;

		if (controller_->getButton(X360::Button::L3).wasPressed()) {
			if (--rotGear_ < minGear_) rotGear_ = minGear_;
		}
		else if (controller_->getButton(X360::Button::R3).wasPressed()) {
			if (++rotGear_ > maxGear_) rotGear_ = maxGear_;
		}
		rot *= (double)(rotGear_) / (double)(maxGear_);
		if (rot < -1.0) rot = -1.0;
		else if (rot > 1.0) rot = 1.0;

		drive_->ArcadeDrive(vel, rot);
	}
private:
	static const char minGear_ = 3;
	static const char maxGear_ = 6;
	char gear_;
	char rotGear_;
};

class TankDrive : public DriveComponent {
public:
	TankDrive(frc::RobotDrive * drive, Controller * controller) : DriveComponent(drive, controller), gear_(3) {
		DebugLog::postDebugString("Tank Drive Initialized");
	}
	void drive() {
		double lVel = -controller_->getAxis(X360::Axis::LStickY).getState();
		double rVel = -controller_->getAxis(X360::Axis::RStickY).getState();

		if (controller_->getButton(X360::Button::LB).wasPressed()) {
			if (--gear_ < minGear_) gear_ = minGear_;
		}
		else if (controller_->getButton(X360::Button::RB).wasPressed()) {
			if (++gear_ > maxGear_) gear_ = maxGear_;
		}

		double multiplier = (double)(gear_) / (double)(maxGear_);

		lVel *= multiplier;
		if (lVel < -1.0) lVel = -1.0;
		else if (lVel > 1.0) lVel = 1.0;

		rVel *= multiplier;
		if (rVel < -1.0) rVel = -1.0;
		if (rVel > 1.0) rVel = 1.0;

		drive_->TankDrive(lVel, rVel);
	}
private:
	static const char minGear_ = 3;
	static const char maxGear_ = 6;
	char gear_;
};

class SplitArcadeDrive : public DriveComponent {
public:
	SplitArcadeDrive(frc::RobotDrive * drive, Controller * controller) : DriveComponent(drive, controller), gear_(3), rotGear_(3) {
		DebugLog::postDebugString("Split Arcade Drive Initialized");
	}
	void drive() {
		double vel = -controller_->getAxis(X360::Axis::LStickY).getState();
		double rot = -controller_->getAxis(X360::Axis::RStickX).getState();

		if (controller_->getButton(X360::Button::LB).wasPressed()) {
			if (--gear_ < minGear_) gear_ = minGear_;
		}
		else if (controller_->getButton(X360::Button::RB).wasPressed()) {
			if (++gear_ > maxGear_) gear_ = maxGear_;
		}
		vel *= (double)(gear_) / (double)(maxGear_);
		if (vel < -1.0) vel = -1.0;
		else if (vel > 1.0) vel = 1.0;

		if (controller_->getButton(X360::Button::L3).wasPressed()) {
			if (--rotGear_ < minGear_) rotGear_ = minGear_;
		}
		else if (controller_->getButton(X360::Button::R3).wasPressed()) {
			if (++rotGear_ > maxGear_) rotGear_ = maxGear_;
		}
		rot *= (double)(rotGear_) / (double)(maxGear_);
		if (rot < -1.0) rot = -1.0;
		else if (rot > 1.0) rot = 1.0;

		drive_->ArcadeDrive(vel, rot);
	}
private:
	static const char minGear_ = 3;
	static const char maxGear_ = 6;
	char gear_;
	char rotGear_;
};

#endif /* SRC_DRIVECOMPONENTS_H_ */
