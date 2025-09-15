// Entry point for Calculator application without .ui (programmatic UI)
#include <QApplication>
#include "src/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w; 
    w.show();
    return app.exec();
}
