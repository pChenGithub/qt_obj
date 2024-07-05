#ifndef STFTPD_H
#define STFTPD_H
#include "sbase.h"
#include <QTcpServer>
#include <QTcpSocket>

class STftpd: public SBase
{
    Q_OBJECT
public:
    STftpd();
    ~STftpd();

    int ServerStart() override;
    int ServerStop() override;

protected slots:
    void SlotNewconnect();

private:
    // ftp参数
    QString _ip;
    quint16 _port;
    //
    QTcpServer _server;
};
#endif // STFTPD_H