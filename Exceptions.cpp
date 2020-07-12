#include "Exceptions.h"

const char* data_struct::AccessIllegalElement::what() const noexcept
{
	return "data_struct matrix error: An attempt to access an illegal element";
}

const char* data_struct::IllegalInitialization::what() const noexcept
{
	return "data_struct matrix error: Illegal initialization values";
}

data_struct::DimensionMismatch::DimensionMismatch(Dimensions mat1, Dimensions mat2) :
	error("data_struct matrix error: Dimension mismatch: " + mat1.toString() + " " + mat2.toString()) {}

const char* data_struct::DimensionMismatch::what() const noexcept
{
	return error.c_str();
}

const char* data_struct::IllegalArgument::what() const noexcept
{
	return "A game related error has occurred: IllegalArgument";
}

const char* data_struct::IllegalCell::what() const noexcept
{
	return "A game related error has occurred: IllegalCell";
}

const char* data_struct::CellEmpty::what() const noexcept
{
	return "A game related error has occurred: CellEmpty";
}

const char* data_struct::MoveTooFar::what() const noexcept
{
	return "A game related error has occurred: MoveTooFar";
}

const char* data_struct::CellOccupied::what() const noexcept
{
	return "A game related error has occurred: CellOccupied";
}

const char* data_struct::OutOfRange::what() const noexcept
{
	return "A game related error has occurred: OutOfRange";
}

const char* data_struct::OutOfAmmo::what() const noexcept
{
	return "A game related error has occurred: OutOfAmmo";
}

const char* data_struct::IllegalTarget::what() const noexcept
{
	return "A game related error has occurred: IllegalTarget";
}