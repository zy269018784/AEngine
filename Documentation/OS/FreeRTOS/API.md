| Kernel Control API | 描述             |
|---|----------------|
| taskYIELD | 请求一次任务切换               |
| taskENTER_CRITICAL | 进入临界区          |
| taskEXIT_CRITICAL | 退出临界区          |
| taskENTER_CRITICAL_FROM_ISR | ISR中进入临界区      |
| taskEXIT_CRITICAL_FROM_ISR | ISR中退出临界区      |
| taskDISABLE_INTERRUPTS | 禁止可屏蔽中断        |
| taskENABLE_INTERRUPTS | 打开可屏蔽中断        |
| vTaskStartScheduler | 启动调度器          |
| vTaskEndScheduler | 终止调度器(会删掉所有任务) |
| vTaskSuspendAll | 挂起调度器, 不禁止中断.  |
| xTaskResumeAll | 恢复调度器.         |
| vTaskStepTick |                |

| Task Creation API | 描述          |
|-------------------|-------------|
| xTaskCreate       | 创建任务(堆动态分配) |
| xTaskCreateStatic | 创建任务(静态缓冲区) |
| vTaskDelete | 删除任务 |

| Task Control API | 描述          |
|-------------------|-------------|
| vTaskDelay       | 延迟任务几个ticks |
| vTaskDelayUntil | 延迟任务到特定时间   |
| vTaskPrioritySet | 设置任务优先级     |
| vTaskSuspend | 挂起任务        |
| vTaskResume | 恢复任务        |
| xTaskResumeFromISR |             |
| xTaskAbortDelay |             |
| uxTaskPriorityGet |             |
| uxTaskPriorityGetFromISR |             |
| uxTaskBasePriorityGet |             |
| uxTaskBasePriorityGetFromISR |             |

| Task Utilities API | 描述 |
|---|---|
| vTaskDelay |  |
| uxTaskGetSystemState |  |
| vTaskGetInfo |  |
| xTaskGetCurrentTaskHandle |  |
| xTaskGetIdleTaskHandle |  |
| uxTaskGetStackHighWaterMark |  |
| eTaskGetState |  |
| pcTaskGetName |  |
| xTaskGetHandle |  |
| xTaskGetTickCount |  |
| xTaskGetTickCountFromISR |  |
| xTaskGetSchedulerState |  |
| uxTaskGetNumberOfTasks |  |
| vTaskList |  |
| vTaskListTasks |  |
| vTaskStartTrace |  |
| ulTaskEndTrace |  |
| vTaskGetRunTimeStats |  |
| vTaskGetRunTimeStatistics |  |
| vTaskGetIdleRunTimeCounter |  |
| ulTaskGetRunTimeCounter |  |
| ulTaskGetRunTimePercent |  |
| ulTaskGetIdleRunTimeCounter |  |
| ulTaskGetIdleRunTimePercent |  |
| vTaskSetApplicationTaskTag |  |
| xTaskGetApplicationTaskTag |  |
| xTaskCallApplicationTaskHook |  |
| pvTaskGetThreadLocalStoragePointer |  |
| vTaskSetThreadLocalStoragePointer |  |
| vTaskSetTimeOutState |  |
| xTaskCheckForTimeOut |  |
| vTaskResetState |  |




| Queue Management API | 描述 |
|---|---|
| pcQueueGetName |  |
| uxQueueMessagesWaiting |  |
| uxQueueMessagesWaitingFromISR |  |
| uxQueueSpacesAvailable |  |
| vQueueAddToRegistry |  |
| vQueueDelete |  |
| vQueueUnregisterQueue |  |
| xQueueCreate |  |
| xQueueCreateStatic |  |
| xQueueGetStaticBuffers |  |
| xQueueIsQueueEmptyFromISR |  |
| xQueueIsQueueFullFromISR |  |
| xQueueOverwrite |  |
| xQueueOverwriteFromISR |  |
| xQueuePeek |  |
| xQueuePeekFromISR |  |
| xQueueReceive |  |
| xQueueReceiveFromISR |  |
| xQueueReset |  |
| xQueueSend |  |
| xQueueSendFromISR |  |
| xQueueSendToBack |  |
| xQueueSendToBackFromISR |  |
| xQueueSendToFront |  |
| xQueueSendToFrontFromISR |  |

| Queue Set API | 描述 |
|---|---|
| xQueueCreateSet |  |
| xQueueCreateSetStatic |  |
| xQueueAddToSet |  |
| xQueueRemoveFromSet |  |
| xQueueSelectFromSet |  |
| xQueueSelectFromSetFromISR |  |

