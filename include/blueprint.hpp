#ifndef __BLUEPRINT_HPP__
#define __BLUEPRINT_HPP__

#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGridLayout>

enum class ButtonType {
	Random     = 0x01,
	MarkCopy   = 0x02,
	SetTo      = 0x03,
	TYPE_MASK  = 0x0f,
	VALUE_MASK = 0xf0,
};

ButtonType operator&(ButtonType a, ButtonType b);
ButtonType operator|(ButtonType a, ButtonType b);
ButtonType operator^(ButtonType a, ButtonType b);

class BlueprintCell;
class Blueprint;

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

class BlueprintCell : public QWidget {
private:
	QPushButton* _random;
	QPushButton* _clopy;
	ButtonLine* _setto;
	ButtonType _type = ButtonType::Random;

	void _make_child();
	void toggle_type();
public:
	size_t x, y;
	BlueprintCell(size_t x, size_t y, Blueprint* parent);

	void render();
};

class Blueprint : public QWidget {
	BlueprintCell* _cells[4][4];
	QGridLayout* _grid;
public:
	Blueprint(QWidget* parent = nullptr);
	~Blueprint() override {}

	friend class BlueprintCell;
};

#endif
