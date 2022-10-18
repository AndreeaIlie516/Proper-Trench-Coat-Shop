#include "GUIFile.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Repository repository{ false, "inputFile.txt" };

    GUIFile w;
    w.setWindowTitle("Proper Trench Coats");
    w.show();
    return a.exec();
}
