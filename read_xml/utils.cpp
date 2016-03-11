#include "utils.h"
#include "gl_settings.h"

namespace Utils {
template <typename Type>
    std::string toString(const Type& element) {
    std::stringstream sstream;
    sstream << element;
    return sstream.str();
}

// First business logic shall be agreed. Some tags can be missed (with default values set). Some - can not! So
// there are two types of tag-handling: Error (program should terminate) and Warning - program should warn and continue.
template <typename Type>
void ReportTagMissing(const std::string & tag, const Type & default_value) {
    std::cerr << "[WARNING] Tag <" << tag << "> is missing; default value '" << default_value << "' set." << std::endl;
}
}
