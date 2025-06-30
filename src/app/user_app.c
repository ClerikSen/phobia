#include <stddef.h>

#include "freertos/FreeRTOS.h"
#include "hal/hal.h"

#include "starter_generator.h"
#include "libc.h"
#include "main.h"
#include "regfile.h"

/* The application allows you to startup PMC automatically at power up.
 * */

LD_TASK void app_AUTOSTART(void *pData)
{
	volatile int		*lknob = (volatile int *) pData;

	run_starter_generator(void *pData);

    vTaskDelete( NULL );
}

