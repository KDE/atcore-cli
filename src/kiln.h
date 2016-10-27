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
    PrinterState state();
public slots:
    void printProgressChanged(const float &newProgress);
    /**
     * @brief Check received messages
     *
     */
    void checkReceivedCommand();

    /**
     * @brief Check pushed message
     *
     * @param  bmsg : Message
     */
    void checkPushedCommands(QByteArray);
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

    /**
     * @brief Normal header
     *
     * @return QString
     */
    QString logHeader();

    /**
     * @brief Return string with actual time
     *
     * @return QString
     */
    QString getTime();

    /**
     * @brief Header of type received
     *
     * @return QString
     */
    QString rLogHeader();

    /**
     * @brief Header of type send
     *
     * @return QString
     */
    QString sLogHeader();

    /**
     * @brief Add in logger normal type message
     *
     * @param  msg: Message
     */
    void addLog(QString msg);

    /**
     * @brief Add in logger received type message
     *
     * @param  msg: Message
     */
    void addRLog(QString msg);

    /**
     * @brief Add in logger send type message
     *
     * @param  msg: Message
     */
    void addSLog(QString msg);
};
