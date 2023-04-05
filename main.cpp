
#include <QApplication>
#include <QMainWindow>
#include "tableau.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    tableau *tableauWidget = new tableau(&mainWindow);
    mainWindow.setCentralWidget(tableauWidget);
    mainWindow.setWindowTitle("Tableau de Labels");
    mainWindow.show();

    return app.exec();
}
