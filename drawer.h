#pragma once

#include <vector>

#include "object.h"

namespace snake {

class Drawer {
public:
	Drawer();
	void Add(const Object &obj); // add a new object to the object list
	void Validate() const; // display the objects in the object list
private:
	std::vector<Object> objects_;
};

} //snake