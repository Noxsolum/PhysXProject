#pragma once

#include <string>
using namespace std;

//Generic exception.

// #################################################################
// ### Inherit from this class to implement your own exceptions. ###
// #################################################################
class Exception
{
	string message;

public:
	Exception(const string s) : message(s) {};

	virtual const string& what() const throw() { return message; }
};

