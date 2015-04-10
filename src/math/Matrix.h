#ifndef MATRIX_H_
#define MATRIX_H_

namespace math {

class Matrix {
	int w, h, *mat;

public:
	Matrix(int, int);
	int getWidth();
	int getHeight();
	int getElem(int, int);
	float *VecMultiply(float *vec, int length);
	virtual ~Matrix();
};

} // namespace math

#endif /* MATRIX_H_ */
