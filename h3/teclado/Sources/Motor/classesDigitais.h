#include "classesDispositivos.h"

class OnOff
{
private:
    led led_device;
    Switch button_device;

public:
    OnOff(gpio_Pin pin_button, gpio_Pin pin_led) : button_device(pin_button), led_device(pin_led)
    {
    }
    int readButton()
    {
        return button_device.read();
    }
    void writeLed(int params){
    	led_device.off();
    	if(params==1){
    		 led_device.on();
    	}

    }
};

class Contador
{
private:
    int mod;

public:
    int value;
    Contador(int modulo)
    {
        value = 0;
        mod = modulo;
    }
    void increment()
    {
        value++;
        if (value == mod)
        {
            value = 0;
        }
    }
    void reset()
    {
        value = 0;
    }
};

class Comparador
{
private:
    int element_1;
    int element_2;

public:
    int status;
    void setElement(int a, int b)
    {
        element_1 = a;
        element_2 = b;
        Use();
    }
    void Use()
    {
        if (element_1 > element_2)
        {
            status = 1;
        }
        else
        {
            status = 0;
        }
    }
};

class FlipFlop
{
private:
    led led_device;

public:
    int input;
    FlipFlop(gpio_Pin pin_led) : led_device(pin_led){};

    void use()
    {
        if (input == 1)
        {
            led_device.on();
        }
        else
        {
            led_device.off();
        }
    }

    void reset()
    {
        input = 0;
        led_device.off();
    }
};
