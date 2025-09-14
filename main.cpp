#include <QApplication>
#include <QPushButton>
#include <QMessageBox>

#include <QObject>

void onButtonClicked(QApplication *app) {
    qInfo("Button was clicked!");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Info", "Button clicked, application will close.",
                                    QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
        app->quit();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Close Application");
    button.resize(200, 100);
    QObject::connect(&button, &QPushButton::clicked, [&app]() { onButtonClicked(&app); });
    button.show();

    return app.exec();
}
