USB Device States
	Visible Device States
	Attached
	Powered
	Default
	Address
	Configured
	Suspended
Standard Device Requests
	Clear Feature
	Get Configuration
	Get Descriptor
	Get Interface
	Get Status
	Set Address
	Set Configuration
	Set Descriptor
	Set Feature
	Set Interface
	Synch Frame
Standard USB Descriptor Definitions
	Device
	Device_Qualifier
	Configuration
	Other_Speed_Configuration
	Interface
	Endpoint
	String
Control Transfers
	Control Transfer Data Format
	Control Transfer Direction
	Control Transfer Packet Size Constraints
	Control Transfer Bus Access Constraints
	Control Transfer Data Sequences
Isochronous Transfers
	Isochronous Transfer Data Format
	Isochronous Transfer Direction
	Isochronous Transfer Packet Size Constraints
	Isochronous Transfer Bus Access Constraints
	IsochronousTransfer Data Sequences
Interrupt Transfers
	Interrupt Transfer Data Format
	Interrupt Transfer Direction
	Interrupt Transfer Packet Size Constraints
	Interrupt Transfer Bus Access Constraints
	Interrupt Transfer Data Sequences
Bulk Transfers
	Bulk Transfer Data Format
	Bulk Transfer Direction
	Bulk Transfer Packet Size Constraints
	Bulk Transfer Bus Access Constraints
	Bulk Transfer Data Sequences
USB接口的速度标准根据不同版本有显著差异，从USB1.0的1.5 Mbps到USB 4的40Gbps不等。
各版本USB速度标准
1. USB 1.0:
·低速(Low Speed)：理论最高速率为 1.5 Mbit/s (0.1875 MBytes/s)。
·全速(Full Speed)：理论最高速率为 12 Mbit/s(1.5 MBytes/s)。
2. USB 2.0:
·高速(High Speed)：理论最高速率为 480 Mbit/s (60 MBytes/s)。
3. USB 3.0:
·超速(Super Speed)：理论最高速率为 5 Gbit/s (600 MBytes/s)。
4. USB 3.1:
·Gen 1: 理论最高速率为 5 Gbit/s (600 MBytes/s)。
·Gen 2: 理论最高速率为 10 Gbit/s(1250 MBytes/s)。
5. USB 3.2:
·Gen 1: 理论最高速率为 5 Gbit/s(600 MBytes/s)。
·Gen 2: 理论最高速率为 10 Gbit/s(1250 MBytes/s)。
·Gen 2x2: 理论最高速率为20 Gbit/s(2500 MBytes/s)，仅限Type-C接口。
6. USB 4:
·理论最高速率为40 Gbit/s(5000 MBytes/s)，仅限Type-C接口。
Base Class     Descriptor Usage       Description
00h            Device                 Use class information in the Interface Descriptors
01h            Interface              Audio
02h            Both                   Communications and CDC Control
03h            Interface              HID (Human Interface Device)
05h            Interface              Physical
06h            Interface              Image
07h            Interface              Printer
08h            Interface              Mass Storage
09h            Device                 Hub
0Ah            Interface              CDC-Data
0Bh            Interface              Smart Card
0Dh            Interface              Content Security
0Eh            Interface              Video        
0Fh            Interface              Personal Healthcare
10h            Interface              Audio/Video Devices
11h            Device                 Billboard Device Class
12h            Interface              USB Type-C Bridge Class
13h            Interface              USB Bulk Display Protocol Device Class
14h            Interface              MCTP over USB Protocol Endpoint Device Class
3Ch            Interface              I3C Device Class
DCh            Both                   Diagnostic Device
E0h            Interface              Wireless Controller
EFh            Both                   Miscellaneous
FEh            Interface              Application Specific
FFh            Both                   Vendor Specific
Base Class 00h (Device)
	Base Class     SubClass     Protocol         Meaning
	00h            00h          00h              Use class code info from Interface Descriptors
Base Class 01h (Audio)
	Base Class     SubClass     Protocol         Meaning
	01h            xxh          xxh              Audio device
Base Class 02h (Communications and CDC Control)
	Base Class     SubClass     Protocol         Meaning
	02h            xxh          xxh              Communication device class
Base Class 03h (HID – Human Interface Device)
	Base Class     SubClass     Protocol         Meaning
	03h            xxh          xxh              HID device class
Base Class 05h (Physical)
	Base Class     SubClass     Protocol         Meaning
	05h            xxh          xxh              Physical device class
Base Class 06h (Still Imaging)
	Base Class     SubClass     Protocol         Meaning
	06h            01h          01h              Still Imaging device
Base Class 07h (Printer)
	Base Class     SubClass     Protocol         Meaning
	07h            xxh          xxh              Printer device
Base Class 08h (Mass Storage)
	Base Class     SubClass     Protocol         Meaning
	08h            xxh          xxh              Mass Storage device
