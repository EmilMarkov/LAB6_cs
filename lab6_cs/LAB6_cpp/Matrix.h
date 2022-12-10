#pragma once

#include <array>
#include <stdio.h>
#include <random>
#include <stdarg.h>
#include <iostream>

class Matrix {

public:
	int* row;
	int* col;
	int size;

	Matrix(const int n, bool flag);
	Matrix(const int n, ...);
	Matrix(Matrix& base, bool flag);
	~Matrix();
	Matrix& operator=(const Matrix& source);
	int** build();
};

Matrix::Matrix(const int n, bool flag) {
	this->row = new int[n];
	this->col = new int[n];
	this->size = n;
	
	for (int i = 0; i < n; i++) {
		row[i] = i;
	}
	for (int i = n + 1; i < n * 2; i++) {
		row[i] = i;
	}
}

Matrix::Matrix(int n, ...) {
	int* params = new int[n];
	this->row = new int[n];
	this->col = new int[n];
	size = n;

	va_list tmp_par;
	va_start(tmp_par, n);
	for (int i = 0; i < n; i++) {
		params[i] = va_arg(tmp_par, int);
	}
	va_end(tmp_par);

	for (int i = 0; i < n / 2; i++) {
		row[i] = params[i];
	}
	for (int i = (n / 2) + 1; i < n; i++) {
		col[i] = params[i];
	}

	delete[] params;
}

Matrix::Matrix(Matrix& base, bool flag) {
	this->size = base.size;
	this->row = base.row;
	this->col = base.col;
}

Matrix::~Matrix() { 
	delete[] row;
	delete[] col;
}

Matrix& Matrix::operator=(const Matrix& source) {
	size = source.size;
	for (int i = 0; i < size / 2; i++) {
		row[i] = source.row[i];
	}
	for (int i = (size / 2) + 1; i < size; i++) {
		col[i] = source.col[i];
	}
	return *this;
}

int** Matrix::build() {
	int n = this->size;

	int* values = new int[n + n - 2];
	for (int i = 0; i < n; i++) {
		values[i] = row[i];
	}
	for (int i = n; i < n + n - 2; i++) {
		values[i] = col[i];
	}

	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
	}

	for (int i = 0, k = 0; i < n + n - 2, k < n; i++) {
		for (int j = 0; j < n; i++) {
			matrix[n - k - 1][j] = values[i];
		}
	}
	return matrix;
}