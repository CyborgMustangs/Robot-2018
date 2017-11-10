#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <Joystick.h>

#include <map> //unordered_map doesn't work because eclipse is broken

class Controller {
	class Button {
	public:
		Button() {}
		void init(int number, Controller * parent) {
			num = number;
			state = false;
			prevState = false;
			parent_ = parent;
		}
		Button(int number, Controller * parent) : num(number), state(false), prevState(false), parent_(parent) {}
		void update() {
			prevState = state;
			state = parent_->controller_->GetRawButton(num);
		}

		bool isDown() { return state; }
		bool wasPressed() {
			return state && !prevState;
		}
		bool wasReleased() {
			return !state && prevState;
		}

	private:
		int num;
		bool state;
		bool prevState;
		Controller * parent_;
	};

	class Axis {
	public:
		Axis() {}
		void init(int number, Controller * parent) {
			num = number;
			state = 0.0;
			parent_ = parent;
		}
		Axis(int number, Controller * parent) : num(number), state(0.0), parent_(parent) {}
		void update() {
			state = parent_->controller_->GetRawAxis(num);
		}

		double getState() { return state; }
	private:
		int num;
		double state;
		Controller * parent_;
	};

public:
	Controller();
	void init(int port);
	Controller(int port);
	void update();

	Button getButton(int number);
	Axis getAxis(int number);

	~Controller();
private:
	frc::Joystick * controller_;
	std::map<int, Button> buttons_;
	std::map<int, Axis> axes_;
};

#endif /* SRC_CONTROLLER_H_ */
