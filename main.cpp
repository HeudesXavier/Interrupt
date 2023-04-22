#include "mbed.h"
#include "C12832.h"

InterruptIn joystickcenter(p14);
InterruptIn button(p9);
DigitalOut led(LED1);
DigitalOut flash(LED4);

C12832 lcd(p5, p7, p6, p8, p11);

volatile int flag = 0;                      // flag to signal that button is pressed

void flip() {
    led = !led;                             // toggles the led when the joystick button is pressed.
    flag = 1;                               // set flag when button is pressed
}

int main() {
    joystickcenter.rise(&flip);             // attach the function address to the rising edge
    button.mode(PullUp);                    // With this, no external pullup resistor needed
    button.rise(&flip);                     // attach the function address to the rising edge
    

    while (1) {                             // wait around, interrupts will interrupt this!
        flash = !flash;                     // turns LED4 on if off, off if on
        wait(0.25);                         // the instruction to wait for a quarter-second

        if (flag == 1) {                    // check if button is pressed
            lcd.cls();
            lcd.locate(0, 0);
            lcd.printf("Button pressed");
            flag = 0;                       // reset flag
        }
    }
}