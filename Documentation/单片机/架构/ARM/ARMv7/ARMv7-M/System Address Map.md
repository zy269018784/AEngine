| Address Range             | Notes                                                                  |
|---------------------------|------------------------------------------------------------------------|
| 0x00000000-0x1FFFFFFF     | Code                                                                   |
| 0x20000000-0x3FFFFFFF     | SRAM                                                                   |
| 0x40000000-0x5FFFFFFF     | Peripheral                                                             |
| 0x60000000-0x7FFFFFFF     | RAM                                                                    |
| 0x80000000-0x9FFFFFFF     | RAM                                                                    |
| 0xA0000000-0xBFFFFFFF     | Device                                                                 |
| 0xC0000000-0xDFFFFFFF     | Device                                                                 |
| 0xE0000000-0xFFFFFFFF     | System                                                                 |
| 0xE000E000-0xE000EFFF     | System Control Space                                                   |
| 0xE000E000-0xE000E00F     | Includes the Interrupt Controller Type and Auxiliary Control registers |
| 0xE000ED00-0xE000ED8F     | System Control Block                                                   |
| 0xE000E100-0xE000ECFF     | NVIC                                                                   |
| 0xE000E010-0xE000E0FF     | SysTick                                                                |
| 0xE000ED90-0xE000EDEF     | MPU                                                                    |


| Address                                    | Register            |
|--------------------------------------------|---------------------|
| 0xE000E100                                 | NVIC_ISER0          |
| ...                                        | NVIC_ISERx          |
| 0xE000E13C                                 | NVIC_ISER15         |
| 0xE000E180                                 | NVIC_ICER0          |
| ...                                        | NVIC_ICERx          |
| 0xE000E1BC                                 | NVIC_ICER15         |
| 0xE000E200                                 | NVIC_ISPR0          |
| ...                                        | NVIC_ISPRx          |
| 0xE000E23C                                 | NVIC_ISPR15         |
| 0xE000E280                                 | NVIC_ICPR0          |
| ...                                        | NVIC_ICPRx          |
| 0xE000E2BC                                 | NVIC_ICPR15         |
| 0xE000E300                                 | NVIC_IABR0          |
| ...                                        | NVIC_IABRx          |
| 0xE000E33C                                 | NVIC_IABR15         |
| 0xE000E400                                 | NVIC_IPR0           |
| ...                                        | NVIC_IPRx           |
| 0xE000E5EC                                 | NVIC_IPR123         |
| 0xE000E010                                 | SYST_CSR            |
| 0xE000E014                                 | SYST_RVR            |
| 0xE000E018                                 | SYST_CVR            |
| 0xE000E01C                                 | SYST_CALIB          |
| 0xE000ED90                                 | MPU_TYPE            |
| 0xE000ED94                                 | MPU_CTRL            |
| 0xE000ED98                                 | MPU_RNR             |
| 0xE000ED9C                                 | MPU_RBAR            |
| 0xE000EDA0                                 | MPU_RASR            |
| 0xE000EDA4                                 | MPU_RBAR_A1         |
| 0xE000EDA8                                 | MPU_RASR_A1         |
| 0xE000EDAC                                 | MPU_RBAR_A2         |
| 0xE000EDB0                                 | MPU_RASR_A2        |
| 0xE000EDB4                                 | MPU_RBAR_A3        |
| 0xE000EDB8                                 | MPU_RASR_A3        |










