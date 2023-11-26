#include <stdio.h>
#include <NetworkManager.h>

int main()
{
    NMDeviceWifi *wifi;
    const GPtrArray *aps;
    int i;
    NMAccessPoint *ap;
    char ssid[16];
    const char *bssid;
    guint8 strength;

    // 获取WiFi设备列表
    const GPtrArray *devices = nm_client_get_devices(nm_client_new(NULL, NULL));

    // 遍历设备列表，找到已开启的WiFi热点设备
    for (i = 0; i < devices->len; i++)
    {
        NMDevice *device = g_ptr_array_index(devices, i);
        if (nm_device_get_device_type(device) == NM_DEVICE_TYPE_WIFI && nm_device_get_state(device) == NM_DEVICE_STATE_ACTIVATED)
        {
            wifi = NM_DEVICE_WIFI(device);
            break;
        }
    }

    if (!wifi)
    {
        printf("未找到已开启的WiFi热点设备\n");
        return 1;
    }

    // 获取接入点列表
    aps = nm_device_wifi_get_access_points(wifi);

    for (i = 0; i < aps->len; i++)
    {
        ap = g_ptr_array_index(aps, i);
        GByteArray *arr = g_bytes_unref_to_array(nm_access_point_get_ssid(ap));
        memcpy(ssid, arr->data, arr->len);

        bssid = nm_access_point_get_bssid(ap);
        strength = nm_access_point_get_strength(ap);
        printf("SSID: %s\n", ssid);         // 打印SSID（可选）
        printf("BSSID: %s\n", bssid);       // 打印MAC地址
        printf("信号强度: %d\n", strength); // 打印信号强度（可选）
    }

    return 0;
}