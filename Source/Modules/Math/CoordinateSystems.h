#pragma once
/*
    MVP = P * V * M
coordinate systems:
    Local space (or Object space)
    World space
    View space (or Eye space)
    Clip space
    Screen space
coordinate systems:
    left hand
    right hand

标准坐标系:
    屏幕朝右为X正方向, 屏幕朝左为X负方向.
    屏幕朝上为Y正方向, 屏幕朝下为Y负方向.
    屏幕朝外为Z正方向, 屏幕朝里为Z负方向.

OpenGL坐标系:右手坐标系
    屏幕朝右为X正方向, 屏幕朝左为X负方向.
    屏幕朝上为Y正方向, 屏幕朝下为Y负方向.
    屏幕朝外为Z正方向, 屏幕朝里为Z负方向.

Vulkan坐标系:右手坐标系
    屏幕朝右为X正方向，屏幕朝左为X负方向。
    屏幕朝下为Y正方向，屏幕朝上为Y负方向。
    屏幕朝外为Z负方向，屏幕朝里为Z正方向。

D3D坐标系:左手坐标系
    屏幕朝右为X正方向，屏幕朝左为X负方向。
    屏幕朝上为Y正方向, 屏幕朝下为Y负方向.
    屏幕朝外为Z负方向，屏幕朝里为Z正方向。

Metal坐标系:右手坐标系
    屏幕朝右为X正方向，屏幕朝左为X负方向。
    屏幕朝下为Y正方向，屏幕朝上为Y负方向。
    屏幕朝外为Z正方向，屏幕朝里为Z负方向。


 */