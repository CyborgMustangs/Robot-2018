#include "CubeManipulator.h"
#include "ButtonMap.h"

CubeManipulator::Elevator::Elevator() : motor_(nullptr), controller_(nullptr) {}
void CubeManipulator::Elevator::init(int feedLeftPort, int feedRightPort, Controller * controller) {
	if (motor_ == nullptr) motor_ = new Spark(feedRightPort);
	controller_ = controller;
}
void CubeManipulator::Elevator::update() {
	double z = controller_->getAxis(X360::Axis::RT).getState() - controller_->getAxis(X360::Axis::LT).getState();
	motor_.Set(z);
}
CubeManipulator::Elevator::~Elevator() {
	if (motor_ != nullptr) delete motor_;
}


CubeManipulator::Feeder::Feeder() : left_(nullptr), right_(nullptr), controller_(nullptr) {}
void CubeManipulator::Feeder::init(int feedLeftPort, int feedRightPort, Controller * controller) {
	if (left_ == nullptr) left_ = new Talon(feedLeftPort);
	if (right_ == nullptr) right_ = new Talon(feedRightPort);
	controller_ = controller;
}
void CubeManipulator::Feeder::update() {
	if(controller_->getButton(X360::Button::A).isDown()) {
		left_->Set(1.0);
		right_->Set(1.0);
	}
	else if (controller_->getButton(X360::Button::X).isDown()) {
		left_->Set(-1.0);
		right_->Set(-1.0);
	}
	else {
		left_->Set(0.0);
		right_->Set(0.0);
	}
}
CubeManipulator::Feeder::~Feeder() {
	if (left_ != nullptr) delete left_;
	if (right_ != nullptr) delete right_;
}
