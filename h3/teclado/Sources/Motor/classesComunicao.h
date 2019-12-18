#include "classesDigitais.h"

class ControllerService
{
private:
    MotorDC motor;
    int mode;

public:
    Switch playPauseButton;
    Switch cancelButton;
    Switch eot;
    ControllerService(
        gpio_Pin pin_button_play_pause,
        gpio_Pin pin_button_cancel,
        tpm_Pin tmp_pin,
        gpio_Pin pin_left,
        gpio_Pin pin_right,
        gpio_Pin pin_eot) : playPauseButton(pin_button_play_pause), cancelButton(pin_button_cancel), motor(tmp_pin, pin_left, pin_right), eot(pin_eot)
    {
        mode = 1;
    }
    void motorState(int state)
    {
        if (state == 0)
        {
            motor.turnOff();
        }
        else if (state == 1)
        {
            motor.turnOn();
        }
    }
    void motorSpin(int spin)
    {
        if (spin == 0)
        {
            motor.spinClockWise();
        }
        else if (spin == 1)
        {
            motor.spinCounterClockWise();
        }
    }
    void motorSpeed(int speed)
    {
        if (speed == 0)
        {
            motor.speedLow();
        }
        else if (speed == 1)
        {
            motor.speedHigh();
        }
    }
};

class SignalService
{
private:
    led lamp;
    Buzzer buzzer;
    Switch door;

public:
    SignalService(gpio_Pin pin_lamp, gpio_Pin pin_sensor, gpio_Pin pin_buzzer) : lamp(pin_lamp), buzzer(pin_buzzer), door(pin_sensor)
    {
    }
    void activeBuzzer()
    {
        buzzer.activeBuzzer();
    };
    void turnLamp(int params){
    	lamp.off();
    	if(params==1){
    		lamp.on();
    	}

    };
    int readDoor()
    {
        return door.read();
    }
};

class SystemKeyService
{
private:
    SignalService signalService;
    ControllerService controllerService;
    led temp;
    bool play;
    bool door;
    int cancel;
    int eot;

public:
    SystemKeyService(
        gpio_Pin pin_button_play_pause,
        gpio_Pin pin_button_cancel,
        tpm_Pin tmp_pin,
        gpio_Pin pin_left,
        gpio_Pin pin_right,
        gpio_Pin pin_lamp,
        gpio_Pin pin_sensor,
        gpio_Pin pin_buzzer,
        gpio_Pin pin_temp,
        gpio_Pin pin_eot)
        : controllerService(pin_button_play_pause, pin_button_cancel, tmp_pin, pin_left, pin_right, pin_eot),
          signalService(pin_lamp, pin_sensor, pin_buzzer),
          temp(pin_temp)
    {

        play = 0;
        door = 0;
        cancel = 0;
    };
    void readAllInput()
    {
        // Door closed?
        if (signalService.readDoor() == 0)
        {
            // Door closed, check play button, button played pressed?
            if (controllerService.playPauseButton.isOn())
            {
                //If play, pause otherwise if pause, play
                play = !play;
            }
            door = 0;
        }
        else
        {
            door = 1;
        }

        // button cancel pressed?
        if (controllerService.cancelButton.isOn())
        {
            cancel = 1;
        }

        // end of temporization occurs?
        if (controllerService.eot.isOn())
        {
            eot = 1;
        };
    };

    void doService()
    {
        if (play)
        {
            turnOn();
            if (door)
            {
                temp.off();
            }
            else
            {
                temp.on();
            }
        }
        else
        {
            turnOff();
            temp.off();
        }

        if (door)
        {
            signalService.turnLamp(1);
        }
        else
        {
            signalService.turnLamp(0);
        }

        if (eot)
        {
            signalService.turnLamp(1);
            signalService.activeBuzzer();
            turnOff();
            temp.off();
            eot = 0;
            play = false;
        }

        if (cancel)
        {
            signalService.turnLamp(0);
            temp.off();
            turnOff();
            cancel = 0;
            play = false;
        }
    };
    void turnOn()
    {
        controllerService.motorState(1);
        controllerService.motorSpin(0);
        controllerService.motorSpeed(1);
    };
    void turnOff()
    {
        controllerService.motorState(0);
    };
};