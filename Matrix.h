#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include <string>
#include <assert.h>
#include "Auxiliaries.h"
#include "Exceptions.h"

namespace data_struct {
	template<class T>
	class Matrix {
		Dimensions dimension;
		T* matrix;

		bool dimensions_check(Dimensions dims) {
			if (dims.getCol() <= 0 || dims.getRow() <= 0) {
				return false;
			}
			return true;
		}

		int index(const int x, const int y) const {
			if (x < 0 || y < 0 || x >= width() || y >= height())
				throw AccessIllegalElement();
			return x + (width() * y);
		}

	public:
		// Matrix ctor, assuming T has default ctor, dtor and operator=.
		Matrix(const Dimensions dims, const T value = T()) :
			dimension(dimensions_check(dims) ? dims : throw IllegalInitialization()),
			matrix(new T[size()]) {
			for (int y = 0; y < height(); y++) {
				for (int x = 0; x < width(); x++) {
					(*this)(y, x) = value;
				}
			}
		}

		// Matrix copy ctor, assuming T has default ctor and operator=.
		Matrix(const Matrix<T> & mat_to_copy) :
			dimension(mat_to_copy.height(), mat_to_copy.width()), matrix(new T[size()]) {
			for (int y = 0; y < height(); y++) {
				for (int x = 0; x < width(); x++) {
					(*this)(y, x) = mat_to_copy(y, x);
				}
			}
		}

		// Matrix dtor, assuming T has dtor.
		~Matrix()
		{
			delete[] matrix;
		}

		// Matrix operator=, assuming T has default ctor, dtor and operator=.
		Matrix& operator=(const Matrix & right_mat) {
			if (this == &right_mat) {
				return *this;
			}
			int temp_mat_size = right_mat.size();
			T* temp = new T[temp_mat_size];
			try {
				for (int i = 0; i < temp_mat_size; i++) {
					temp[i] = right_mat.matrix[i];
				}
			}
			catch (...) {
				delete[] temp;
				throw;
			}
			delete[] matrix;
			matrix = temp;
			dimension = right_mat.dimension;
			return *this;
		}

		// Matrix operator().
		T& operator()(const int y, const int x) {
			return matrix[index(x, y)];
		}

		//Diagonal matrix. assuming T has default ctor, dtor and operator=
		static Matrix Diagonal(const int size, const T value) {
			Matrix return_mat(Dimensions(size, size));
			for (int d = 0; d < size; d++) {
				return_mat(d, d) = value;
			}
			return return_mat;
		}

		// Matrix operator().
		const T& operator()(const int y, const int x) const {
			return matrix[index(x, y)];
		}

		// Matrix dimensions check.
		int height() const { return dimension.getRow(); }
		int width() const { return dimension.getCol(); };
		int size() const { return width()* height(); }

		// Matrix transpose, assuming T has default ctor, dtor and operator=
		Matrix transpose() const {
			Dimensions transposed_dims(width(), height());
			Matrix result(transposed_dims);
			for (int y = 0; y < height(); y++) {
				for (int x = 0; x < width(); x++) {
					result(x, y) = (*this)(y, x);
				}
			}
			return result;
		}

		// Matrix operator-, assuming T has default ctor, dtor, operator= and operator-
		Matrix operator-() const {
			Dimensions dims(height(), width());
			Matrix result(dims);
			for (int y = 0; y < result.height(); y++) {
				for (int x = 0; x < result.width(); x++) {
					result(y, x) = -(*this)(y, x);
				}
			}
			return result;
		}

		// Matrix operator+=, assuming T has default ctor, dtor and copy ctor, operator+ and operator=.
		Matrix& operator+=(const T & value) {
			Matrix copy = *this;
			*this = copy + value;
			return *this;
		}
	private:
		// Functor for < operator. assuming T has copy ctor and operator<.
		class isSmaller {
		private:
			const T& value;
		public:
			isSmaller(const T& value) : value(value) {}
			bool operator()(const T& rhs) const {
				return value < rhs;
			}
		};

		// Functor for > operator. assuming T has copy ctor and operator>.
		class isBigger {
		private:
			const T& value;
		public:
			isBigger(const T& value) : value(value) {}
			bool operator()(const T& rhs) const {
				return value > rhs;
			}
		};

