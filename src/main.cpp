#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGridLayout>

#include <board.hpp>
#include <blueprint.hpp>


class MyApp : public QWidget {
private:
	Blueprint* blueprint;
public:
	MyApp(QWidget* parent = nullptr) : QWidget(parent) {
		blueprint = new Blueprint(this);
		auto* button = new QPushButton("Submit", this);
		connect(button, &QPushButton::clicked, this, &MyApp::submit);

		auto* layout = new QGridLayout(this);
		layout->addWidget(blueprint, 0, 0);
		layout->addWidget(button, 1, 0);
	}

	void submit(){

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
