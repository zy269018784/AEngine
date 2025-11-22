/*
	1. v4.6.0 API
		1.1		SDK版本信息
			GetSDKVersion 
		1.2		SDK初始化
			MV_CC_Initialize 
			MV_CC_Finalize
		1.3		相机初始化
			MV_CC_EnumDevices
			MV_CC_EnumDevicesByInterface
			MV_CC_IsDeviceAccessible
			MV_CC_CreateHandle
			MV_CC_IsDeviceConnected
			MV_CC_OpenDevice
			MV_CC_GetAllMatchInfo
			MV_CC_GetDeviceInfo
			MV_CC_CloseDevice
			MV_CC_DestroyHandle
		1.4		采集卡初始化
			MV_CC_EnumInterfaces
			MV_CC_CreateInterface
			MV_CC_CreateInterfaceByID
			MV_CC_OpenInterface
			MV_CC_CloseInterface
			MV_CC_DestroyInterface
		1.5		参数设置
		1.6		图像采集
			MV_CC_StartGrabbing	开始采集图像流
			MV_CC_StopGrabbing
			MV_CC_GetImageBuffer
			MV_CC_FreeImageBuffer
			MV_CC_ClearImageBuffer
			MV_CC_SetGrabStrategy
			MV_CC_SetOutputQueueSize
			MV_CC_RegisterImageCallBackEx
			MV_CC_RegisterImageCallBackEx2
		1.7		图像渲染
		1.8		图像处理
			MV_CC_SaveImageEx3
			MV_CC_SaveImageToFileEx
			MV_CC_SaveImageToFileEx2
			MV_CC_RotateImage
			MV_CC_FlipImage
			MV_CC_ConvertPixelTypeEx
			MV_CC_SetBayerCvtQuality
			MV_CC_SetBayerFilterEnable
			MV_CC_SetBayerGammaValue
			MV_CC_SetGammaValue
			MV_CC_SetBayerGammaParam
			MV_CC_SetBayerCCMParam
			MV_CC_SetBayerCCMParamEx
			MV_CC_ImageContrast
			MV_CC_PurpleFringing
			MV_CC_SetISPConfig
			MV_CC_ISPProcess
			MV_CC_HB_Decode
			MV_CC_StartRecord
			MV_CC_InputOneFrame
			MV_CC_StopRecord
			MV_CC_ReconstructImage
		1.9		事件及异常
			MV_CC_RegisterExceptionCallBack 
			MV_CC_RegisterAllEventCallBack
			MV_CC_RegisterEventCallBackEx
			MV_CC_EventNotificationOn
			MV_CC_EventNotificationOff
			MV_CC_RegisterStreamExceptionCallBack
		1.10	串口控制
			MV_CC_SerialPort_Open 
			MV_CC_SerialPort_Write
			MV_CC_SerialPort_Read
			MV_CC_SerialPort_ClearBuffer
			MV_CC_SerialPort_Close
		1.11	GigE相机
		1.12	U3V相机
		1.13	串口设备
			MV_CAML_SetDeviceBaudrate 
			MV_CAML_GetDeviceBaudrate
			MV_CAML_GetSupportBaudrates
			MV_CAML_SetGenCPTimeOut
			MV_CAML_GetSerialPortList
			MV_CAML_SetEnumSerialPorts
		1.14	GenTL
		1.15	回调函数定义
		1.16	设备升级
		1.17	结构体升级
		1.18	枚举类型定义
		1.19	宏定义
		1.20	状态码
	2. 
		2.1 trigger mode 
	3. Examples
		3.1	Hello World
			MV_CC_Initialize				初始化SDK
			MV_CC_CreateHandle				创建句柄
			MV_CC_OpenDevice				打开设备
			MV_CC_StartGrabbing				开始取流
			MV_CC_StopGrabbing				停止取流
			MV_CC_CloseDevice				关闭设备
			MV_CC_DestroyHandle				销毁句柄
			MV_CC_Finalize					反初始化SDK
		3.2 异步取图及处理

*/