#include "fsl_debug_console.h"
#include "board.h"
#include "math.h"
#include "fsl_mma.h"

#include "fsl_port.h"
#include "fsl_gpio.h"
#define I2C_RELEASE_BUS_COUNT 100U
void BOARD_I2C_ReleaseBus(void);

static void update_leds(uint16_t x, uint16_t y);

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

    /* Drive SDA low first to simulate a start */
    GPIO_PinWrite(BOARD_ACCEL_I2C_SDA_GPIO, BOARD_ACCEL_I2C_SDA_PIN, 0U);
    delay();

    /* Send 9 pulses on SCL and keep SDA high */
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
/* Update the duty cycle of an active pwm signal */
static void update_leds(uint16_t x, uint16_t y)
{
    /* Updated duty cycle */
    TPM_UpdatePwmDutycycle(BOARD_TIMER_PERIPHERAL, kTPM_Chnl_5, kTPM_EdgeAlignedPwm, x);
    TPM_UpdatePwmDutycycle(BOARD_TIMER_PERIPHERAL, kTPM_Chnl_2, kTPM_EdgeAlignedPwm, y);
}
void setuptimer(void)
{
	SIM->SCGC6 = SIM_SCGC6_PIT_MASK;
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->CHANNEL[0].LDVAL = DEFAULT_SYSTEM_CLOCK/100;
	PIT->CHANNEL[0].TCTRL = (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
};

int main(void)
{
    mma_handle_t mmaHandle = {0};
    mma_data_t sensorData = {0};
    mma_config_t config = {0}; 
    status_t result;
    int16_t xData = 0;
    int16_t yData = 0;
    int16_t zData = 0;
    int j = 0;
    int16_t xDuty = 0;
    int16_t yDuty = 0;

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

    while (1)
    {
        /* Get new accelerometer data. */
        if (MMA_ReadSensorData(&mmaHandle, &sensorData) != kStatus_Success)
        {
            return -1;
        }

        xData = (int16_t)((uint16_t)((uint16_t)sensorData.accelXMSB << 8) | (uint16_t)sensorData.accelXLSB) / 4U;
        yData = (int16_t)((uint16_t)((uint16_t)sensorData.accelYMSB << 8) | (uint16_t)sensorData.accelYLSB) / 4U;
        zData = (int16_t)((uint16_t)((uint16_t)sensorData.accelZMSB << 8) | (uint16_t)sensorData.accelZLSB) / 4U;

        if (j == 0){
			if (xDuty==0){
					xDuty = 100;
					yDuty = 0;
			}else{
				xDuty = 0;
				yDuty = 100;
			}
			j=100;
			update_leds(xDuty, yDuty);
        }
        j--;

        PRINTF("%dx%dy%dz", xData,yData,zData);    }
}