		// Functor for >= operator. assuming T has copy ctor and operator>=.
		class isBiggerOrEqual {
		private:
			const T& value;
		public:
			isBiggerOrEqual(const T& value) : value(value) {}
			bool operator()(const T& rhs) const {
				return value >= rhs;
			}
		};

		// Functor for <= operator. assuming T has copy ctor and operator<=.
		class isSmallerOrEqual {
		private:
			const T& value;
		public:
			isSmallerOrEqual(const T& value) : value(value) {}
			bool operator()(const T& rhs) const {
				return value <= rhs;
			}
		};

		// Functor for == operator. assuming T has copy ctor and operator==.
		class isEqual {
		private:
			const T& value;
		public:
			isEqual(const T& value) : value(value) {}
			bool operator()(const T& rhs) const {
				return value == rhs;
			}
		};

		// Functor for != operator. assuming T has copy ctor and operator!=.
		class isNotEqual {
		private:
			const T& value;
		public:
			isNotEqual(const T& value) : value(value) {}
			bool operator()(const T& rhs) const {
				return value != rhs;
			}
		};

		// Binary operation, assuming T support this operation.
		template<typename Op>
		Matrix<bool> binary_operation(const T & value, Op op) {
			Matrix<bool> result(this->dimension, false);
			for (int y = 0; y < height(); y++) {
				for (int x = 0; x < width(); x++) {
					if (op((*this)(y, x))) {
						result(y, x) = true;
					}
				}
			}
			return result;
		}

	public:
		// Matrix operator<, assuming T has operator>, ctor and dtor.
		Matrix<bool> operator<(const T & value) {
			Matrix<bool> return_mat = binary_operation(value, isBigger(value));
			return return_mat; //TODO: ask about it.
		}

		// Matrix operator>, assuming T has ctor, dtor and operator>.
		Matrix<bool> operator>(const T & value) {
			Matrix<bool> return_mat = binary_operation(value, isSmaller(value));
			return return_mat; //TODO: ask about it.
		}

		// Matrix operator>=, assuming T has ctor, dtor and operator<=.
		Matrix<bool> operator>=(const T & value) {
			Matrix<bool> return_mat = binary_operation(value, isSmallerOrEqual(value));
			return return_mat; //TODO: ask about it.
		}

		// Matrix operator<=, assuming T has ctor, dtor and operator>=.
		Matrix<bool> operator<=(const T & value) {
			Matrix<bool> return_mat = binary_operation(value, isBiggerOrEqual(value));
			return return_mat; //TODO: ask about it.
		}

		// Matrix operator==, assuming T has ctor, dtor and operator==.
		Matrix<bool> operator==(const T & value) {
			Matrix<bool> return_mat = binary_operation(value, isEqual(value));
			return return_mat; //TODO: ask about it.
		}

		// Matrix operator!=, assuming T has ctor, dtor and operator!=.
		Matrix<bool> operator!=(const T & value) {
			Matrix<bool> return_mat = binary_operation(value, isNotEqual(value));
			return return_mat; //TODO: ask about it.
		}

		class iterator
		{
			const Matrix<T>* matrix_ptr;
			int ptr_index;
			friend class Matrix<T>;
			iterator(const Matrix<T>* matrix, int index) :
				matrix_ptr(matrix), ptr_index(index) {}
		public:

			T& operator*() const {
				if (ptr_index < 0 || ptr_index >= matrix_ptr->size()) {
					throw AccessIllegalElement();
				}
				return matrix_ptr->matrix[ptr_index];
			}
			iterator& operator++() {
				++ptr_index;
				return *this;
			}
			iterator operator++(int) {
				iterator result = *this;
				++* this;
				return result;
			}

			bool operator==(const iterator& it) const {
				assert(matrix_ptr == it.matrix_ptr);
				return ptr_index == it.ptr_index;
			}
			bool operator!=(const iterator & it) const {
				return !(*this == it);
			}

			iterator(const iterator&) = default;
			iterator& operator=(const iterator&) = default;
			~iterator() = default;
		};

		class const_iterator {
			const Matrix<T>* matrix_ptr;
			int ptr_index;
			friend class Matrix<T>;
			const_iterator(const Matrix<T>* matrix, int index) :
				matrix_ptr(matrix), ptr_index(index) {}
		public:

