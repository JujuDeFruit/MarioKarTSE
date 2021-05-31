#include <QApplication>
#include "Widget.h"

#include <QDateTime>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QThread>
#include <QTextStream>
#include <iostream>

QUrl logFileUrl("../mario-kartse/logger.log");
bool logToFile=true;
int appLogLevel=3;

void logger(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    bool writeLogLine = false;
    QString line;
    QString msgType;
    QString time = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz");
    switch (type) {
    case QtInfoMsg:{
        msgType = "Info";
        break;
    }
    case QtDebugMsg:{
        msgType = "Debug";
        break;
    }
    case QtWarningMsg:{
        msgType = "Warning";
        break;
    }
    case QtCriticalMsg:{
        msgType = "Critical";
        break;
    }
    case QtFatalMsg:{
        msgType = "Fatal";
        abort();
    }
    }
    line = QString("[%1] <%2> %3 (%4) | %5:%6 (%7) '%8'")
            .arg(time)
            .arg(static_cast<int>(reinterpret_cast<intptr_t>(QThread::currentThreadId())))
            .arg(msgType)
            .arg(context.category)
            .arg(context.file)
            .arg(context.line)
            .arg(context.function)
            .arg(msg);
    if (!logToFile){
        writeLogLine = false;
        std::cout << line.toStdString() << std::endl;
    } else {
        switch (appLogLevel){
        case 0:{
            writeLogLine = false;
            break;
        }
        case 1:{
            if (type == QtFatalMsg)
                writeLogLine = true;
            break;
        }
        case 2:{
            if (type == QtCriticalMsg || type == QtFatalMsg)
                writeLogLine = true;
            break;
        }
        case 3:{
            if (type != QtInfoMsg && type != QtDebugMsg)
                writeLogLine = true;
            break;
        }
        case 4:{
            if (type != QtDebugMsg)
                writeLogLine = true;
            break;
        }
        case 5:{
            writeLogLine = true;
            break;
        }
        }
    }
    if (writeLogLine){
        QFile logFile(logFileUrl.toLocalFile());
        if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream ts(&logFile);
            ts << line << Qt::endl;
            logFile.close();
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("WARNING");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText(logFile.errorString());
            msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
            msgBox.exec();
        }
    }
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(logger);
    /* QT App */
    QApplication app(argc, argv);
	
    /* OpenGL Widget */
    MKWidget glWidget;
    glWidget.show();

    /* QT App execution */
    return app.exec();
}
