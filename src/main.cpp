#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>

class MyButton : public QWidget {
public:
	MyButton(QWidget* parent = nullptr) : QWidget(parent) {
		auto* button = new QPushButton("Button", this);
		button->setGeometry(10, 10, 100, 30);

		button->setToolTip("QPushButton");
		connect(button, &QPushButton::clicked, qApp, &QApplication::quit);
	}
};

int main(int argc, char** argv) {

	QApplication app(argc, argv);

	MyButton window;

	window.resize(250, 150);
	window.setWindowTitle("Tool Tip");
	window.setToolTip("QWidget");
	window.show();

	return app.exec();
}
