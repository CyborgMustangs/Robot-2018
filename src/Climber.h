#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

#include "Controller.h"

#include <Talon.h>

#include <vector>

class Climber {
public:
	Climber();
	Climber(int port, Controller::Button * up, Controller::Button * down) : motor_(nullptr) { init(port, up, down); }

	void init(int port, Controller::Button * up, Controller::Button * down);

	void update();

	~Climber();
private:
	void climb_(double velocity);

	Spark * motor_;
	Controller::Button *up_, *down_;
};

#endif *//* SRC_CLIMBER_H_ */
