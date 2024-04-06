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
}

void BlueprintCell::render(){
	if (this->_child != nullptr){
		delete this->_child;
		((Blueprint*)this->parent())->_grid->removeWidget(this->_child);
	}
	this->_make_child();
	((Blueprint*)this->parent())->_grid->addWidget(this->_child, this->x, this->y);
}

void BlueprintCell::toggle_type(){
	std::cout << "toggled" << std::endl;
	switch(this->_type & ButtonType::TYPE_MASK){
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

struct ButtonLine : QWidget {
	QGridLayout* layout;
	QPushButton* button;
	QLineEdit* line;
	ButtonLine(QWidget* parent = nullptr) : QWidget(parent) {
		layout = new QGridLayout(this);
		button = new QPushButton("S", this);
		line   = new QLineEdit("Number", this);

		layout->addWidget(line, 0, 0);
		layout->addWidget(button, 0, 1);
		setLayout(layout);
	}
};

void BlueprintCell::_make_child(){
	switch(this->_type & ButtonType::TYPE_MASK){
		case ButtonType::Random:
			this->_child = new QPushButton("Random", this);
			connect((QPushButton*)_child, &QPushButton::clicked, this, &BlueprintCell::toggle_type);
			break;
		case ButtonType::MarkCopy:
			this->_child = new QPushButton("MarkCopy", this);
			connect((QPushButton*)_child, &QPushButton::clicked, this, &BlueprintCell::toggle_type);
			break;
		case ButtonType::SetTo:
			// this->_child = new ButtonLine(this);
			// connect(((ButtonLine*)_child)->button, &QPushButton::clicked, this, &BlueprintCell::toggle_type);
			break;
		default:
			break;
	}
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


