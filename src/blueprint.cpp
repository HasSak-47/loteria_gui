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
	this->_blueprint = parent;
	this->_child = nullptr;
}

void BlueprintCell::create_button(const char* text){
	this->_child = new QPushButton(text, this);
	this->_blueprint->_grid->addWidget(this->_child, x, y);
	connect((QPushButton*)this->_child, &QPushButton::clicked, this, &BlueprintCell::toggle_type);
}

LineButton::LineButton(QWidget* parent) : QWidget(parent) {
	button = new QPushButton("c", this);
	line = new QLineEdit(this);

	button->setFixedWidth(20);

	layout = new QGridLayout(this);
	layout->addWidget(line, 0, 0);
	layout->addWidget(button, 0, 1);
	setLayout(layout);
}

LineButton::~LineButton() {
	delete button;
	delete line;
}

void BlueprintCell::render(){
	if (this->_child != nullptr){
		_blueprint->_grid->removeWidget(this->_child);
		delete this->_child;
	}

	switch (this->_type & ButtonType::TYPE_MASK){
		case ButtonType::Random:
			this->create_button("Random");
			break;
		case ButtonType::MarkCopy:
			this->create_button("MarkCopy");
			break;
		case ButtonType::SetTo:
			this->_child = new LineButton(this);
			_blueprint->_grid->addWidget(this->_child, x, y);
			connect(((LineButton*)this->_child)->button, &QPushButton::clicked, this, &BlueprintCell::toggle_type);
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

const std::string options[] = {
	"Random",
	"MarkCopy",
	"SetTo",

	"SetCount",
	"SetTotal",
};

std::vector<BlueprintParam> Blueprint::build(){
	std::vector<BlueprintParam> params = {};

	params.push_back({"SetCount", {this->count}});
	params.push_back({"SetTotal", {this->total}});
	for (size_t x = 0; x < 4; x++){
		for (size_t y = 0; y < 4; y++){
			auto* cell = this->_cells[x][y];
			switch(cell->_type & ButtonType::TYPE_MASK){
				case ButtonType::Random:
					break;
				case ButtonType::MarkCopy:
					params.push_back({"MarkCopy", {x, y}});
					break;
				case ButtonType::SetTo:
					params.push_back({"SetTo", {
						x,
						y,
						((LineButton*)cell->_child)->line->text().toUInt()
					}});
					break;
				default:
					break;
			}
		}
	}

	return params;
}
