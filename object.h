#pragma once

namespace snake {

class Pixel;

class Object {
public:
	Object();

	virtual void Draw();
private:
	typedef std::vector<Pixel> object_vec_t;

	object_vec_t object_;
};

}