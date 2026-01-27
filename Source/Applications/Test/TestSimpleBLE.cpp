#ifdef PROJECT_USE_SIMPLEBLE
	#include <simpleble/SimpleBLE.h>
#endif
#include <iostream>
int SimpleBLEMain(int argc, char **argv)
{
#ifdef PROJECT_USE_SIMPLEBLE
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

        if (peripheral.identifier() == "zy  xiaomi  14  pro")
        {
            XiaoMi14Pro = peripheral;
            std::cout << "xiao mi 14 found" << std::endl;
        }
	}
    XiaoMi14Pro.connect();

#endif
	return 0;
}	