| RTOS Stream Buffers API | 描述 |
|---|---|
| xStreamBufferCreate |  |
| xStreamBufferCreateStatic |  |
| xStreamBufferSend |  |
| xStreamBufferSendFromISR |  |
| xStreamBufferReceive |  |
| xStreamBufferReceiveFromISR |  |
| vStreamBufferDelete |  |
| xStreamBufferBytesAvailable |  |
| xStreamBufferSpacesAvailable |  |
| xStreamBufferSetTriggerLevel |  |
| xStreamBufferReset |  |
| xStreamBufferResetFromISR |  |
| xStreamBufferIsEmpty |  |
| xStreamBufferIsFull |  |
| xStreamBufferGetStaticBuffers |  |
| uxStreamBufferGetStreamBufferNotificationIndex |  |
| vStreamBufferSetStreamBufferNotificationIndex |  |
| xStreamBatchingBufferCreate |  |
| xStreamBatchingBufferCreateStatic |  |

| RTOS Message Buffers API | 描述 |
|---|---|
| xMessageBufferCreate |  |
| xMessageBufferCreateStatic |  |
| xMessageBufferSend |  |
| xMessageBufferSendFromISR |  |
| xMessageBufferReceive |  |
| xMessageBufferReceiveFromISR |  |
| vMessageBufferDelete |  |
| xMessageBufferSpacesAvailable |  |
| xMessageBufferReset |  |
| xMessageBufferResetFromISR |  |
| xMessageBufferIsEmpty |  |
| xMessageBufferIsFull |  |
| xMessageBufferGetStaticBuffers |  |

| Semaphores API | 描述 |
|---|---|
| xSemaphoreCreateBinary |  |
| xSemaphoreCreateBinaryStatic |  |
| vSemaphoreCreateBinary |  |
| xSemaphoreCreateCounting |  |
| xSemaphoreCreateCountingStatic |  |
| xSemaphoreCreateMutex |  |
| xSemaphoreCreateMutexStatic |  |
| xSemaphoreCreateRecursiveMutex |  |
| xSemaphoreCreateRecursiveMutexStatic |  |
| vSemaphoreDelete |  |
| xSemaphoreGetMutexHolder |  |
| xSemaphoreTake |  |
| xSemaphoreTakeFromISR |  |
| xSemaphoreTakeRecursive |  |
| xSemaphoreGive |  |
| xSemaphoreGiveRecursive |  |
| xSemaphoreGiveFromISR |  |
| uxSemaphoreGetCount |  |

| Software Timers API | 描述 |
|---|---|
| xTimerCreate |  |
| xTimerCreateStatic |  |
| xTimerIsTimerActive |  |
| pvTimerGetTimerID |  |
| pcTimerGetName |  |
| vTimerSetReloadMode |  |
| xTimerStart |  |
| xTimerStop |  |
| xTimerChangePeriod |  |
| xTimerDelete |  |
| xTimerReset |  |
| xTimerStartFromISR |  |
| xTimerStopFromISR |  |
| xTimerChangePeriodFromISR |  |
| xTimerResetFromISR |  |
| vTimerResetState |  |
| pvTimerGetTimerID |  |
| vTimerSetTimerID |  |
| xTimerGetTimerDaemonTaskHandle |  |
| xTimerPendFunctionCall |  |
| xTimerPendFunctionCallFromISR |  |
| xTimerGetPeriod |  |
| xTimerGetExpiryTime |  |
| xTimerGetReloadMode |  |

| Event Groups API | 描述 |
|---|---|
| xEventGroupCreate |  |
| xEventGroupCreateStatic |  |
| xEventGroupWaitBits |  |
| xEventGroupSetBits |  |
| xEventGroupSetBitsFromISR |  |
| xEventGroupClearBits |  |
| xEventGroupClearBitsFromISR |  |
| xEventGroupGetBits |  |
| xEventGroupGetBitsFromISR |  |
| xEventGroupGetStaticBuffer |  |
| xEventGroupSync |  |
| vEventGroupDelete |  |

| FreeRTOS-MPU Specific Functions | 描述 |
|---|---|
| xTaskCreateRestricted |  |
| vTaskAllocateMPURegions |  |
| portSWITCH_TO_USER_MODE |  |

| Co-routine API | 描述 |
|---|---|
| CoRoutineHandle_t |  |
| xCoRoutineCreate |  |
| crDELAY |  |
| crQUEUE_SEND |  |
| crQUEUE_RECEIVE |  |
| crQUEUE_SEND_FROM_ISR |  |
| crQUEUE_RECEIVE_FROM_ISR |  |
| vCoRoutineSchedule |  |



