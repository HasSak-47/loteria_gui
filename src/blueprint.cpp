#include <blueprint.hpp>
#include <iostream>

#define ENUM_OPER(operator) \
	static_cast<typeof(a)>(static_cast<int>(a) operator static_cast<int>(b))

ButtonType operator&(ButtonType a, ButtonType b) { return ENUM_OPER(&); }
ButtonType operator|(ButtonType a, ButtonType b) { return ENUM_OPER(|); }
ButtonType operator^(ButtonType a, ButtonType b) { return ENUM_OPER(^); }

BlueprintCell::BlueprintCell(size_t x, size_t y, Blueprint* parent) : QWidget(parent) {
	this->x = x;
	this->y = y;

	this->_random = new QPushButton("Random", this);
	this->_copy = new QPushButton("SetTo", this);
	this->_setto = new ButtonLine(this);

	((QGridLayout*)this->parent())->addWidget(this->_random, x, y);
	((QGridLayout*)this->parent())->addWidget(this->_copy, x, y);
	((QGridLayout*)this->parent())->addWidget(this->_setto, x, y);

	this->render();
}

void BlueprintCell::render(){
	this->setLayout(this->_setto->layout);
	switch (this->_type & ButtonType::TYPE_MASK){
		case ButtonType::Random:
			this->_setto->hide();
			this->_random->show();
			this->_copy->hide();
			break;
		case ButtonType::MarkCopy:
			this->_setto->hide();
			this->_random->hide();
			this->_copy->show();
			break;
		case ButtonType::SetTo:
			this->_setto->show();
			this->_random->hide();
			this->_copy->hide();
			break;
		default:
			break;
	}

}

void BlueprintCell::toggle_type(){
	switch (this->_type & ButtonType::TYPE_MASK){
		case ButtonType::Random:
			this->_type = ButtonType::MarkCopy;
			break;
		case ButtonType::MarkCopy:
			this->_type = ButtonType::SetTo;
			break;
		case ButtonType::SetTo:
			this->_type = ButtonType::Random;
		break;
		default:
			break;
	}
	this->render();
}

Blueprint::Blueprint(QWidget* parent) : QWidget(parent) {
	this->_grid = new QGridLayout(this);
	for (size_t x = 0; x < 4; x++){
		for (size_t y = 0; y < 4; y++){
			this->_cells[x][y] = new BlueprintCell(x, y, this);
			this->_cells[x][y]->render();
		}
	}

	setLayout(this->_grid);

}


