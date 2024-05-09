#include <iostream>
#include <runner.hpp>
#include <stdlib.h>

#define FORCE_WIN

// windows stuff
#if defined(__WIN32) || defined(__WIN64) || defined(FORCE_WIN)

Cmd CmdBuilder::build(){
	std::string cmd = "";
	if (!this->_path)
		cmd = ".\\";
	cmd += this->_cmd + ".exe";

	return {cmd, this->_args};
}

// ignore all the fancy pipe shit this is just a system function call wrapper
void Runner::run(){
	std::string line = this->_cmd.cmd;
	for(const auto& arg : this->_cmd.args){
		line += " " + arg;
	}

	std::cout << "runnin: (" << line << ")\n";
}


#endif
