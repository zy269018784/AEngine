#pragma once
#include <cstdint>
#include <list>
class GUIElement
{
public:
    /*
     * 父对象
     */
    GUIElement *Parent;
    /*
     * 孩子
     */
    std::list<GUIElement*> Children;
    /*
     * 宽度
     */
    std::uin32_t Width;
    /*
     * 高度
     */
    std::uint32_t Height;
    /*
     * X
     */
    std::uin32_t X;
    /*
     * Y
     */
    std::uint32_t Y;
    /*
     * 图层
     */
    std::uint32_t Z;
    /*
     * 使能
     */
    bool Enabled;
    /*
     * 聚焦
     */
    bool Focus;
    /*
     * 可见
     */
    bool Visible;
};
