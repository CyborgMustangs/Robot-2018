#ifndef SRC_TSHIRTCANNON_H_
#define SRC_TSHIRTCANNON_H_

#include "Controller.h"

#include <Solenoid.h>

class TShirtCannon {
public:
	TShirtCannon() : activation_(nullptr), solenoid_(nullptr), startTime_(-1) {}
	void init(const Controller::Button * activation, int channel, int moduleNumber = 0);

	TShirtCannon(const Controller::Button * activation, int channel, int moduleNumber = 0);

	void update();

	~TShirtCannon();
private:
	const Controller::Button * activation_;

	frc::Solenoid * solenoid_;

	double startTime_;

	static constexpr const double SHOOT_TIME = 0.75;
};

#endif /* SRC_TSHIRTCANNON_H_ */
