#pragma once

#include <vector>

namespace snake {

class Pixel;

class Object {
public:
	Object();
	// explicit Object(std::vector<std::vector<char> > arr);

	virtual void Float(std::vector<std::vector<Pixel> > &buffer);
	virtual void UpdatePosition();
	virtual void UpdateDirection();
protected:
	typedef std::vector<Pixel> pixel_vec_t;
	
	pixel_vec_t object_;
};

}