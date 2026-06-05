#pragma once

// D3D9 核心头文件
#include <d3d9.h>
#include <d3d9types.h>
#if 0
// D3D9扩展（可选）
#include <d3dx9.h>        // D3DX完整库（已弃用）
#include <d3dx9math.h>    // D3DX数学库
#include <d3dx9shader.h>  // 着色器相关
#include <d3dx9effect.h>  // 效果框架
#include <d3dx9mesh.h>    // 网格处理
#endif
// 或者只包含需要的部分（推荐，减少依赖）
// #include <d3dx9math.h>    // 仅数学库

// DXGI在D3D9中不可用，使用D3D9自己的接口

// COM智能指针（D3D9需要手动管理COM对象）
#include <wrl/client.h>   // 或者使用_com_ptr_t

// 传统头文件（旧项目可能使用）
#include <windows.h>      // Windows API