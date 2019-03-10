#include <exception>

class windowException : public std::exception {
	public:
	  virtual const char* what() const throw() {
			return "Unspesified window exception.";
			}
};


class poorParameterException : public windowException {
	public:
		virtual const char* what() const throw() {
			return "Width and/or height is less than or equal to zero!";
		}
};

class tooLargeImageException : public windowException {
		public:
		virtual const char* what() const throw() {
			return "Width and/or height is too large! Only images less than 100x100 accepted.";
		}
};

class notRunningException : public windowException {
		public:
		virtual const char* what() const throw() {
			return "The window is not running!";
		}
};

class fontLoadException : public windowException {
		public:
		virtual const char* what() const throw() {
			return "Failed to load the font!";
		}
};
