#pragma once

#include <vector>

namespace snake {

class Pixel;
class Object;

class Drawer {
public:
	explicit Drawer(uint32_t r, uint32_t c);
	void Add(const Object &obj); // add a new object to the object list
	void Start() const;

private:
	// Screen Interaction
	void ClearScreen() const;
	void NewLine() const;
	void Rewind() const;
	void DrawInternal();


	typedef std::vector<Object> object_vec_t;

	std::vector<std::vector<Pixel> > image_buffer_;
	object_vec_t objects_;

	uint32_t row_;
	uint32_t col_;
};

} //snake