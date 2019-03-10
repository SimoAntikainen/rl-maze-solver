#include <exception>

class configException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Unspecified configreader exception.";
	}
};

class invalidDoubleException : public configException {
public:
	virtual const char* what() const throw() {
		return "Value of alpha and gamma must be between 0.0 and 1.0!";
	}
};

class configIOException : public configException {
public:
	virtual const char* what() const throw() {
		return "Could not open file 'config.txt'! Data maybe corrupt or file not present!";
	}
};

class readerIOException : public configException {
public:
	virtual const char* what() const throw() {
		return "Could not open file for reading Q-matrix! Data maybe corrupt or file not present!";
	}
};

class invalidHeightWidthException : public configException {
public:
	virtual const char* what() const throw() {
		return "The saved height and width must match present dimensions for .png-file!";
	}
};
