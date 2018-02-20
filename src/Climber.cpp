#include <Climber.h>

Climber::Climber() : motor_(nullptr) {}

void Climber::init(int port, Controller::Button * up, Controller::Button * down) {
	if (motor_ == nullptr) motor_ = new Spark(port);
	up_ = up;
	down_ = down;
}

void Climber::update() {
	if (up_->isDown()) climb(1.0);
	else if (down_->isDown()) climb(-1.0);
	else climb(0.0);
}

Climber::~Climber() {
	if (motor_ != nullptr) delete motor_;
}

void Climber::climb_(double velocity) {
	motor_->Set(velocity);
}*/
