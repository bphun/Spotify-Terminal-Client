#ifndef CURSOR_H
#define CURSOR_H

#include <string>

#include "../utils/json.h"

class Cursor {
	
private:

	std::string after;

public:

	Cursor();
	Cursor(nlohmann::json cursorJson);

	std::string GetAfter();

};


#endif