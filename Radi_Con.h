#ifndef Radi_Con_h
#define Radi_Con_h

class Radi_con
{
    //pin_number
    int R1_pin, R2_pin, L1_pin, L2_pin;

    //chanel converted from pin num
    int R_pwm_chanel, L_pwm_chanel;

    //HIGH or LOW
    int R1, R2, L1, L2;

    //duty cycle
    int R_duty_cycle, L_duty_cycle;

    //helper func
    void set_condition(int R1_new, int R2_new, int L1_new, int L2_new, int R_duty_cycle_new, int L_duty_cycle_new);
    void set_wheel_move(int R1_new, int R2_new, int L1_new, int L2_new);
    void set_duty_cycle(int rn, int ln);
    void set_duty_cycle(int n);
    int get_condition();

public:
    //constructer 
    Radi_con(int R1, int R2, int R_pwm_pin, int L1, int L2, int L_pwm_pin);

    //move
    void forward();
    void back();
    void brake();
    void idle();
    void turn_right();
    void turn_left();

    //velocity
    void accelerate();
    void decelerate();

    //extra
    void demo1();
};

#endif