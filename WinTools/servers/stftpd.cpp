#include "stftpd.h"
#include "cftp.h"

STftpd::STftpd()
{
    qDebug() << "create STftpd";
    // ftp默认端口是21
    _port = 21;
    // 监听服务状态
    connect(&_server, SIGNAL(newConnection()), this, SLOT(SlotNewconnect()));
}

STftpd::~STftpd()
{
    disconnect(&_server, SIGNAL(newConnection()), this, SLOT(SlotNewconnect()));
}

int STftpd::ServerStart()
{
    _server.listen(QHostAddress::AnyIPv4, _port);
}

int STftpd::ServerStop()
{

}

void STftpd::SlotNewconnect()
{
    // 对于新的连接，获取socket，然后加入监听
    QTcpSocket* sck = _server.nextPendingConnection();
    qDebug() << "a new ftp connect";
    new Cftp(sck);
}
