#ifdef PROJECT_USE_BLUEZ
    #include <bluetooth/bluetooth.h>
    #include <bluetooth/hci.h>
    #include <bluetooth/hci_lib.h>
#endif
#include  <iostream>
void TestBluetooth()
{
#ifdef PROJECT_USE_BLUEZ
    int dev_id = hci_get_route(NULL);
    std::cout << dev_id << std::endl;
#endif
}