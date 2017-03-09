#ifndef CORE_MEMORY_H_
#define CORE_MEMORY_H_

#include <stdexcept>

namespace core {

template<typename T = char>
class Array {

public:
	const size_t size;

	Array(T* a, size_t size) :
		size(size), array(a) {
	}

	virtual ~Array() {}

	T* operator*() const {
		return array;
	}

	T& operator[](size_t index) const throw (std::out_of_range) {
		checkRange(index);
		return *(array + index);
	}

	T* operator+(size_t index) const throw (std::out_of_range) {
		checkRange(index);
		return array + index;
	}

protected:
	T* array;

	inline void checkRange(size_t index) const throw (std::out_of_range) {
		if (index >= 0 && index < size) {
			return;
		}
		// todo: index info
		throw std::out_of_range("core::Array");
	}

};

template<typename T = char>
class AutoArray : public Array<T> {

public:
	AutoArray(T* a, size_t size) : Array<T>(a, size){
	}

	AutoArray(Array<T> array) : Array<T>(*array, array.size){
	}

	virtual ~AutoArray() {
		if (this->array != 0) {
			delete[] this->array;
			this->array = 0;
		}
	}

	Array<T> takeAway(){
		Array<T> result(this->array, this->size);
		this->array = 0;
		return result;
	}

private:
	AutoArray(const AutoArray& other);
	AutoArray& operator=(const AutoArray&);
};

};

#endif /* CORE_MEMORY_H_ */
