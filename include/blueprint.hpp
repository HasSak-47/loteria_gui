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
	VALUE_MASK = 0xff0,
};

ButtonType operator&(ButtonType a, ButtonType b);
ButtonType operator|(ButtonType a, ButtonType b);
ButtonType operator^(ButtonType a, ButtonType b);

class BlueprintCell;
class Blueprint;
class LineButton;

struct LineButton : public QWidget {
	QGridLayout* layout;
	QPushButton* button;
	QLineEdit* line;
	LineButton(QWidget* parent = nullptr);
	~LineButton();
};

class BlueprintCell : public QWidget {
private:
	QWidget* _child;
	ButtonType _type = ButtonType::Random;
	Blueprint* _blueprint;

	void toggle_type();
	void create_button(const char* text);
public:
	size_t x, y;
	BlueprintCell(size_t x, size_t y, Blueprint* parent);
	~BlueprintCell() override {}
	void render();

	friend class Blueprint;
};

struct BlueprintParam {
	std::string name;
	std::vector<size_t> values;
};

class Blueprint : public QWidget {
	BlueprintCell* _cells[4][4];
	QGridLayout* _grid;
public:
	size_t count = 0;
	size_t total = 0;

	Blueprint(QWidget* parent = nullptr);
	~Blueprint() override {}

	friend class BlueprintCell;
	std::vector<BlueprintParam> build();
};

extern const std::string options[];

#endif