Base Class 09h (Hub)
	Base Class     SubClass     Protocol         Meaning
	09h            00h          00h              Full speed Hub
								01h              Hi-speed hub with single TT
								02h              Hi-speed hub with multiple TTs
Base Class 0Ah (CDC-Data)
	Base Class     SubClass     Protocol         Meaning
	0Ah            xxh          xxh              CDC data device
Base Class 0Bh (Smart Card)
	Base Class     SubClass     Protocol         Meaning
	0Bh            xxh          xxh              Smart Card device
Base Class 0Dh (Content Security)
	Base Class     SubClass     Protocol         Meaning
	0Dh            00h          00h              Content Security device
Base Class 0Eh (Video)
	Base Class     SubClass     Protocol         Meaning
	0Eh            xxh          xxh              Video device
Base Class 0Fh (Personal Healthcare)
	Base Class     SubClass     Protocol         Meaning
	0Fh            xxh          xxh              Personal Healthcare device
Base Class 10h (Audio/Video Devices)
	Base Class     SubClass     Protocol         Meaning
	10h            01h          00h              Audio/Video Device – AVControl Interface
				   02h          00h              Audio/Video Device – AVData Video Streaming Interface
				   03h          00h              Audio/Video Device – AVData Audio Streaming Interface
Base Class 11h (Billboard Device)
	Base Class     SubClass     Protocol         Meaning
	11h            00h          00h              Billboard Device
Base Class 12h (USB Type-C Bridge Device)
	Base Class     SubClass     Protocol         Meaning
	12h            00h          00h              USB Type-C Bridge Device
Base Class 13h (USB Bulk Display Protocol Device Class)
	Base Class     SubClass     Protocol         Meaning
	13h            00h          00h              USB BDP Device
Base Class 14h (MCTP over USB Protocol Endpoint Device Class)
	Base Class     SubClass     Protocol         Meaning
	14h            00h          01h: MCTP 1.x    MCTP Management-controller and Managed-Device endpoints
								02h: MCTP 2.x
				   01h          01h: MCTP 1.x    MCTP Host Interface endpoint
								02h: MCTP 2.x
Base Class 3Ch (I3C Device Class)
	Base Class     SubClass     Protocol     Meaning
	3Ch            00h          00h          I3C Device
Base Class DCh (Diagnostic Device)
	Base Class    SubClass     Protocol       Meaning
	DCh           01h          01h            USB2 Compliance Device. Definition for this device can be found at http://www.intel.com/technology/usb/spec.htm	                                  
				  02h          00h            Debug Target vendor defined. Please see http://www.intel.com/content/www/us/en/io/universal-serial-bus/extensible-host-controler-interface-usb-xhci.html for more info.	
							   01h            GNU Remote Debug Command Set. Please see http://www.intel.com/content/www/us/en/io/universal-serial-bus/extensible-host-controler-interface-usb-xhci.html for more info.
				  03h          00h            Undefined
							   01h            Vendor defined Trace protocol on DbC.
				  04h          00h            Undefined
							   01h            Vendor defined Dfx protocol on DbC.
				  05h          00h            Vendor defined Trace protocol over General Purpose (GP) endpoint on DvC.
							   01h            GNU Protocol protocol over General Purpose (GP) endpoint on DvC.http://www.gnu.org/software/gdb/
				  06h          00h            Undefined
							   01h            Vendor defined Dfx protocol on DvC.
				  07h		   00h            Undefined
							   01h            Vendor defined Trace protocol on DvC.
				  08h          00h            Undefined
Base Class E0h (Wireless Controller)
	Base Class    SubClass     Protocol       Meaning
	E0h           01h          01h            Bluetooth Programming Interface. Get specific information from www.bluetooth.com.
							   02h            UWB Radio Control Interface. Definition for this is found in the Wireless USB Specification in Chapter 8.
							   03h            Remote NDIS. Information can be found at: http://www.microsoft.com/windowsmobile/mobileoperators/default.mspx
							   04h            Bluetooth AMP Controller. Get specific information from www.bluetooth.com.
				  2h		   01h            Host Wire Adapter Control/Data interface. Definition can be found in the Wireless USB Specification in Chapter 8.
							   02h            Device Wire Adapter Control/Data interface. Definition can be found in the Wireless USB Specification in Chapter 8.
							   03h            Device Wire Adapter Isochronous interface. Definition can be found in the Wireless USB Specification in Chapter 8.
