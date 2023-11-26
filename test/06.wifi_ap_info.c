#include <NetworkManager.h>
#include <stdio.h>
#include <libnm_glib.h>

int main()
{
    NMClient *client;
    NMAccessPoint *ap;
    const GPtrArray *aps;
    int i;

    // 创建NMClient实例
    client = nm_client_new(NULL, NULL);

    // 获取当前已连接的WiFi设备列表
    aps = nm_client_get_access_points(client);
    nm_client_get_all_devices
        // 遍历设备列表，查找已连接的WiFi AP设备
        for (i = 0; i < aps->len; i++)
    {
        ap = g_ptr_array_index(aps, i);
        if (nm_ap_get_strength(ap) > 0)
        {
            // 打印已连接的WiFi AP设备信息
            printf("已连接的WiFi AP：\n");
            printf("SSID：%s\n", nm_ap_get_ssid(ap));
            printf("BSSID：%s\n", nm_ap_get_bssid(ap));
            printf("信号强度：%d\n", nm_ap_get_strength(ap));
            break;
        }
    }

    // 释放资源
    g_object_unref(client);

    return 0;
}