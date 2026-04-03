#include <stdint.h>
#include "Systick.h"
#include "Registers/Registers.h"
/*
 * 工作原理:
 *      开启SysTick后, 计时器会把SYST_CVR里的值减少。
 *      当计数器到0后, 重新加载SYST_RVR里的值到SYST_CVR.
 *      向SYST_RVR写0, 关闭计数器.
 *      COUNTFLAG:
 *          当计数器为0时, COUNTFLAG被设置为1;
*           读取COUNTFLAG, COUNTFLAG被设置为0;
*           写SYST_CVR, COUNTFLAG被设置为0;
 */


void EnableSystick()
{
    SYST_CSR |= SYSTICK_ENABLE_BIT;
}

void DisableSystick()
{
    SYST_CSR &= ~SYSTICK_ENABLE_BIT;
}

void EnableSystickINT()
{
    SYST_CSR |= SYSTICK_TICKINT_BIT;
}

void DisableSystickINT()
{
    SYST_CSR &= ~SYSTICK_TICKINT_BIT;
}

void ReloadSystick(uint32_t Value)
{
    SYST_RVR |= (SYST_RVR_RELOAD_MASK & Value);
}

void SysTickUseProcessorClock()
{
    SYST_CSR |= SYSTICK_CLKSOURCE_BIT;
}

void SysTickUseExternalReferenceClock()
{
    SYST_CSR &= ~SYSTICK_CLKSOURCE_BIT;
}
