#pragma once

// D3D11 核心头文件
#include <d3d11.h>
#include <d3d11_1.h>      // D3D11.1 功能（可选）
#include <d3d11_2.h>      // D3D11.2 功能（可选）
#include <d3d11_3.h>      // D3D11.3 功能（可选）
#include <d3d11_4.h>      // D3D11.4 功能（可选）

// DXGI（图形接口）
#include <dxgi.h>
#include <dxgi1_2.h>      // DXGI 1.2（Windows 8+）
#include <dxgi1_3.h>      // DXGI 1.3（Windows 8.1+）
#include <dxgi1_4.h>      // DXGI 1.4（Windows 10+）
#include <dxgi1_5.h>      // DXGI 1.5（可选）
#include <dxgi1_6.h>      // DXGI 1.6（Windows 10 1703+）

// 着色器编译
#include <d3dcompiler.h>

// COM智能指针
#include <wrl/client.h>   // 注意：D3D11通常使用wrl/client.h

// 数学库
#include <DirectXMath.h>
#include <DirectXColors.h> // DirectX颜色常量（可选）

// 其他实用工具
#include <DirectXPackedVector.h> // 打包向量（可选）
#include <DirectXCollision.h>    // 碰撞检测（可选）

// 旧版D3DX库（不推荐使用，仅用于兼容）
// #include <D3DX11.h>        // 已弃用
// #include <D3DX11async.h>   // 已弃用