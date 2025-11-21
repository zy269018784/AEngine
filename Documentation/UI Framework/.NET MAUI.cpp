/*
	1. 
	2. 编译各种
		2.1 QT
			set (CMAKE_AUTOMOC ON)
			set (CMAKE_AUTOUIC ON)
			set (CMAKE_AUTORCC ON)
			find_package(Qt6 COMPONENTS Widgets Qml Quick QuickControls2 QuickWidgets REQUIRED)
			set (QT_LIBS Qt6::Widgets
						 Qt6::QuickWidgets
						 Qt6::Quick
						 Qt6::Qml
						 Qt6::QuickControls2)

		2.2 MFC
			-DQLEMR_CFG_DLL
			-D_AFXDLL
			-DUNICODE -D_UNICODE
			CMAKE_MFC_FLAG	
				1	静态链接
				2	动态链接
			add_executable(${PROJ_NAME} WIN32 ${SRC_LIST})
*/