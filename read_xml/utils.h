#ifndef UTILS_H
#define UTILS_H

namespace Utils {

template <typename Type>
std::string toString(const Type &);

template <typename Type>
void ReportTagMissing(const std::string &, const Type &);

//template <typename Type>
//void ErrorTagMissing(const std::string &, const Type &);

}

#endif // UTILS_H
