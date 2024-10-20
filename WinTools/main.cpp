#include "mainwindow.h"
#include "mainwindow2.h"
#include "base/tcpIp/multicast.h"
#include "base/core/task_core.h"
#include <stdio.h>
#include <QApplication>
#include <QTextCodec>
#include "servers/serversmanager.h"
#include "servers/telnet/telnetsv.h"

TASK_ENTRY* task_entry = NULL;

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    setbuf(stdout, NULL);
    printf("build time %s\n", __TIME__);
    QApplication a(argc, argv);
#if 0
    MainWindow w;
    w.itent = &w;
#else
    MainWindow2 w;
#endif
    int ret = start_task_core(&task_entry, 2);
    if (ret<0) {
        printf("start task core errro, ret %d\n", ret);
    }
    w.show();

    //
    ServersManager* sm = new ServersManager;
    sm->StartServer("STftpd");

    return a.exec();
}
