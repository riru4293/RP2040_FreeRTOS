#include <stdio.h>
#include "pico/stdlib.h"

// /* FreeRTOS */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>



typedef uint     UINT;      /* 32bit */
typedef uint8_t  UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef bool BOOL;
typedef void VOID;


#define TRUE            ( (BOOL)true )
#define FALSE           ( (BOOL)false )

// #define MINOF_UINT      ( (UINT)0U )
// #define MINOF_UINT8     ( (UINT8)0U )
// #define MINOF_UINT16    ( (UINT16)0U )
// #define MINOF_UINT32    ( (UINT32)0U )
// #define MINOF_UINT64    ( (UINT64)0U )

// #define MAXOF_UINT      ( (UINT)0xFFFFFFFFU )
// #define MAXOF_UINT8     ( (UINT8)0xFFU )
// #define MAXOF_UINT16    ( (UINT16)0xFFFFU )
// #define MAXOF_UINT32    ( (UINT32)0xFFFFFFFFU )
// #define MAXOF_UINT64    ( (UINT64)0xFFFFFFFFFFFFFFFFULL )


static VOID task( VOID* unused );

/* -------------------------------------------------------------------------- */
/* Globals                                                                 */
/* -------------------------------------------------------------------------- */
volatile static SemaphoreHandle_t semaphore;
static TaskHandle_t task_handle;


int main()
{
    stdio_init_all();

    xTaskCreate( task, "TEST_TASK", 1024, NULL, 1, &task_handle );

    vTaskStartScheduler();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

static VOID task( VOID* unused )
{
    /* Create binary semaphore for reset CAN controller */
    semaphore = xSemaphoreCreateBinary();
    
    while( TRUE )
    {
        /* Wait a reset request */
        xSemaphoreTake( semaphore, portMAX_DELAY );
    }
}
