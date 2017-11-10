#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

#include <SmartDashboard/SmartDashboard.h>

#include <array>

class DebugLog {
public:
	static void postDebugString(std::string debugString) {
		static unsigned int nextLine = 0;
		static std::array<std::string, 10> debugLog_;

		debugLog_[nextLine] = debugString;

		if (++nextLine >= debugLog_.size()) nextLine = 0;

		int currentLine;
		for (unsigned int i = 0; i < debugLog_.size(); i++) {
			currentLine = nextLine - 1 - i;
			if (currentLine < 0) currentLine += debugLog_.size();
			frc::SmartDashboard::PutString("Debug Line " + std::to_string(i + 1), debugLog_[currentLine]);
		}
	}
};

#endif //SRC_DEBUG_H_
