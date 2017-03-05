#ifndef CORE_UTILS_MATH_H_
#define CORE_UTILS_MATH_H_

namespace core {

template <typename T>
T max(T x, T y){
	if(x > y)
		return x;
	return y;
}

template <typename T>
T min(T x, T y){
	if(x < y)
		return x;
	return y;
}

};

#endif /* CORE_UTILS_MATH_H_ */
