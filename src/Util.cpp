#include <algorithm>
#include <math.h>


float rand01() {
    return (float)rand() / (float)RAND_MAX ;
}

int toInt(float value) {
	return (int) round(value);
}

int modIndex(int i, unsigned max) {
	// if (i < 0 || (unsigned)i >= max) {
	// 	int mod = i % (int) max;
	// 	// % operation returns negative values
	//     if (mod < 0) {
	//         mod += max;
	//     }
	// 	return mod;
	// } else {
	// 	return i;
	// }
	if (i < 0) {
		i += max;
	} else if ((unsigned)i >= max) {
		i -= max;
	}
	return i;
}

int modIndex(float i, unsigned max) {
	return modIndex(toInt(i), max);
}
