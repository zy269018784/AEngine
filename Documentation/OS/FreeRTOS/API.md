Task Creation:
    xTaskCreate
    xTaskCreateStatic
    xTaskCreateRestrictedStatic
    vTaskDelete


Task Control:
    vTaskDelay
    vTaskDelayUntil
    xTaskDelayUntil
    uxTaskPriorityGet
    uxTaskPriorityGetFromISR
    uxTaskBasePriorityGet
    uxTaskBasePriorityGetFromISR
    vTaskPrioritySet
    vTaskSuspend
    vTaskResume
    xTaskResumeFromISR
    xTaskAbortDelay

Task Utilities
    uxTaskGetSystemState
    vTaskGetInfo
    xTaskGetCurrentTaskHandle
    xTaskGetIdleTaskHandle
    uxTaskGetStackHighWaterMark
    eTaskGetState
    pcTaskGetName
    xTaskGetHandle
    xTaskGetTickCount
    xTaskGetTickCountFromISR
    xTaskGetSchedulerState
    uxTaskGetNumberOfTasks
    vTaskList
    vTaskListTasks
    vTaskStartTrace
    ulTaskEndTrace
    vTaskGetRunTimeStats
    vTaskGetRunTimeStatistics
    vTaskGetIdleRunTimeCounter
    ulTaskGetRunTimeCounter
    ulTaskGetRunTimePercent
    ulTaskGetIdleRunTimeCounter
    ulTaskGetIdleRunTimePercent
    vTaskSetApplicationTaskTag
    xTaskGetApplicationTaskTag
    xTaskCallApplicationTaskHook
    pvTaskGetThreadLocalStoragePointer
    vTaskSetThreadLocalStoragePointer
    vTaskSetTimeOutState
    xTaskCheckForTimeOut
    vTaskResetState     


Kernel Control
    taskYIELD
    taskENTER_CRITICAL
    taskEXIT_CRITICAL
    taskENTER_CRITICAL_FROM_ISR
    taskEXIT_CRITICAL_FROM_ISR
    taskDISABLE_INTERRUPTS
    taskENABLE_INTERRUPTS
    vTaskStartScheduler
    vTaskEndScheduler
    vTaskSuspendAll
    xTaskResumeAll
    vTaskStepTick

Queue Management
    pcQueueGetName
    uxQueueMessagesWaiting
    uxQueueMessagesWaitingFromISR
    uxQueueSpacesAvailable
    vQueueAddToRegistry
    vQueueDelete
    vQueueUnregisterQueue
    xQueueCreate
    xQueueCreateStatic
    xQueueGetStaticBuffers
    xQueueIsQueueEmptyFromISR
    xQueueIsQueueFullFromISR
    xQueueOverwrite
    xQueueOverwriteFromISR
    xQueuePeek
    xQueuePeekFromISR
    xQueueReceive
    xQueueReceiveFromISR
    xQueueReset
    xQueueSend
    xQueueSendFromISR
    xQueueSendToBack
    xQueueSendToBackFromISR
    xQueueSendToFront
    xQueueSendToFrontFromISR

Queue Set
    xQueueCreateSet
    xQueueCreateSetStatic
    xQueueAddToSet
    xQueueRemoveFromSet
    xQueueSelectFromSet
    xQueueSelectFromSetFromISR

RTOS Stream Buffers
    xStreamBufferCreate 
    xStreamBufferCreateStatic 
    xStreamBufferSend 
    xStreamBufferSendFromISR 
    xStreamBufferReceive 
    xStreamBufferReceiveFromISR 
    vStreamBufferDelete 
    xStreamBufferBytesAvailable 
    xStreamBufferSpacesAvailable 
    xStreamBufferSetTriggerLevel 
    xStreamBufferReset 
    xStreamBufferResetFromISR 
    xStreamBufferIsEmpty 
    xStreamBufferIsFull 
    xStreamBufferGetStaticBuffers 
    uxStreamBufferGetStreamBufferNotificationIndex 
    vStreamBufferSetStreamBufferNotificationIndex 
    xStreamBatchingBufferCreate 
    xStreamBatchingBufferCreateStatic 

RTOS Message Buffers
    xMessageBufferCreate 
    xMessageBufferCreateStatic 
    xMessageBufferSend 
    xMessageBufferSendFromISR 
    xMessageBufferReceive 
    xMessageBufferReceiveFromISR 
    vMessageBufferDelete 
    xMessageBufferSpacesAvailable 
    xMessageBufferReset 
    xMessageBufferResetFromISR 
    xMessageBufferIsEmpty 
    xMessageBufferIsFull 
    xMessageBufferGetStaticBuffers 

Semaphores
    xSemaphoreCreateBinary
    xSemaphoreCreateBinaryStatic
    vSemaphoreCreateBinary
    xSemaphoreCreateCounting
    xSemaphoreCreateCountingStatic
    xSemaphoreCreateMutex
    xSemaphoreCreateMutexStatic
    xSemaphoreCreateRecursiveMutex
    xSemaphoreCreateRecursiveMutexStatic
    vSemaphoreDelete
    xSemaphoreGetMutexHolder
    xSemaphoreTake
    xSemaphoreTakeFromISR
    xSemaphoreTakeRecursive
    xSemaphoreGive
    xSemaphoreGiveRecursive
    xSemaphoreGiveFromISR
    uxSemaphoreGetCount

Software Timers
    xTimerCreate
    xTimerCreateStatic
    xTimerIsTimerActive
    pvTimerGetTimerID
    pcTimerGetName
    vTimerSetReloadMode
    xTimerStart
    xTimerStop
    xTimerChangePeriod
    xTimerDelete
    xTimerReset
    xTimerStartFromISR
    xTimerStopFromISR
    xTimerChangePeriodFromISR
    xTimerResetFromISR
    vTimerResetState
    pvTimerGetTimerID
    vTimerSetTimerID
    xTimerGetTimerDaemonTaskHandle
    xTimerPendFunctionCall
    xTimerPendFunctionCallFromISR
    xTimerGetPeriod
    xTimerGetExpiryTime
    xTimerGetReloadMode

Event Groups
    xEventGroupCreate
    xEventGroupCreateStatic
    xEventGroupWaitBits
    xEventGroupSetBits
    xEventGroupSetBitsFromISR
    xEventGroupClearBits
    xEventGroupClearBitsFromISR
    xEventGroupGetBits
    xEventGroupGetBitsFromISR
    xEventGroupGetStaticBuffer
    xEventGroupSync
    vEventGroupDelete


FreeRTOS-MPU Specific Functions
    xTaskCreateRestricted 
    vTaskAllocateMPURegions 
    portSWITCH_TO_USER_MODE 

Co-routine
    CoRoutineHandle_t
    xCoRoutineCreate
    crDELAY
    crQUEUE_SEND
    crQUEUE_RECEIVE
    crQUEUE_SEND_FROM_ISR
    crQUEUE_RECEIVE_FROM_ISR
    vCoRoutineSchedule




