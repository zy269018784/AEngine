/*
	1. 
		https://llvm.org/
		https://github.com/llvm/llvm-project/releases

	2. 下载链接
		https://github.com/llvm/llvm-project/releases/download/llvmorg-21.1.4/clang+llvm-21.1.4-x86_64-pc-windows-msvc.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-21.1.0/clang+llvm-21.1.0-x86_64-pc-windows-msvc.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.8/clang+llvm-18.1.8-x86_64-pc-windows-msvc.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.7/clang+llvm-18.1.7-x86_64-pc-windows-msvc.tar.xz

		https://github.com/llvm/llvm-project/releases/download/llvmorg-21.1.4/LLVM-21.1.4-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-21.1.0/LLVM-21.1.0-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.8/LLVM-18.1.8-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.7/LLVM-18.1.7-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/LLVM-17.0.6-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-16.0.6/LLVM-16.0.6-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.6/LLVM-14.0.6-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/LLVM-14.0.4-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.0/LLVM-14.0.0-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.0/LLVM-13.0.0-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-12.0.0/LLVM-12.0.0-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-11.0.0/LLVM-11.0.0-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/LLVM-10.0.0-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-9.0.1/LLVM-9.0.1-win64.exe
		https://releases.llvm.org/9.0.0/LLVM-9.0.0-win64.exe
		https://releases.llvm.org/8.0.0/LLVM-8.0.0-win64.exe
		https://releases.llvm.org/7.0.1/LLVM-7.0.1-win64.exe
		https://releases.llvm.org/7.0.0/LLVM-7.0.0-win64.exe
		https://releases.llvm.org/6.0.0/LLVM-6.0.0-win64.exe
		https://releases.llvm.org/5.0.1/LLVM-5.0.1-win64.exe
		https://releases.llvm.org/5.0.0/LLVM-5.0.0-win64.exe
		https://releases.llvm.org/4.0.1/LLVM-4.0.1-win64.exe
		https://releases.llvm.org/4.0.0/LLVM-4.0.0-win64.exe
		https://releases.llvm.org/3.9.1/LLVM-3.9.1-win64.exe
		https://releases.llvm.org/3.9.0/LLVM-3.9.0-win64.exe

	3. 源码下载链接
		https://github.com/llvm/llvm-project/releases/download/llvmorg-21.1.0/llvm-21.1.0.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.8/llvm-18.1.8.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.7/llvm-18.1.7.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/llvm-17.0.6.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-16.0.6/llvm-16.0.6.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.6/llvm-14.0.6.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/llvm-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.0/llvm-14.0.0.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-13.0.0/llvm-13.0.0.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-12.0.0/llvm-12.0.0.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-11.0.0/llvm-11.0.0.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/llvm-10.0.0.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-9.0.1/llvm-9.0.1.src.tar.xz
		https://releases.llvm.org/9.0.0/llvm-9.0.0.src.tar.xz
		https://releases.llvm.org/8.0.0/llvm-8.0.0.src.tar.xz
		https://releases.llvm.org/7.0.1/llvm-7.0.1.src.tar.xz
		https://releases.llvm.org/7.0.0/llvm-7.0.0.src.tar.xz
		https://releases.llvm.org/6.0.0/llvm-6.0.0.src.tar.xz
		https://releases.llvm.org/5.0.1/llvm-5.0.1.src.tar.xz
		https://releases.llvm.org/5.0.0/llvm-5.0.0.src.tar.xz
		https://releases.llvm.org/4.0.1/llvm-4.0.1.src.tar.xz
		https://releases.llvm.org/4.0.0/llvm-4.0.0.src.tar.xz
		https://releases.llvm.org/3.9.1/llvm-3.9.1.src.tar.xz
		https://releases.llvm.org/3.9.0/llvm-3.9.0.src.tar.xz



	3. 14.04
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/LLVM-14.0.4-win64.exe
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/clang-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/flang-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/libclc-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/libcxx-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/libunwind-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/lld-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/lldb-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/openmp-14.0.4.src.tar.xz
		https://github.com/llvm/llvm-project/releases/download/llvmorg-14.0.4/polly-14.0.4.src.tar.xz
*/