#include "gl_settings.h"

#ifndef ERRORS_CPP
#define ERRORS_CPP

class MissingTagError
{
public:
    MissingTagError();
    MissingTagError(const std::string & tag) {
        _tag = tag;
    }
    std::string tag() {
        return _tag;
    }
private:
    std::string _tag;
};

class ParserError
{
public:
    ParserError();
    ParserError(const std::string & msg, const std::string & path) {
        _msg = msg;
        _path = path;
    }
    std::string path() {
        return _path;
    }
    std::string msg() {
        return _msg;
    }

private:
    std::string _path;
    std::string _msg;
};

#endif
