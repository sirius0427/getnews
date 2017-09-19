#include <iostream>
#include <math.h>
#include <cstring>

double similarity( char *input );

#ifdef __cplusplus
extern "C" {  // 即使这是一个C++程序，下列这个函数的实现也要以C约定的风格来搞！
#endif

	double c_similarity(char *input)
	{
		double ret=similarity(input);
		return ret;
	}

#ifdef __cplusplus
}
#endif
