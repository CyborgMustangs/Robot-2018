/*
 * ButtonMap.h
 *
 *  Created on: Nov 1, 2017
 *      Author: bateng
 */

#ifndef SRC_BUTTONMAP_H_
#define SRC_BUTTONMAP_H_

namespace X360 {
	namespace Button {
		enum Button {
				A = 1, B = 2, X = 3, Y = 4,
				LB = 5, RB = 6, L3 = 9, R3 = 10,
				Select = 7, Start = 8
			};
	}
	namespace Axis {
		enum Axis {
				LStickX = 0, LStickY = 1,
				RStickX = 4, RStickY = 5,
				LT = 2, RT = 3
			};
	}
};

#endif /* SRC_BUTTONMAP_H_ */
