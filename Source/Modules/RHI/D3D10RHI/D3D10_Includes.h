#pragma once

// D3D10 核心头文件
#include <d3d10.h>


// DXGI
#include <dxgi.h>
#if 0
// 效果框架（D3DX10）
#include <d3dx10.h>
#include <d3dx10math.h>
#include <d3dx10async.h>  // 异步着色器编译
#endif
// COM智能指针
#include <wrl/client.h>
#if 0
// 注意：DirectXMath在DX10时还未引入
// 可以使用D3DX数学库或XNAMath
#include <xnamath.h>      // XNA数学库（Windows SDK 8.0之前）
#endif