#include "kiln.h"

Kiln::Kiln(QObject *parent) :
    QObject(parent),
    core(new AtCore(this))
{
    connect(this,SIGNAL(done()), this->parent(), SLOT(quit()));
    connect(this, &Kiln::print, core, &AtCore::print);
}

void Kiln::setDevice(const QString &device, int baud)
{

    core->initFirmware(device,baud);
}


void Kiln::printFile(const QString &fileName)
{
    emit(print(fileName));
}
Kiln::~Kiln()
{

}
