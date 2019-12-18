#include "mkl_TPMPulseWidthModulation.h"
#include "../Dispositivos/switch.h"
#include "../Dispositivos/led.h"

class MotorDC
{
private:
    mkl_TPMPulseWidthModulation pwm_motor;
    mkl_GPIOPort portClockWise;
    mkl_GPIOPort portCounterClockWise;
    int spin;
    int speed;

public:
    MotorDC(tpm_Pin tmp_pin, gpio_Pin pin_left, gpio_Pin pin_right) : pwm_motor(tmp_pin), portClockWise(pin_left), portCounterClockWise(pin_right)
    {
        int duty = 500;
        spin = 1;

        pwm_motor.setFrequency(tpm_div16, 999);
        pwm_motor.setDutyCycle(duty);

        portClockWise.setPortMode(gpio_output);
        portClockWise.setPullResistor(gpio_pullUpResistor);
        portCounterClockWise.setPortMode(gpio_output);
        portCounterClockWise.setPullResistor(gpio_pullUpResistor);

        spinClockWise();
    }
    void turnOn()
    {
        pwm_motor.enableOperation();
    }
    void turnOff()
    {
        pwm_motor.setFrequency(tpm_div16, 999);
        pwm_motor.setDutyCycle(0);
        pwm_motor.enableOperation();
    }
    void spinClockWise()
    {
        portClockWise.writeBit(spin);
        portCounterClockWise.writeBit(!spin);
    }
    void spinCounterClockWise()
    {
        portClockWise.writeBit(!spin);
        portCounterClockWise.writeBit(spin);
    }
    void speedLow()
    {
        pwm_motor.setFrequency(tpm_div16, 999);
        pwm_motor.setDutyCycle(250);
        pwm_motor.enableOperation();
    }
    void speedHigh()
    {
        pwm_motor.setFrequency(tpm_div16, 999);
        pwm_motor.setDutyCycle(750);
        pwm_motor.enableOperation();
    }
};

class Buzzer
{
private:
    mkl_GPIOPort pinBuzzer;

public:
    Buzzer(gpio_Pin buzzer_pin) : pinBuzzer(buzzer_pin)
    {
        pinBuzzer.setPortMode(gpio_output);
        pinBuzzer.setPullResistor(gpio_pullUpResistor);
    }
    void delayMsMotor(int time)
    {
        int i;
        int j;

        for (i = 0; i < time; i++)
        {
            for (j = 0; j < 7000; j++)
            {
            }
        }
    }
    void activeBuzzer()
    {
        pinBuzzer.writeBit(1);
        delayMsMotor(250);
        pinBuzzer.writeBit(0);
    }
};

