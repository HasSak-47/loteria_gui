#ifndef __RUNNER_HPP__
#define __RUNNER_HPP__

#include <string>
#include <vector>

struct Cmd{
	std::string cmd;
	std::vector<std::string> args;
};

class CmdBuilder{
private:
	std::string _cmd;
	std::vector<std::string> _args;
	bool _path;
public:
	CmdBuilder(std::string cmd): _cmd(cmd){ }

	CmdBuilder& add_arg(std::string arg){
		this->_args.push_back(arg);
		return *this;
	}

	void set_local(){
		this->_path = false;
	}

	Cmd build();
};

class Runner{
private:
	Cmd _cmd;
public:
	Runner(Cmd cmd): _cmd(cmd){ }

	// void pipe_in(const std::string& msg);
	// std::string pipe_out();

	void run();

};

#endif
