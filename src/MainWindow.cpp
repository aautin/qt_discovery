#include "MainWindow.h"
#include "services/CalculatorService.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QFrame>
#include <QCloseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    service = new CalculatorService(this);
    buildUi();
    wireSignals();
}

void MainWindow::buildUi() {
	// Central widget
    central = new QWidget(this);
    setCentralWidget(central);

	// Vertical box in central widget
    auto* vbox = new QVBoxLayout();
    central->setLayout(vbox);

	// Vertical box first row: result element as a label
    display = new QLabel("", this);
    display->setFrameShape(QFrame::Panel);
    display->setFrameShadow(QFrame::Sunken);
    QFont f = display->font(); f.setPointSize(18); display->setFont(f);
    display->setMinimumHeight(50);
    display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    vbox->addWidget(display);

	// Vertical box second row: a qwidget with grid layout
    QWidget* keypad = new QWidget(this);
    grid = new QGridLayout();
    keypad->setLayout(grid);
    vbox->addWidget(keypad);

    // Configure every cell of grid as buttons
	QString buttons[] = {
		"7", "8", "9", "/", 
		"4", "5", "6", "*", 
		"1", "2", "3", "-", 
		"0", ".", "=", "+",
	};
	addButton("C", 0, 0, 1, 2);
	addButton("<<", 0, 2, 1, 2);
	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i)
		addButton(buttons[i], (i / 4) + 1, i % 4);

	// Set window title and size
    setWindowTitle("Calculator");
    resize(300,400);
}

void MainWindow::addButton(const QString& text, int row, int col, int rowSpan, int colSpan) {
    auto* btn = new QPushButton(text, this);
    grid->addWidget(btn,row,col,rowSpan,colSpan);

    // Connect directly with lambda that decides behavior
    connect(btn,&QPushButton::clicked,this,[this,text]() {
        if (text == "C") {
            service->clear();
            display->setText("");
		} else if (text == "<<") {
			service->backspace();
			display->setText(service->expression());
        } else if (text == "=") {
            QString r = service->evaluate();
            display->setText(r);
        } else {
            service->appendToken(text);
            display->setText(service->expression());
        }
    });
}

void MainWindow::wireSignals() {
    // Could connect service signals if we wanted reactive updates
    connect(service,&CalculatorService::expressionChanged,this,[this](const QString& expr){
        (void)expr;
    });
    connect(service,&CalculatorService::resultReady,this,[this](const QString& res){
        display->setText(res);
    });
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (QMessageBox::question(this, "Quitter", "Fini les calculs?") != QMessageBox::Yes) {
        event->ignore();
        return;
    }

    event->accept();
}
