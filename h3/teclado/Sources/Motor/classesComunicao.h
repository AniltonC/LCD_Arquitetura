#include "classesDigitais.h"
#include "../Classes/digital.h"
#include "../Classes/monitor.h"
#include "../Classes/devices.h"

class ControllerService
{
private:
    MotorDC motor;
    int mode;

public:
    Switch playPauseButton;
    Switch cancelButton;
    ControllerService(
        gpio_Pin pin_button_play_pause,
        gpio_Pin pin_button_cancel,
        tpm_Pin tmp_pin,
        gpio_Pin pin_left,
        gpio_Pin pin_right) : playPauseButton(pin_button_play_pause), cancelButton(pin_button_cancel), motor(tmp_pin, pin_left, pin_right)
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
    void turnLamp(int params)
    {
        lamp.off();
        if (params == 1)
        {
            lamp.on();
        }
    };
    int readDoor()
    {
        return door.read();
    }
};

class MonitorMotor
{
private:
    SignalService signalService;
    ControllerService controllerService;
    led temp;
    bool door_signal;
    MonitorLCD *LCD;
    bool operationData[3] = {0, 0, 0};
    Led fimLedServ = Led(gpio_PTB18);

public:
    bool cancel_signal;
    bool play_signal;
    MonitorMotor(
        gpio_Pin pin_button_play_pause,
        gpio_Pin pin_button_cancel,
        tpm_Pin tmp_pin,
        gpio_Pin pin_left,
        gpio_Pin pin_right,
        gpio_Pin pin_lamp,
        gpio_Pin pin_sensor,
        gpio_Pin pin_buzzer,
        gpio_Pin pin_temp,
        MonitorLCD *param_lcd)
        : controllerService(pin_button_play_pause, pin_button_cancel, tmp_pin, pin_left, pin_right),
          signalService(pin_lamp, pin_sensor, pin_buzzer),
          temp(pin_temp)
    {

        play_signal = 0;
        door_signal = 0;
        cancel_signal = 0;
        LCD = param_lcd;
    };
    void readAllInput()
    {
        // Door closed?
        if (signalService.readDoor() == 0)
        {
            // Door closed, check play button, button played pressed?
            if (controllerService.playPauseButton.isOn() || LCD->monMemory.enableBT)
            {
                //If play, pause otherwise if pause, play
                LCD->monMemory.enableBT = 0;
                play_signal = !play_signal;
            }
            door_signal = 0;
        }
        else
        {
            door_signal = 1;
        }

        // button cancel pressed?
        if (controllerService.cancelButton.isOn() || LCD->monMemory.cancelBT)
        {
            LCD->monMemory.cancelBT = 0;
            cancel_signal = 1;
        }
    };

    void doService()
    {
        if (play_signal)
        {
            if (!LCD->monMemory.isNothingOnTimer())
            {
                LCD->monMemory.setAction(play);
                turnOn();
                if (door_signal)
                    temp.off();

                else
                    temp.on();
            }
            else
                play_signal = false;
        }
        else
        {
            LCD->monMemory.setAction(pause);
            turnOff();
            temp.off();
        }

        if (door_signal)
        {
            signalService.turnLamp(1);
        }
        else
        {
            signalService.turnLamp(0);
        }
        /*
        if (LCD->monMemory.getFimLedAction())
        {
            LCD->monMemory.setAction(pause);
            signalService.turnLamp(1);
            signalService.activeBuzzer();
            turnOff();
            temp.off();
            play_signal = 0;
            LCD->monMemory.setIsFimTimer(0);
        }
*/
        if (!fimLedServ.getLed())
        {
            LCD->monMemory.setAction(pause);
            signalService.turnLamp(1);
            signalService.activeBuzzer();
            turnOff();
            temp.off();
            play_signal = 0;
            LCD->monMemory.setIsFimTimer(0);
        }

        if (cancel_signal)
        {
            LCD->monMemory.setCancelAction(cancel_signal);
            LCD->monMemory.setAction(pause);
            LCD->monMemory.setCookGeral(ed);
            signalService.turnLamp(0);
            temp.off();
            turnOff();
            cancel_signal = 0;
            play_signal = 0;
        }
        operationData[0] = {door_signal};
        operationData[1] = {play_signal};
        operationData[2] = {play_signal};
        LCD->monMemory.setOperGeral(operationData);
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

    void setActionMotor(bool param)
    {
        play_signal = param;
    }
};
