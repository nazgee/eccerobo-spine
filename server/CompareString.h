#ifndef COMPARESTRING_H_
#define COMPARESTRING_H_

namespace ecce {
struct CompareString {
		bool operator()(const std::string& lhs, const std::string& rhs) const {
			return (strcmp(lhs.c_str() , rhs.c_str())) < 0;
		}
	};
} // ecce

#endif
