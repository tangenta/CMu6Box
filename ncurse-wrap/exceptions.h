#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

class Exception {
public:
    Exception(std::string const& m): msg(m) {}
private:
    std::string msg;
};

struct FatalError: public Exception {
    FatalError(std::string const& m): Exception(m) {}
};
struct OutOfRangeError: public Exception {
    OutOfRangeError(std::string const& m): Exception(m) {}
};
struct InvalidError: public Exception {
    InvalidError(std::string const& m): Exception(m) {}
};
struct JsonOpenError: public Exception {
    JsonOpenError(std::string const& m): Exception(m) {}
};

#endif // EXCEPTIONS_H
