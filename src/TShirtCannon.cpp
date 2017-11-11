#include <TShirtCannon.h>

#include <Timer.h>

void TShirtCannon::init(const Controller::Button * activation, int channel, int moduleNumber) {
	if (solenoid_ != nullptr) delete solenoid_;
	solenoid_ = new frc::Solenoid(channel, moduleNumber);
	activation_ = activation;
}

TShirtCannon::TShirtCannon(const Controller::Button * activation, int channel, int moduleNumber) : startTime_(-1) {
	solenoid_ = new frc::Solenoid(channel, moduleNumber);
	activation_ = activation;
}

void TShirtCannon::update() {
	if (startTime_ != -1) {
		if (Timer::GetFPGATimestamp() - startTime_ >= SHOOT_TIME) {
				startTime_ = -1;
				solenoid_->Set(false);
		}
	}
	if (activation_->wasPressed()) {
		startTime_ = Timer::GetFPGATimestamp();
		solenoid_->Set(true);
	}
}

TShirtCannon::~TShirtCannon() {
	if (solenoid_ != nullptr) delete solenoid_;
}
