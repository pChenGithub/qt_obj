#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "base/tcpIp/multicast.h"
#include "protocol/device_prot.h"
// 扫描设备
int scanDevice(const char* ifIp, handMulticastRsp cb);
// 更新设备应用程序
int updateDevice(const char* file, DEVICE_BASE_INFO *dinfo);
// 获取日志
int getDevlog(const char* path, DEVICE_BASE_INFO *dinfo);
// 重启设备
int devReboot(DEVICE_BASE_INFO *dinfo);
// 升级服务
int upServer(const char *file, DEVICE_BASE_INFO* dinfo);

#ifdef __cplusplus
}
#endif

