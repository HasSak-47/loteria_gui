#include <runner.hpp>
#include <stdlib.h>

// windows
#if defined(__WIN32) &&  defined(__WIN64)

// ignore all the fancy pipe shit this is just a system function call wrapper
void Runner::run(){
	std::string line = this->_cmd.cmd;
	for(const& auto arg : this->_cmd.args){
		line += " " + arg
	}

	system(line);
}


#endif

// linux
#ifdef __linux
#endif
