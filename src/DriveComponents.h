#ifndef SRC_DRIVECOMPONENTS_H_
#define SRC_DRIVECOMPONENTS_H_

#include "ButtonMap.h"
#include "Controller.h"
#include "Debug.h"

#include <RobotDrive.h>

#include <array>

class DriveComponent {
public:
	DriveComponent() : drive_(nullptr) {}
	DriveComponent(frc::RobotDrive * drive) : drive_(drive) {}
	virtual void drive() = 0;
	virtual ~DriveComponent() {}
protected:
	frc::RobotDrive * drive_;
};

class NullDrive : public DriveComponent {
public:
	NullDrive() {}
	void drive() {
		DebugLog::postDebugString("Attempted to drive with null component.");
	}
};

class ArcadeDrive : public DriveComponent {
public:
	ArcadeDrive(frc::RobotDrive * drive, std::array<const Controller::Axis *, 2> axes, std::array<const Controller::Button *, 4> buttons) :
		DriveComponent(drive),
		speed_(axes[0]),
		rotation_(axes[1]),
		gearDown_(buttons[0]),
		gearUp_(buttons[1]),
		rotGearDown_(buttons[2]),
		rotGearUp_(buttons[3]),
		gear_(3),
		rotGear_(3) {}
	void drive() {
		double vel = -speed_->getState();
		double rot = -rotation_->getState();

		if (gearDown_->wasPressed()) {
			if (--gear_ < minGear_) gear_ = minGear_;
		}
		else if (gearUp_->wasPressed()) {
			if (++gear_ > maxGear_) gear_ = maxGear_;
		}
		vel *= (double)(gear_) / (double)(maxGear_);
		if (vel < -1.0) vel = -1.0;
		else if (vel > 1.0) vel = 1.0;

		if (rotGearDown_->wasPressed()) {
			if (--rotGear_ < minGear_) rotGear_ = minGear_;
		}
		else if (rotGearUp_->wasPressed()) {
			if (++rotGear_ > maxGear_) rotGear_ = maxGear_;
		}
		rot *= (double)(rotGear_) / (double)(maxGear_);
		if (rot < -1.0) rot = -1.0;
		else if (rot > 1.0) rot = 1.0;

		drive_->ArcadeDrive(vel, rot);
	}
private:
	const Controller::Axis * speed_;
	const Controller::Axis * rotation_;
	const Controller::Button * gearDown_;
	const Controller::Button * gearUp_;
	const Controller::Button * rotGearDown_;
	const Controller::Button * rotGearUp_;

	char gear_;
	char rotGear_;

	static const char minGear_ = 3;
	static const char maxGear_ = 6;
};

class TankDrive : public DriveComponent {
public:
	TankDrive(frc::RobotDrive * drive, std::array<const Controller::Axis *, 2> axes, std::array<const Controller::Button *, 2> buttons) :
		DriveComponent(drive),
		lSpeed(axes[0]),
		rSpeed(axes[1]),
		gearDown(buttons[0]),
		gearUp(buttons[1]),
		gear_(3) {}
	void drive() {
		double lVel = -lSpeed->getState();
		double rVel = -rSpeed->getState();

		if (gearDown->wasPressed()) {
			if (--gear_ < minGear_) gear_ = minGear_;
		}
		else if (gearUp->wasPressed()) {
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
	const Controller::Axis * lSpeed;
	const Controller::Axis * rSpeed;
	const Controller::Button * gearDown;
	const Controller::Button * gearUp;

	char gear_;

	static const char minGear_ = 3;
	static const char maxGear_ = 6;
};

#endif /* SRC_DRIVECOMPONENTS_H_ */
