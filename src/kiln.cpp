#include "kiln.h"
#include <seriallayer.h>
#include <QTime>

Kiln::Kiln(QObject *parent) :
    QObject(parent),
    core(new AtCore(this))
{
    connect(this, &Kiln::print, core, &AtCore::print);
    connect(core, &AtCore::printProgressChanged, this, &Kiln::printProgressChanged);
}

void Kiln::setDevice(const QString &device, int baud)
{
    addLog(QStringLiteral("Connecting To:%1 baud:%2").arg(device,QString::number(baud)));
    core->initSerial(device,baud);
    connect(core->serial(), &SerialLayer::receivedCommand, this, &Kiln::checkReceivedCommand);
    connect(core->serial(), &SerialLayer::pushedCommand, this, &Kiln::checkPushedCommands);
}

void Kiln::printProgressChanged(const float &newProgress)
{
    QString text = QStringLiteral("[                    ]");
    int p = newProgress/5;
    QString indicator;
    indicator.fill(QChar::fromLatin1('#'),p);
    text.replace(1,p,indicator);
    text.append(QStringLiteral("%1\%").arg(QString::number(newProgress,'f',1)));
    addLog(text);
}

void Kiln::printFile(const QString &fileName)
{
    addLog(QStringLiteral("Printing:%1").arg(fileName));
    emit(print(fileName));
}

PrinterState Kiln::state()
{
    return core->state();
}

Kiln::~Kiln()
{

}

void Kiln::checkReceivedCommand()
{
    addRLog(QString::fromUtf8(core->serial()->popCommand()));
}

void Kiln::checkPushedCommands(QByteArray bmsg)
{
    QString msg = QString::fromUtf8(bmsg);
    QRegExp _newLine(QChar::fromLatin1('\n'));
    QRegExp _return(QChar::fromLatin1('\r'));
    msg.replace(_newLine, QStringLiteral("\\n"));
    msg.replace(_return, QStringLiteral("\\r"));
    addSLog(msg);
}

QString Kiln::getTime()
{
    return QTime::currentTime().toString(QStringLiteral("hh:mm:ss:zzz"));
}

QString Kiln::logHeader()
{
    return QStringLiteral("[%1]  ").arg(getTime());
}

QString Kiln::rLogHeader()
{
    return QStringLiteral("[%1]< ").arg(getTime());
}

QString Kiln::sLogHeader()
{
    return QStringLiteral("[%1]> ").arg(getTime());
}

void Kiln::addLog(QString msg)
{
    QString message(logHeader() + msg);
    QTextStream(stdout) << message <<endl;
}

void Kiln::addRLog(QString msg)
{
    QString message(rLogHeader() + msg);
    QTextStream(stdout) << message <<endl;
}

void Kiln::addSLog(QString msg)
{
    QString message(sLogHeader() + msg);
    QTextStream(stdout) << message <<endl;
}
