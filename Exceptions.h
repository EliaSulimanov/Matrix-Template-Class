#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "Auxiliaries.h"

namespace data_struct {
	class Exception : public std::exception {};

	class AccessIllegalElement : public Exception {
	public:
		const char* what() const noexcept override;
	};

	class IllegalInitialization : public Exception {
	public:
		const char* what() const noexcept override;
	};

	class DimensionMismatch : public Exception {
		std::string error;
	public:
		DimensionMismatch(Dimensions mat1, Dimensions mat2);
		const char* what() const noexcept override;
	};

	class GameException : public Exception {};

	class IllegalArgument : public GameException {
	public:
		const char* what() const noexcept override;
	};

	class IllegalCell : public GameException {
	public:
		const char* what() const noexcept override;
	};

	class CellEmpty : public GameException {
	public:
		const char* what() const noexcept override;
	};

	class MoveTooFar : public GameException {
	public:
		const char* what() const noexcept override;
	};

	class CellOccupied : public GameException {
	public:
		const char* what() const noexcept override;
	};

	class OutOfRange : public GameException {
	public:
		const char* what() const noexcept override;
	};

	class OutOfAmmo : public GameException {
	public:
		const char* what() const noexcept override;
	};

	class IllegalTarget : public GameException {
	public:
		const char* what() const noexcept override;
	};
}

#endif