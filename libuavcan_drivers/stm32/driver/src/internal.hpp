/*
 * Copyright (C) 2014 Pavel Kirienko <pavel.kirienko@gmail.com>
 */

#pragma once

#if UAVCAN_STM32_CHIBIOS
# include <hal.h>
#else
# error "Unknown OS"
#endif

#if UAVCAN_STM32_DEBUG
# include <cstdio>
# include <cstdarg>
#endif

/**
 * IRQ handler macros
 */
#if UAVCAN_STM32_CHIBIOS

# define UAVCAN_STM32_IRQ_HANDLER(id)  CH_IRQ_HANDLER(id)
# define UAVCAN_STM32_IRQ_PROLOGUE()    CH_IRQ_PROLOGUE()
# define UAVCAN_STM32_IRQ_EPILOGUE()    CH_IRQ_EPILOGUE()

#else

# define UAVCAN_STM32_IRQ_HANDLER(id)  void id(void)
# define UAVCAN_STM32_IRQ_PROLOGUE()
# define UAVCAN_STM32_IRQ_EPILOGUE()

#endif

/**
 * Priority mask for timer and CAN interrupts.
 */
#ifndef UAVCAN_STM32_IRQ_PRIORITY_MASK
# define UAVCAN_STM32_IRQ_PRIORITY_MASK  CORTEX_PRIORITY_MASK(CORTEX_MAX_KERNEL_PRIORITY)
#endif

/**
 * Any General-Purpose timer (TIM2, TIM3, TIM4, TIM5)
 * e.g. -DUAVCAN_STM32_TIMER_NUMBER=2
 */
#ifndef UAVCAN_STM32_TIMER_NUMBER
# error UAVCAN_STM32_TIMER_NUMBER
#endif

/**
 * Glue macros
 */
#define UAVCAN_STM32_GLUE2_(A, B)       A##B
#define UAVCAN_STM32_GLUE2(A, B)        UAVCAN_STM32_GLUE2_(A, B)

#define UAVCAN_STM32_GLUE3_(A, B, C)    A##B##C
#define UAVCAN_STM32_GLUE3(A, B, C)     UAVCAN_STM32_GLUE3_(A, B, C)

namespace uavcan_stm32
{

struct CriticalSectionLocker
{
    CriticalSectionLocker() { chSysSuspend(); }
    ~CriticalSectionLocker() { chSysEnable(); }
};

namespace clock
{

uavcan::uint64_t getUtcUSecFromCanInterrupt();

}

}
