#include <Movement.h>

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
		driveMode.AddDefault(SPLIT_ARCADE_DRIVE, SPLIT_ARCADE_DRIVE);
		driveMode.AddObject(ARCADE_DRIVE, ARCADE_DRIVE);
		driveMode.AddObject(TANK_DRIVE, TANK_DRIVE);
		frc::SmartDashboard::PutData("Drive Mode", &driveMode);

		modeSelected = SPLIT_ARCADE_DRIVE;

		controller_.init(0);
		driveTrain_.init(1, 2, 3, 4, DriveMode::splitArcadeDrive, &controller_);
	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		if (modeSelected != driveMode.GetSelected()) {
			modeSelected = driveMode.GetSelected();

			if (modeSelected == SPLIT_ARCADE_DRIVE) driveTrain_.changeDriveMode(DriveMode::splitArcadeDrive);
			else if (modeSelected == ARCADE_DRIVE) driveTrain_.changeDriveMode(DriveMode::arcadeDrive);
			else driveTrain_.changeDriveMode(DriveMode::tankDrive);
		}

		controller_.update();
		driveTrain_.update();
	}

	void TestPeriodic() {
		//lw->Run();
	}

private:
	//frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> driveMode;
	const std::string SPLIT_ARCADE_DRIVE = "Split Arcade Drive";
	const std::string ARCADE_DRIVE = "Arcade Drive";
	const std::string TANK_DRIVE = "Tank Drive";
	std::string modeSelected;

	Movement driveTrain_;
	Controller controller_;
};

START_ROBOT_CLASS(Robot)
