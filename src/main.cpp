#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <QTextStream>

#include "kiln.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName(QString::fromLatin1("Kiln"));
    app.setApplicationVersion(QString::fromLatin1("0.1"));

    Kiln *kiln = new Kiln;
    QString device;
    int baud=115200;
    QString fileName;

    if (argc >1) {
        for (int i=1; i < argc; i++) {
            if (QString::fromLatin1(argv[i]) == QString::fromLatin1("-d")) {
                device = QString::fromLatin1(argv[i+1]);
            } else if (QString::fromLatin1(argv[i]) == QString::fromLatin1("-b")) {
                baud = QString::fromLatin1(argv[i+1]).toInt();
            } else if (QString::fromLatin1(argv[i]) == QString::fromLatin1("-p")) {
                fileName = QString::fromLatin1(argv[i+1]);
            }
        }
    }

    if (!device.isEmpty()) {
        kiln->setDevice(device, baud);
        bool waiting = true;
        while (waiting){
            QCoreApplication::processEvents();
            if (kiln->state() == IDLE){
                waiting = false;
            }
        }
    } else {
        QTextStream(stdout) << "usage: kiln -d /dev/ttyUSB0 -p ~/file.gcode" << endl;
    }

    if(!fileName.isEmpty()) {
        kiln->printFile(fileName);
    }
}
