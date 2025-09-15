#pragma once
#include <QMainWindow>
class QLabel;
class QPushButton;
class QGridLayout;
class CalculatorService;

class MainWindow : public QMainWindow {
    Q_OBJECT

	public:
		explicit MainWindow(QWidget* parent = nullptr);

	protected:
		void closeEvent(QCloseEvent* event) override;
	
	private:
		void buildUi();
		void wireSignals();
		void addButton(const QString& text, int row, int col, int rowSpan=1, int colSpan=1);

		QWidget* central;
		QLabel* display;
		QGridLayout* grid;
		CalculatorService* service;
};
