#include <QApplication>
#include "myglwidget.h"

int main(int argc, char *argv[])
{
    // Creation de l'application QT
    QApplication app(argc, argv);
	
	// Creation du widget opengl
    MyGLWidget glWidget;
    glWidget.show();

    // Execution de l'application QT
    return app.exec();
}
