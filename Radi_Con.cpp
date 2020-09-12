#include "Arduino.h"
#include "Radi_Con.h"

void Radi_con::set_condition(int R1_new, int R2_new, int L1_new, int L2_new, int R_duty_cycle_new, int L_duty_cycle_new)
{
    R1 = R1_new;
    R2 = R2_new;
    L1 = L1_new;
    L2 = L2_new;
    R_duty_cycle = R_duty_cycle_new;
    L_duty_cycle = L_duty_cycle_new;

    digitalWrite(R1_pin, R1);
    digitalWrite(R2_pin, R2);
    digitalWrite(L1_pin, L1);
    digitalWrite(L2_pin, L2);

    ledcWrite(R_pwm_chanel, R_duty_cycle);
    ledcWrite(L_pwm_chanel, L_duty_cycle);
}

int get_condition()
{
    if (R1 == HIGH && R2 == LOW && L1 == HIGH && L2 == LOW)
    {
        return 0;
    }
    else if(R1 == LOW && R2 == HIGH && L1 == LOW && L2 == HIGH)
    {
        return 1;
    }
    else if(R1 == HIGH && R2 == HIGH && L1 == HIGH && L2 == HIGH)
    {
        return 2;
    }
    else if(R1 == HIGH && R2 == HIGH && L1 == HIGH && L2 == HIGH)
    {
        return 3;
    }
    else if(R1 == HIGH && R2 == HIGH && L1 == HIGH && L2 == HIGH)
    {
        return 4;
    }
}

void Radi_con::set_wheel_move(int R1_new, int R2_new, int L1_new, int L2_new)
{
    set_condition(R1_new, R2_new, L1_new, L2_new, R_duty_cycle, L_duty_cycle);
}

void Radi_con::set_duty_cycle(int rn, int ln)
{
    set_condition(R1, R2, L1, L2, rn, ln);
}

void Radi_con::set_duty_cycle(int n)
{
    set_duty_cycle(n, n);
}

Radi_con::Radi_con(int R1_pin, int R2_pin, int R_pwm_pin, int L1_pin, int L2_pin, int L_pwm_pin)
    : R1_pin(R1_pin), R2_pin(R2_pin), L1_pin(L1_pin), L2_pin(L2_pin)
{
    ledcSetup(0, 490, 8);
    ledcSetup(1, 490, 8);
    ledcAttachPin(R_pwm_pin, 0);
    ledcAttachPin(L_pwm_pin, 1);
    R_pwm_chanel = 0;
    L_pwm_chanel = 1;

    pinMode(R1_pin, OUTPUT);
    pinMode(R2_pin, OUTPUT);
    pinMode(L1_pin, OUTPUT);
    pinMode(L2_pin, OUTPUT);

    set_duty_cycle(126);
    set_wheel_move(LOW, LOW, LOW, LOW);
}

void Radi_con::forward()
{
    set_wheel_move(HIGH, LOW, HIGH, LOW);
}

void Radi_con::back()
{
    set_wheel_move(LOW, HIGH, LOW, HIGH);
}

void Radi_con::brake()
{
    set_wheel_move(HIGH, HIGH, HIGH, HIGH);
}

void Radi_con::idle()
{
    set_wheel_move(LOW, LOW, LOW, LOW);
}

void Radi_con::turn_right()
{
    set_wheel_move(HIGH, LOW, HIGH, LOW);
    set_duty_cycle(255, 125);
}

void Radi_con::turn_left()
{
    set_wheel_move(HIGH, LOW, HIGH, LOW);
    set_duty_cycle(125, 255);
}

void Radi_con::nor(int n)
{
    set_duty_cycle(n);
}

void Radi_con::accelerate()
{
    if (R_duty_cycle < 245)
    {
        set_duty_cycle(R_duty_cycle + 10);
    }
}

void Radi_con::decelerate()
{
    if (R_duty_cycle > 10)
    {
        set_duty_cycle(R_duty_cycle - 10);
    }
}

void Radi_con::demo1()
{
}