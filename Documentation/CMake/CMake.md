1. 支持的语言
	C
	C++
	C#
	Java
	Fortran
	Objective-C 
	Objective-C++
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

3. 命令行
cmake 
	-S
	-B 
	-D
	-G
	--open
	--build
	--target
   -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake


toolchain.cmake
	# toolchain.cmake
	set(CMAKE_SYSTEM_NAME Linux)
	set(CMAKE_SYSTEM_PROCESSOR aarch64)
	
	# 交叉编译器
	set (CMAKE_MAKE_PROGRAM "C:/Program Files/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r6_/mingw64/bin/make.exe")
	set (CMAKE_C_COMPILER "C:/app/arm-gnu-toolchain-15.2.rel1-mingw-w64-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc.exe")
	set (CMAKE_CXX_COMPILER "C:/app/arm-gnu-toolchain-15.2.rel1-mingw-w64-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-c++.exe")
	
	# 清除 Windows 特定标志
	set(CMAKE_EXE_LINKER_FLAGS "" CACHE STRING "" FORCE)
	set(CMAKE_SHARED_LINKER_FLAGS "" CACHE STRING "" FORCE)
5. 脚本
   CMAKE_AUTOUIC 
   CMAKE_AUTOMOC 
   CMAKE_AUTORCC 
   CMAKE_CXX_STANDARD