			T operator*() const {
				if (ptr_index < 0 || ptr_index >= this->matrix_ptr->size()) {
					throw AccessIllegalElement();
				}
				return matrix_ptr->matrix[ptr_index];
			}
			const_iterator& operator++() {
				++ptr_index;
				return *this;
			}
			const_iterator operator++(int) {
				const_iterator result = *this;
				++* this;
				return result;
			}

			bool operator==(const const_iterator& it) const {
				assert(matrix_ptr == it.matrix_ptr);
				return ptr_index == it.ptr_index;
			}
			bool operator!=(const const_iterator & it) const {
				return !(*this == it);
			}

			const_iterator(const const_iterator&) = default;
			const_iterator& operator=(const const_iterator&) = default;
			~const_iterator() = default;
		};

		iterator begin() {
			return iterator(this, 0);
		}

		iterator end() {
			return iterator(this, size());
		}

		const_iterator begin() const {
			return const_iterator(this, 0);
		}

		const_iterator end() const {
			return const_iterator(this, size());
		}

		// Apply function, assuming T has copy ctor and operator=.
		template<typename Obj>
		Matrix apply(Obj obj) const {
			Matrix result(*this);
			for (int y = 0; y < height(); y++) {
				for (int x = 0; x < width(); x++) {
					result(y, x) = obj((*this)(y, x));
				}
			}
			return result;
		}
	};

	// Matrix operator+, assuming T has default ctor, dtor, operator+ and operator=.
	template<class T>
	Matrix<T> operator+(const Matrix<T>& left_mat, const Matrix<T>& right_mat)
	{
		Dimensions left(left_mat.height(), left_mat.width()); // TODO: maybe reversed, check it.
		Dimensions right(right_mat.height(), right_mat.width()); // TODO: maybe reversed, check it.
		if (left != right) {
			throw Matrix<T>::DimensionMismatch(left, right); //TODO: ask about it.
		}
		Dimensions dims(left_mat.height(), left_mat.width());
		Matrix<T> result(dims);
		for (int y = 0; y < result.height(); y++) {
			for (int x = 0; x < result.width(); x++) {
				result(y, x) = left_mat(y, x) + right_mat(y, x);
			}
		}
		return result;
	}

	// Matrix operator-, assuming T has default ctor, dtor, operator+, operator- and operator=.
	template<class T>
	Matrix<T> operator-(const Matrix<T>& left_mat, const Matrix<T>& right_mat) {
		Dimensions left(left_mat.height(), left_mat.width()); // TODO: maybe reversed, check it.
		Dimensions right(right_mat.height(), right_mat.width()); // TODO: maybe reversed, check it.
		if (left != right) {
			throw Matrix<T>::DimensionMismatch(left, right); // TODO: ask about it.
		}
		Matrix<T> result = left_mat + (-right_mat);
		return result;
	}

	// Matrix operator+ with T, assuming T has default and copy ctor, operator+ and operator=.
	template<class T>
	Matrix<T> operator+(const Matrix<T> & left_mat, const T & value) {
		Dimensions dims(left_mat.height(), left_mat.width()); // TODO: see if better take value by value.
		Matrix<T> right_mat(dims, value);
		return left_mat + right_mat;
	}

	// Matrix operator+ with T, assuming T has default and copy ctor, operator+ and operator=.
	template<class T>
	Matrix<T> operator+(const T & value, const Matrix<T> & right_mat) {
		Dimensions dims(right_mat.height(), right_mat.width()); // TODO: see if better take value by value.
		Matrix<T> left_mat(dims, value);
		return left_mat + right_mat;
	}

	// All function, assuming T has operator!=.
	template<class T>
	bool all(const T & mat) {
		for (int y = 0; y < mat.height(); y++) {
			for (int x = 0; x < mat.width(); x++) {
				if (!mat(y, x)) {
					return false;
				}
			}
		}
		return true;
	}

	// Any function, assuming T has operator==.
	template<class T>
	bool any(const T & mat) {
		for (int y = 0; y < mat.height(); y++) {
			for (int x = 0; x < mat.width(); x++) {
				if (mat(y, x)) {
					return true;
				}
			}
		}
		return false;
	}

	// Matrix operator<<, assuming T has default ctor, copy ctor, dtor, operator<< and operator=.
	template<class T>
	std::ostream& operator<<(std::ostream & out, Matrix<T> right_mat)
	{
		return printMatrix(out, right_mat.begin(), right_mat.end(), right_mat.width());
	}
}

#endif // !EX3_MATRIX_H