Base Class EFh (Miscellaneous)					   
	Base Class    SubClass     Protocol       Meaning
	EFh           01h		   01h			  Active Sync device. This class code can be used in either Device or Interface Descriptors. Contact Microsoft for more information on this class. 
							   02h            Palm Sync. This class code can be used in either Device or Interface Descriptors.
				  02h		   01h            Interface Association Descriptor. The usage of this class code triple is defined in the Interface Association Descriptor ECN that is provided on www.usb.org . This class code may only be used in Device Descriptors.
							   02h            Wire Adapter Multifunction Peripheral programming interface. Definition can be found in the Wireless USB Specification in Chapter 8. This class code may only be used in Device Descriptors
				  03h          01h	          Cable Based Association Framework. This is defined in the Association Model addendum to the Wireless USB specification. This class code may only be used in Interface Descriptors.
				  04h		   01h            RNDIS over Ethernet.Connecting a host to the Internet via Ethernet mobile device. The device appears to the host as an Ethernet gateway device.This class code may only be used in Interface Descriptors.
							   02h            RNDIS over WiFi.Connecting a host to the Internet via WiFi enabled mobile device. The device represents itself to the host as an 802.11 compliant network device.This class code may only be used in Interface Descriptors.
							   03h            RNDIS over WiMAX.Connecting a host to the Internet via WiMAX enabled mobile device. The device is represented to the host as an 802.16 network device.This class code may only be used in Interface Descriptors.
							   04h            RNDIS over WWAN.Connecting a host to the Internet via a device using mobile broadband, i.e. WWAN (GSM/CDMA).This class code may only be used in Interface Descriptors.
							   05h            RNDIS for Raw IPv4.Connecting a host to the Internet using raw IPv4 via non-Ethernet mobile device. Devices that provide raw IPv4, not in an Ethernet packet, may use this form to in lieu of other stock types.This class code may only be used in Interface Descriptors.
							   06h            RNDIS for Raw IPv6.Connecting a host to the Internet using raw IPv6 via non-Ethernet mobile device. Devices that provide raw IPv6, not in an Ethernet packet, may use this form to in lieu of other stock types.This class code may only be used in Interface Descriptors.
							   07h            RNDIS for GPRS.Connecting a host to the Internet over GPRS mobile device using the device’s cellular radio
				  05h		   00h            USB3 Vision        Machine Vision Device conforming to the USB3 Vision specification. This standard covers cameras and other related devices that are typically used in machine vision, industrial, and embedded applications.
											  Control Interface
							   01h            USB3 Vision        Reference: http://visiononline.org/
											  Event Interface
							   02h            USB3 Vision        This class code may only be used in Interface Descriptors.
											  Streaming
											  Interface
				  06h		   01h            STEP. Stream Transport Efficient Protocol for content protection.
							   02h            STEP RAW. Stream Transport Efficient Protocol for Raw content protection.
				  07h		   01h            Command            The DVB Common Interface (DVB-CI) specification describes a system 
											  Interface in IAD   whereby a removable CI Conditional Access Module (CICAM), given the appropriate usage rights, unscrambles protected pay-TV content and routes it
							   01h            Command            over the same interface back to a TV receiver for display. An interface
											  Interface in       association for a DVB-CI function will contain a DVB-CI Command Interface for
											  Interface          command, control, and status information, it may contain a DVB-CI Media
											  Descriptor         Interface for audiovisual data streams, and it may also contain a CDC EEM interface to provide bridged networking to the CICAM.
				  08h		   01h            OCP Secure         Opencompute.org (OCP) Secure Firmware Recovery defines common
											  Firmware           Recovery framework for Datacenter operation. It defines how to recover a
											  Recovery           failed or compromised Device. The recovery operation provides a mechanism
																 for a recovery agent (RA), in coordination with a PA-RoT (Platform Active RoT),
																 to recover a Device's firmware and/or security critical parameters of an AC-RoT (Active Component RoT).
																 Reference: https://www.opencompute.org/documents/ocp-recovery-document-1p0-final-1-pdf
																 This class code may only be used in Interface Descriptors.
				  09h		   01h			  OCP OBMF-ICP		 Opencompute.org (OCP) Open Boot and Management Framework (OBMF)
																 Interface Consolidation Protocol (OBMF-ICP) enables aggregation of multiple
																 legacy interfaces like TPM, I2C, GPIO, SSIF, SPI and other interfaces over a
																 single USB Interface for Datacenter operation. In a typical Server SoC, the
																 number of NICs, GPU supported is large and easily exceeds number of
																 available endpoints on single USB device. OBMF-ICP provides up to 255
																 separate channels with runtime discoverability of supported channels over
																 OBFM-ICP to enable runtime binding to different vendors equipment via
																 generic USB protocol
																 Reference:https://github.com/opencomputeproject/ocp-obmf/wiki#published-documents 
																 https://www.opencompute.org/documents
																 This class code may only be used in Interface Descriptors.
Base Class FEh (Application Specific)
	Base Class     SubClass     Protocol         Meaning
	FEh            01h          01h              Device Firmware Upgrade. Device class definition provided on www.usb.org .
				   02h          00h              IRDA Bridge device. Device class definition provided on www.usb.org .
				   03h          00h              USB Test and Measurement Device. Definition provided in the USB Test and
												 Measurement Class spec found on www.usb.org .
								01h				 USB Test and Measurement Device conforming to the USBTMC USB488 Subclass
												 Specification found on www.usb.org.
Base Class FFh (Vendor Specific)
	Base Class     SubClass     Protocol         Meaning
	FFh			   xxh			xxh				 Vendor specific