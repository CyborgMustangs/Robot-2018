#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <Joystick.h>

#include <unordered_map>

class Controller {
public:
	class Button {
	public:
		Button() : num(-1), state(false), prevState(false), parent_(nullptr) {}
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

		bool isDown() const { return state; }
		bool wasPressed() const {
			return state && !prevState;
		}
		bool wasReleased() const {
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
		Axis() : num(-1), state(0.0), parent_(nullptr) {}
		void init(int number, Controller * parent) {
			num = number;
			state = 0.0;
			parent_ = parent;
		}
		Axis(int number, Controller * parent) : num(number), state(0.0), parent_(parent) {}
		void update() {
			state = parent_->controller_->GetRawAxis(num);
		}

		double getState() const { return state; }
	private:
		int num;
		double state;
		Controller * parent_;
	};

	Controller();
	void init(int port);
	Controller(int port);
	void update();

	const Button & getButton(int number);
	const Axis & getAxis(int number);

	~Controller();
private:
	frc::Joystick * controller_;
	std::unordered_map<int, Button> buttons_;
	std::unordered_map<int, Axis> axes_;
};

#endif /* SRC_CONTROLLER_H_ */
