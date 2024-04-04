#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <cstddef>
#include <cstdint>

struct Board{
	int board[16];
};

class BoardBuilder{
public:
	struct __rust_board_builder{
		uint8_t __rust_object_memory[24];
	};
	__rust_board_builder __builder;

	BoardBuilder();
	~BoardBuilder();

	void build();
	bool add_actor(char* name, uint8_t* params);
	Board* get_board(size_t index = 0);
	size_t get_board_count();
};

#endif
