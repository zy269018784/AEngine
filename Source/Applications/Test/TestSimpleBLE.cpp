#if  PROJECT_USE_SIMPLEBLE
	#include <simpleble/SimpleBLE.h>
#endif
#include <iostream>
int SimpleBLEMain(int argc, char **argv)
{
#if  PROJECT_USE_SIMPLEBLE
	std::cout << "SimpleBLE" << std::endl;
   if (!SimpleBLE::Adapter::bluetooth_enabled()) {
      std::cout << "Bluetooth is not enabled" << std::endl;
      return 1;
   }

   auto adapters = SimpleBLE::Adapter::get_adapters();
   if (adapters.empty()) {
      std::cout << "No Bluetooth adapters found" << std::endl;
      return 1;
   }

   // Use the first adapter
   auto adapter = adapters[0];

   // Do something with the adapter
   std::cout << "Adapter identifier: " << adapter.identifier() << std::endl;
   std::cout << "Adapter address: " << adapter.address() << std::endl;

   // Scan for peripherals for 5000 milliseconds
	adapter.scan_for(15000);

	// Get the list of peripherals found
	std::vector<SimpleBLE::Peripheral> peripherals = adapter.scan_get_results();

    SimpleBLE::Peripheral XiaoMi14Pro;
	// Print the identifier of each peripheral
	for (auto peripheral : peripherals) {
	    std::cout << "Peripheral identifier: " << peripheral.identifier() << " "
	              << "Peripheral address: " << peripheral.address()  << " "
                  << std::endl;

       // if (peripheral.identifier() == "zy  xiaomi  14  pro")
       //if (peripheral.identifier() == "MatePad Pro")
       if (peripheral.identifier() == "TRANYOO-i4")
        {
            XiaoMi14Pro = peripheral;
            std::cout << "xiao mi 14 found" << std::endl;
        }
	}
    if (XiaoMi14Pro.initialized()) {
        std::cout << "is_connectable " << XiaoMi14Pro.is_connectable() << std::endl;
        std::cout << "is_paired " << XiaoMi14Pro.is_paired() << std::endl;
        if (XiaoMi14Pro.is_paired())
        {
            XiaoMi14Pro.unpair();
            std::cout << "is_paired " << XiaoMi14Pro.is_paired() << std::endl;
        }
        std::cout << "is_connected " << XiaoMi14Pro.is_connected() << std::endl;
        XiaoMi14Pro.connect();
        std::cout << "is_paired " << XiaoMi14Pro.is_paired() << std::endl;
        std::cout << "is_connected " << XiaoMi14Pro.is_connected() << std::endl;

        if (XiaoMi14Pro.is_connected()) {
            std::cout << "services " << XiaoMi14Pro.services().size() << std::endl;
            for (int ServiceIndex = 0; ServiceIndex < XiaoMi14Pro.services().size(); ServiceIndex++) {
                SimpleBLE::Service &Service = XiaoMi14Pro.services()[ServiceIndex];
                int CharacteristicsCount = Service.characteristics().size();
                for (int CharacteristicsIndex = 0;
                     CharacteristicsIndex < CharacteristicsCount; CharacteristicsIndex++) {
                    SimpleBLE::Characteristic &Characteristic = Service.characteristics()[CharacteristicsIndex];
                    int DescriptorCount = Characteristic.descriptors().size();
                    for (int DescriptorIndex = 0; DescriptorIndex < DescriptorCount; DescriptorIndex++) {
                        SimpleBLE::Descriptor &Descriptor = Characteristic.descriptors()[DescriptorIndex];
                        std::cout << "Descriptor.uuid " << Descriptor.uuid() << std::endl;
                    }
                }
            }
        }

        if (XiaoMi14Pro.is_connected())
        {
            XiaoMi14Pro.disconnect();
            std::cout << "is_connected " << XiaoMi14Pro.is_connected() << std::endl;
        }
    }
    else
    {
        std::cout << "initialized " << XiaoMi14Pro.initialized() << std::endl;
    }
#endif
	return 0;
}	
