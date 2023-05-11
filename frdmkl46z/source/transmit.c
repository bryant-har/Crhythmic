#include "fsl_debug_console.h"
#include "board.h"
#include "math.h"
#include "fsl_mma.h"
#include <MKL46Z4.h>
#include <system_MKL46Z4.h>
#include "fsl_port.h"
#include "LED.h"
#include "fsl_gpio.h"
#define I2C_RELEASE_BUS_COUNT 100U
void BOARD_I2C_ReleaseBus(void);

/* MMA8451 device address */
const uint8_t g_accel_address[] = {0x1CU, 0x1DU, 0x1EU, 0x1FU};

static void delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}

void BOARD_I2C_ReleaseBus(void)
{
    uint8_t i = 0;

    BOARD_Init_I2C_GPIO_pins();
    GPIO_PinWrite(BOARD_ACCEL_I2C_SDA_GPIO, BOARD_ACCEL_I2C_SDA_PIN, 0U);
    delay();
    for (i = 0; i < 9; i++)
    {
        GPIO_PinWrite(BOARD_ACCEL_I2C_SCL_GPIO, BOARD_ACCEL_I2C_SCL_PIN, 0U);
        delay();

        GPIO_PinWrite(BOARD_ACCEL_I2C_SDA_GPIO, BOARD_ACCEL_I2C_SDA_PIN, 1U);
        delay();

        GPIO_PinWrite(BOARD_ACCEL_I2C_SCL_GPIO, BOARD_ACCEL_I2C_SCL_PIN, 1U);
        delay();
        delay();
    }

    /* Send stop */
    GPIO_PinWrite(BOARD_ACCEL_I2C_SCL_GPIO, BOARD_ACCEL_I2C_SCL_PIN, 0U);
    delay();

    GPIO_PinWrite(BOARD_ACCEL_I2C_SDA_GPIO, BOARD_ACCEL_I2C_SDA_PIN, 0U);
    delay();

    GPIO_PinWrite(BOARD_ACCEL_I2C_SCL_GPIO, BOARD_ACCEL_I2C_SCL_PIN, 1U);
    delay();

    GPIO_PinWrite(BOARD_ACCEL_I2C_SDA_GPIO, BOARD_ACCEL_I2C_SDA_PIN, 1U);
    delay();
}
void setuptimer(void)
{
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK;
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->CHANNEL[0].LDVAL = DEFAULT_SYSTEM_CLOCK/60;
	PIT->CHANNEL[0].TCTRL = (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
};

int16_t xData = 0;
int16_t yData = 0;
int16_t zData = 0;
mma_data_t sensorData = {0};

int main(void)
{
    mma_handle_t mmaHandle = {0};
    mma_config_t config = {0}; 
    status_t result;
    int j = 0;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_I2C_ReleaseBus();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();
    CLOCK_SetTpmClock(1U);
    BOARD_InitPeripherals();


    config.I2C_SendFunc = BOARD_Accel_I2C_Send;
    config.I2C_ReceiveFunc = BOARD_Accel_I2C_Receive;

	config.slaveAddress = g_accel_address[1];
	result = MMA_Init(&mmaHandle, &config);
    if (result != kStatus_Success)
    {
        PRINTF("\r\nSensor device initialize failed!\r\n");
        return -1;
    }


    /* Start timer */
    TPM_StartTimer(BOARD_TIMER_PERIPHERAL, kTPM_SystemClock);
	NVIC_EnableIRQ(PIT_IRQn);
	LED_Initialize();
	setuptimer();
	LEDRed_Toggle();


    while (1)
    {
        /* Get new accelerometer data. */
        if (MMA_ReadSensorData(&mmaHandle, &sensorData) != kStatus_Success)
        {
            return -1;
        }


        if (j == 0){
			j=100;
			LEDRed_Toggle();
        }
        j--;

            }
}


void PIT_IRQHandler(void)
{
	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
	LEDGreen_Toggle();

    xData = (int16_t)((uint16_t)((uint16_t)sensorData.accelXMSB << 8) | (uint16_t)sensorData.accelXLSB) / 4U;
    yData = (int16_t)((uint16_t)((uint16_t)sensorData.accelYMSB << 8) | (uint16_t)sensorData.accelYLSB) / 4U;
    zData = (int16_t)((uint16_t)((uint16_t)sensorData.accelZMSB << 8) | (uint16_t)sensorData.accelZLSB) / 4U;
    PRINTF("%dx%dy%dz", xData,yData,zData);
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[0].LDVAL = DEFAULT_SYSTEM_CLOCK/60;
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
};
