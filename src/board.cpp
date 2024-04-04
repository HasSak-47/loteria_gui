#include <board.hpp>

using rust_board_builder = BoardBuilder::__rust_board_builder;

extern "C"{
	rust_board_builder new_builder();
	void drop_builder(rust_board_builder builder);
	bool add_actor(rust_board_builder* builder, char* name, uint8_t* params);
	void build(rust_board_builder* builder);
	Board* get_board(rust_board_builder* builder, size_t index);
	size_t get_boards_len(rust_board_builder* builder, size_t index);
}

BoardBuilder::BoardBuilder(){
	auto buffer = new_builder();
	this->__builder = *(BoardBuilder::__rust_board_builder*)&buffer;
}

BoardBuilder::~BoardBuilder(){
	drop_builder(this->__builder);
}

void BoardBuilder::build(){
	::build(&this->__builder);
}

bool BoardBuilder::add_actor(char* name, uint8_t* params){
	return ::add_actor(&this->__builder, name, params);
}

Board* BoardBuilder::get_board(size_t index){
	return ::get_board(&this->__builder, index);
}

size_t BoardBuilder::get_board_count(){
	return get_boards_len(&this->__builder, 0);
}

