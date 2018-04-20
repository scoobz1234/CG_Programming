#pragma once


class Matrix {

public:
	Matrix();
	~Matrix();

	void MakeIdentity();
	void Transpose();

	Matrix Transposed();

public:
	float mArr[4][4] = { 0, 0 };


};

