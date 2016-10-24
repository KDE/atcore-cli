#include "kiln.h"

Kiln::Kiln(QObject *parent) :
    QObject(parent),
    core(new AtCore(this))
{
    connect(this,SIGNAL(done()), this->parent(), SLOT(quit()));
    connect(this, &Kiln::print, core, &AtCore::print);
    connect(core, &AtCore::printProgressChanged, this, &Kiln::printProgressChanged);
}

void Kiln::setDevice(const QString &device, int baud)
{
    core->initFirmware(device,baud);
}

void Kiln::printProgressChanged(const float &newProgress)
{
    QString text = QString::fromLatin1("[--------------------]");
    text.replace(1,(newProgress/5),QChar::fromLatin1('*'));
    QTextStream(stdout) << text << QString::number(newProgress) <<QChar::fromLatin1('%') <<endl;
}

void Kiln::printFile(const QString &fileName)
{
    emit(print(fileName));
}
Kiln::~Kiln()
{

}
