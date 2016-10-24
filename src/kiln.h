#pragma once

#include <QObject>
#include <QTextStream>
#include "../atcore/src/atcore.h"


class Kiln : public QObject
{
    Q_OBJECT
public:
    Kiln(QObject *parent = nullptr);
    ~Kiln();
    void setDevice(const QString &device, int baud);
    void printFile(const QString &fileName);
public slots:
    void printProgressChanged(const float &newProgress);
signals:
    /**
     * @brief print : finished kill the program.
     * @param fileName: file to print.
     */
    void print(const QString &fileName);

    /**
     * @brief done : finished kill the program.
     */
    void done();
private:
    AtCore *core;
};
