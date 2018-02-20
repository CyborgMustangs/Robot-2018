#ifndef CUBEMANIPULATOR_H_
#define CUBEMANIPULATOR_H_

#include "Controller.h"

#include <Talon.h>
#include <Spark.h>

#include <array>

class CubeManipulator {
public:
	CubeManipulator() {}
	CubeManipulator(int elevPort, int feedLeftPort, int feedRightPort, Controller * controller) {
		init(elevPort, feedLeftPort, feedRightPort, controller);
	}
	void init(int elevPort, int feedLeftPort, int feedRightPort, Controller * controller) {
		elevator_.init(elevPort, controller);
		feeder_.init(feedLeftPort, feedRightPort, controller);
	}

	void update() {
		feeder_.update();
		elevator_.update();
	}
private:
	class Elevator {
		public:
			Elevator();
			void init(int port, Controller * controller);
			void update();
			~Elevator();
		private:
			Spark *motor_;
			Controller * controller_;
		} elevator_;

	class Feeder {
	public:
		Feeder();
		void init(int feedLeftPort, int feedRightPort, Controller * controller);
		void update();
		~Feeder();
	private:
		Talon *left_, *right_;
		Controller * controller_;
	} feeder_;
};

#endif /* CUBEMANIPULATOR_H_ */
