#ifdef PROJECT_USE_BLUEZ
    // scan_devices.c
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <errno.h>
    #include <string.h>
    #include <signal.h>

    #include <bluetooth/bluetooth.h>
    #include <bluetooth/hci.h>
    #include <bluetooth/hci_lib.h>


#include <iostream>


int BluezMain(int argc, char **argv) {
    std::cout << "bluez " << std::endl;
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    printf("=== Bluetooth Device Scanner ===\n");

    // 获取第一个可用的蓝牙适配器
    dev_id = hci_get_route(NULL);
    if (dev_id < 0) {
        fprintf(stderr, "No Bluetooth adapter found\n");
        return 1;
    }

    printf("Using adapter: hci%d\n", dev_id);

    // 打开HCI socket
    sock = hci_open_dev(dev_id);
    if (sock < 0) {
        perror("Failed to open HCI socket");
        return 1;
    }

    // 设置扫描参数
    len = 8;           // 扫描时长 (1.28秒 * len)
    max_rsp = 255;     // 最大响应设备数
    flags = IREQ_CACHE_FLUSH;  // 清除缓存重新扫描
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    if (!ii) {
        perror("Memory allocation failed");
        close(sock);
        return 1;
    }

    // 开始扫描
    printf("\nScanning for %d seconds...\n", len * 1280 / 1000);
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);

    if (num_rsp < 0) {
        perror("Inquiry failed");
        free(ii);
        close(sock);
        return 1;
    }

    printf("\nFound %d device(s):\n", num_rsp);
    printf("========================================\n");

    // 显示每个设备的信息
    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));

        // 尝试获取设备名称
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr,
                                 sizeof(name), name, 0) < 0) {
            strcpy(name, "[unknown]");
        }

        printf("Device %d:\n", i + 1);
        printf("  MAC Address:  %s\n", addr);
        printf("  Name:         %s\n", name);

        // 正确获取设备类：dev_class 是 uint8_t[3]
        uint8_t *dev_class = (ii+i)->dev_class;
        printf("  Device Class: 0x%02x%02x%02x\n",
               dev_class[0], dev_class[1], dev_class[2]);

        // 将3字节数组转换为32位整数用于解码
        uint32_t class1 = (dev_class[0] << 16) | (dev_class[1] << 8) | dev_class[2];

        // 解码主要设备类型
        printf("  Major Class:  ");
        uint8_t major_class = (class1 >> 16) & 0x1F;
        switch(major_class) {
            case 0x00: printf("Miscellaneous\n"); break;
            case 0x01: printf("Computer (desktop, notebook, PDA, organizer)\n"); break;
            case 0x02: printf("Phone (cellular, cordless, pay phone, modem)\n"); break;
            case 0x03: printf("LAN/Network Access Point\n"); break;
            case 0x04: printf("Audio/Video (headset, speaker, stereo, video display)\n"); break;
            case 0x05: printf("Peripheral (mouse, joystick, keyboard)\n"); break;
            case 0x06: printf("Imaging (printer, scanner, camera, display)\n"); break;
            case 0x07: printf("Wearable (watch, pager, glasses)\n"); break;
            case 0x08: printf("Toy\n"); break;
            case 0x09: printf("Health (blood pressure monitor, thermometer)\n"); break;
            case 0x1F: printf("Uncategorized\n"); break;
            default: printf("Unknown (0x%02x)\n", major_class);
        }

        // 解码次要设备类型
        printf("  Minor Class:  ");
        uint8_t minor_class = (class1 >> 8) & 0x3F;
        switch(major_class) {
            case 0x01:  // Computer
                switch(minor_class & 0x0F) {
                    case 0x00: printf("Uncategorized\n"); break;
                    case 0x01: printf("Desktop workstation\n"); break;
                    case 0x02: printf("Server-class computer\n"); break;
                    case 0x03: printf("Laptop\n"); break;
                    case 0x04: printf("Handheld PC/PDA (clam shell)\n"); break;
                    case 0x05: printf("Palm sized PC/PDA\n"); break;
                    case 0x06: printf("Wearable computer (watch)\n"); break;
                    case 0x07: printf("Tablet\n"); break;
                    default: printf("Unknown computer (0x%02x)\n", minor_class);
                }
                break;

            case 0x04:  // Audio/Video
                switch(minor_class & 0x0F) {
                    case 0x00: printf("Uncategorized\n"); break;
                    case 0x01: printf("Wearable headset device\n"); break;
                    case 0x02: printf("Hands-free device\n"); break;
                    case 0x04: printf("Microphone\n"); break;
                    case 0x05: printf("Loudspeaker\n"); break;
                    case 0x06: printf("Headphones\n"); break;
                    case 0x07: printf("Portable audio\n"); break;
                    case 0x08: printf("Car audio\n"); break;
                    case 0x09: printf("Set-top box\n"); break;
                    case 0x0A: printf("HiFi audio device\n"); break;
                    case 0x0B: printf("VCR\n"); break;
                    case 0x0C: printf("Video camera\n"); break;
                    case 0x0D: printf("Camcorder\n"); break;
                    case 0x0E: printf("Video monitor\n"); break;
                    case 0x0F: printf("Video display and loudspeaker\n"); break;
                    default: printf("Unknown A/V device (0x%02x)\n", minor_class);
                }
                break;

            default:
                printf("0x%02x\n", minor_class);
        }

        // 解码服务类
        printf("  Service Class: 0x%02x%02x%02x\n",
               dev_class[0], dev_class[1], dev_class[2]);

        // 解析服务类位
        uint32_t service_class = (dev_class[0] << 16) | (dev_class[1] << 8) | dev_class[2];
        printf("    Services: ");
        if (service_class & 0x020000) printf("LimitedDiscoverableMode ");
        if (service_class & 0x000200) printf("Positioning ");
        if (service_class & 0x000100) printf("Networking ");
        if (service_class & 0x000080) printf("Rendering ");
        if (service_class & 0x000040) printf("Capturing ");
        if (service_class & 0x000020) printf("ObjectTransfer ");
        if (service_class & 0x000010) printf("Audio ");
        if (service_class & 0x000008) printf("Telephony ");
        if (service_class & 0x000004) printf("Information ");
        printf("\n");

        printf("\n");
    }

    // 清理资源
    free(ii);
    close(sock);

    printf("Scan completed.\n");
    return 0;
}
#endif