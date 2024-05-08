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
	std::vector<std::string> args;
public:
	CmdBuilder(std::string cmd): _cmd(cmd){ }

	CmdBuilder& add_arg(std::string arg){
		this->args.push_back(arg);
		return *this;
	}

	Cmd build(){
		return {this->_cmd, this->args};
	}
};

class Runner{
public:
	enum Pipes{
		stdin = 1,
		stdout= 2,
		stderr= 4,
	};
private:
	Cmd _cmd;
	Pipes _pipe;

	std::string out;
public:
	Runner(Cmd cmd): _cmd(cmd){ }

	void pipe_stdin(){
		this->_pipe = (Pipes)(this->_pipe | stdin);
	}
	void pipe_stdout(){
		this->_pipe = (Pipes)(this->_pipe | stdout);
	}
	void pipe_stderr(){
		this->_pipe = (Pipes)(this->_pipe | stdout);
	}

	void pipe_in(const std::string& msg);
	std::string pipe_out();

	void run();

};

#endif
