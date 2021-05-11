#include <QApplication>
#include "Widget.h"

int main(int argc, char *argv[])
{
    /* QT App */
    QApplication app(argc, argv);
	
    /* OpenGL Widget */
    MKWidget glWidget;
    glWidget.show();

    /* QT App execution */
    return app.exec();
}
