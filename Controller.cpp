#include "Controller.h"

Controller::Controller() : controller_(nullptr) {}
void Controller::init(int port) {
	if (controller_ != nullptr) delete controller_;
	controller_ = new frc::Joystick(port);
}

Controller::Controller(int port) {
	controller_ = new frc::Joystick(port);
}

void Controller::update() {
	for (auto & it : buttons_) {
		it.second.update();
	}
	for (auto & it : axes_) {
		it.second.update();
	}
}

Controller::Button Controller::getButton(int number) {
	if (buttons_.find(number) == buttons_.end()) buttons_.emplace(std::make_pair(number, Button(number, this)));
	return buttons_[number];
}

Controller::Axis Controller::getAxis(int number) {
	if (axes_.find(number) == axes_.end()) axes_.emplace(std::make_pair(number, Axis(number, this)));
	return axes_[number];
}

Controller::~Controller() {
	if (controller_ != nullptr) delete controller_;
}
