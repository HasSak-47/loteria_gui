#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFileDialog>

#include <board.hpp>
#include <blueprint.hpp>
#include <iostream>

class LabelText : public QWidget {
private:
	QLabel* label;
	QLineEdit* line_edit;
	QGridLayout* layout;
public:
	LabelText(const char* text, const char* def, size_t line_width, QWidget* parent = nullptr) : QWidget(parent) {
		label = new QLabel(text, this);
		if (def!= nullptr)
			line_edit = new QLineEdit(def, this);
		else
			line_edit = new QLineEdit(this);

		if (line_width > 0)
			line_edit->setFixedWidth(line_width);
		line_edit->setContentsMargins(0, 0, 0, 0);

		layout = new QGridLayout(this);

		layout->addWidget(label, 0, 0);
		layout->addWidget(line_edit, 0, 1);
		setLayout(layout);
	}

	~LabelText() override {
		delete label;
		delete line_edit;
	}

	friend class MyApp;
};

class PathSelector : public QWidget {
private:
	QLineEdit* line_edit;
	QPushButton* button;
	QFileDialog* dialog;
	QGridLayout* layout;
public:
	PathSelector(const char* text, QWidget* parent = nullptr) : QWidget(parent) {
		if(text != nullptr)
			line_edit = new QLineEdit(text, this);
		line_edit->setReadOnly(true);
		button = new QPushButton("...", this);
		button->setFixedWidth(30);
		dialog = new QFileDialog(this);
		dialog->setFileMode(QFileDialog::Directory);
		dialog->setOption(QFileDialog::ShowDirsOnly);

		layout = new QGridLayout(this);
		layout->addWidget(line_edit, 0, 0);
		layout->addWidget(button, 0, 1);
		setLayout(layout);

		connect(button, &QPushButton::clicked, [this](){
			line_edit->setText(dialog->getExistingDirectory());
		});
	}

	~PathSelector() override {
		delete line_edit;
		delete button;
		delete dialog;
	}

	friend class MyApp;
};

class MyApp : public QWidget {
private:
	Blueprint* blueprint;
	LabelText* count;
	PathSelector* src, *dst;
public:
	MyApp(QWidget* parent = nullptr) : QWidget(parent) {
		blueprint = new Blueprint(this);
		this->count = new LabelText("Numero de loterias", "4", 50, this);
		this->src = new PathSelector("Entrada", this);
		this->dst = new PathSelector("Salida", this);

		auto* dialog = new QFileDialog(this);
		dialog->setFileMode(QFileDialog::Directory);
		dialog->setOption(QFileDialog::ShowDirsOnly);

		auto* button = new QPushButton("Submit", this);
		connect(button, &QPushButton::clicked, this, &MyApp::submit);
		auto* layout = new QGridLayout(this);

		layout->addWidget(count, 0, 0);

		auto* selection_layout = new QGridLayout(this);
		selection_layout->addWidget(src, 0, 0);
		selection_layout->addWidget(dst, 0, 1);

		layout->addLayout(selection_layout, 1, 0);

		layout->addWidget(blueprint, 2, 0);
		layout->addWidget(button,    3, 0);
	}

	void submit(){
		auto p = blueprint->build();
		p.insert(p.begin(), {"SetCount", {(size_t)std::stoi(count->line_edit->text().toStdString())}});
		for (auto& i : p){
			std::cout<< i.name << " ";
			for (auto& j : i.values)
				std::cout<< j << " ";
			std::cout<< std::endl;
		}
	}

	~MyApp() override {}
};

int main(int argc, char** argv) {

	QApplication app(argc, argv);

	MyApp window;

	window.resize(400, 200);
	window.setWindowTitle("Tool Tip");
	window.show();

	return app.exec();
}
