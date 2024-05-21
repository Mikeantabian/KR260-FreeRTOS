/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
/* Xilinx includes. */
#include "xgpio.h"
#include "xstatus.h"
#include "xparameters.h"
/* GPIO device that LEDs are connected to */
#define GPIO_DEVICE_ID  XPAR_AXI_GPIO_0_BASEADDR
/* GPIO port for LEDs */
#define LED_CHANNEL 1
#define DELAY_100_miliSec 100
#define DELAY_1_Sec 1000
#define DELAY_2_Sec 2000
#define DELAY_3_Sec 3000
#define DELAY_4_Sec 4000
static void Task01( void *arguments );
static void Task02( void *arguments );
static void Task03( void *arguments );
static void Task04( void *arguments );
static TaskHandle_t Task01Handle;
static TaskHandle_t Task02Handle;
static TaskHandle_t Task03Handle;
static TaskHandle_t Task04Handle;

XGpio Gpio;

int main( void ) {
    /* GPIO driver initialization */
    int status = XGpio_Initialize(&Gpio, GPIO_DEVICE_ID);
    if (status != XST_SUCCESS) {
        return XST_FAILURE;
    }
    /*Set the direction for the LEDs to output. */
    XGpio_SetDataDirection(&Gpio, LED_CHANNEL, 0x0);

        xTaskCreate(
                /* The function that implements the task. */
                Task01,
                /* Text name for the task, provided to assist debugging only. */
                ( const char * ) "Task01",
                /* The stack allocated to the task. */
                configMINIMAL_STACK_SIZE,
                /* The task parameter is not used, so set to NULL. */
                NULL,
                /* The task runs at the idle priority. */
                tskIDLE_PRIORITY + 3,
                &Task01Handle);

        xTaskCreate(Task02,
                    ( const char * ) "Task02",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    tskIDLE_PRIORITY + 2,
                    &Task02Handle );

        xTaskCreate(Task03,
                    ( const char * ) "Task03",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    tskIDLE_PRIORITY + 1,
                    &Task03Handle );

        xTaskCreate(Task04,
                    ( const char * ) "Task04",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    tskIDLE_PRIORITY,
                    &Task04Handle );

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

        /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for( ;; );
}

static void Task01( void *arguments )
{
    int task = 1;
    const TickType_t x1Sec = pdMS_TO_TICKS( DELAY_1_Sec );

    for( ;; )
    {
    
        xil_printf("Hello from task: %d\r\n", task);
        /* Delay for 1 second. */
        vTaskDelay( x1Sec );

    }
}

static void Task02( void *arguments )
{
    int task = 2;
    const TickType_t x2Sec = pdMS_TO_TICKS( DELAY_2_Sec );

    for( ;; )
    {
    
        xil_printf("Hello from task: %d\r\n", task);
        /* Delay for 2 second. */
        vTaskDelay( x2Sec );

    }
}

static void Task03( void *arguments )
{
    int task = 3;
    const TickType_t x3Sec = pdMS_TO_TICKS( DELAY_3_Sec );

    for( ;; )
    {
    
        xil_printf("Hello from task: %d\r\n", task);
        /* Delay for 3 second. */
        vTaskDelay( x3Sec );

    }
}

static void Task04( void *arguments )
{
    int task = 4;
    const TickType_t x4Sec = pdMS_TO_TICKS( DELAY_4_Sec );
    const TickType_t xThirdSec = pdMS_TO_TICKS( DELAY_100_miliSec );

    for( ;; )
    {
        for(int i = 0; i < 3; i++){
            xil_printf("Hello from task: %d\r\n", task);
            /* Delay for 1 second. */
            vTaskDelay( xThirdSec );
        }
        //xil_printf("Hello from task: %d\r\n", task);

        /* Delay for 4 second. */
        vTaskDelay( x4Sec );

    }
}








