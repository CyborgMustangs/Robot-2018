#include "Movement.h"
#include "CubeManipulator.h"
#include "Climber.h"

#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {
		driveModeChooser.AddDefault(SPLIT_ARCADE_DRIVE, SPLIT_ARCADE_DRIVE);
		driveModeChooser.AddObject(ARCADE_DRIVE, ARCADE_DRIVE);
		driveModeChooser.AddObject(TANK_DRIVE, TANK_DRIVE);
		frc::SmartDashboard::PutData("Drive Mode", &driveModeChooser);

		modeSelected = SPLIT_ARCADE_DRIVE;

		controller_.init(0);
		driveTrain_.init(1, 2, 3, 4, DriveMode::splitArcadeDrive, &controller_);
		//manipulator_.init(0, 0, 0, &controller_);
		//climber_.init(0, &(controller_->getButton(X360::Button::Y)), &(controller_->getButton(X360::Button::B)));
	}
	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		if (modeSelected != driveModeChooser.GetSelected()) {
			modeSelected = driveModeChooser.GetSelected();

			driveTrain_.changeDriveMode(modeSelected);
		}

		controller_.update();
		driveTrain_.update();
		//manipulator_.update();
		//climber_.update();
	}

	void TestPeriodic() {
		//lw->Run();
	}

private:
	//frc::LiveWindow* lw = LiveWindow::GetInstance();

	frc::SendableChooser<std::string> driveModeChooser;
	const std::string SPLIT_ARCADE_DRIVE = "Split Arcade Drive";
	const std::string ARCADE_DRIVE = "Arcade Drive";
	const std::string TANK_DRIVE = "Tank Drive";
	std::string modeSelected;

	Controller controller_;
	Movement driveTrain_;
	//CubeManipulator manipulator_;
	//Climber climber_;
};

START_ROBOT_CLASS(Robot)
