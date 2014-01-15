

#include "typedefs.h"
#include <sstream>
#include <fstream>

class Files {

public:
	static SiString slurp(const char* filename) {
		std::fstream file(SiString(filename),std::ifstream::in);
		std::stringstream sstr;
		sstr << file.rdbuf();
		return sstr.str();
	}

	static SiString slurp(const SiString& filename) {
		return slurp(filename.c_str());
	}


};