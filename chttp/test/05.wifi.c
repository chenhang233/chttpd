#include <glib.h>
#include <stdio.h>
#include <NetworkManager.h>

int main(int argc, char *argv[])
{
    NMClient *client;
    NMDevice *device;
    const GPtrArray *devices;
    int i;
    // 创建NMClient实例
    client = nm_client_new(NULL, NULL);

    // 获取所有设备列表
    devices = nm_client_get_devices(client);

    // 遍历设备列表，查找WiFi网卡
    for (i = 0; i < devices->len; i++)
    {
        device = g_ptr_array_index(devices, i);
        if (nm_device_get_device_type(device) == NM_DEVICE_TYPE_WIFI &&
            nm_device_get_state(device) == NM_DEVICE_STATE_ACTIVATED)
        {

            // 打印WiFi网卡信息
            printf("当前WiFi网卡：%s\n", nm_device_get_iface(device));
            printf("当前WiFi driver：%s\n", nm_device_get_driver(device));
            printf("当前WiFi software %d\n", nm_device_is_software(device));

            break;
        }
    }
    // 释放资源
    g_object_unref(client);

    return 0;
}