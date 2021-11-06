/*
 * motor.c
 *
 *	Copyright 2019 Denis Davydov
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *limitations under the License.
 */

#include "motor.h"
#include "tim.h"
#include "config.h"
#include <stdio.h>

MOTOR_HandleTypedef Motor1 = {};
MOTOR_HandleTypedef Motor2 = {};

MOTOR_Status motorInit(void)
{
    return MOTOR_OK;
}

MOTOR_Status motorsInit(void)
{
    Motor1.name = "M1";
    Motor1.TIM = TIM3;
    Motor1.pwmCH = PWM_CH1;
    Motor1.motorIn1Port = M1_IN1_GPIO_Port;
    Motor1.motorIn2Port = M1_IN2_GPIO_Port;
    Motor1.motorIn1Pin = M1_IN1_Pin;
    Motor1.motorIn2Pin = M1_IN2_Pin;
    Motor1.maxPWM = MAX_PWM;
    Motor1.minPWM = MIN_PWM;
    Motor1.maxPower = MAX_MOTOR_POWER;
    Motor1.minPower = MIN_MOTOR_POWER;

    Motor2.name = "M2";
    Motor2.TIM = TIM3;
    Motor2.pwmCH = PWM_CH2;
    Motor2.motorIn1Port = M2_IN1_GPIO_Port;
    Motor2.motorIn1Port = M2_IN2_GPIO_Port;
    Motor2.motorIn1Pin = M2_IN1_Pin;
    Motor2.motorIn2Pin = M2_IN2_Pin;
    Motor2.maxPWM = MAX_PWM;
    Motor2.minPWM = MIN_PWM;
    Motor2.maxPower = MAX_MOTOR_POWER;
    Motor2.minPower = MIN_MOTOR_POWER;

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

    motorSetSpeed(0, &Motor1);
    motorSetSpeed(0, &Motor2);

    return MOTOR_OK;
}

void motorsHandler()
{
    static power = 0;

    motorHandler(&Motor1);
    motorHandler(&Motor2);

    HAL_Delay(100);
    power++;
    if (power > 1000)
        power = 0;

    motorSetSpeed(power, &Motor1);
    motorSetSpeed(power, &Motor2);

    // TIM3->CCR1 = (uint16_t)MAX_PWM/2;
    // TIM3->CCR2 = (uint16_t)MAX_PWM/2;

    // TIM3->CCR1 = (uint16_t)MAX_PWM/2;
    // TIM3->CCR2 = (uint16_t)MAX_PWM/2;
}

void motorHandler(MOTOR_HandleTypedef *motor)
{
    setPWMsetpoint(getMotorPWMSetpoint(motor->power, motor), motor);
}

MOTOR_Status motorStart(MOTOR_HandleTypedef *motor)
{
    return MOTOR_OK;
}

MOTOR_Status motorStop(MOTOR_HandleTypedef *motor)
{
    return MOTOR_OK;
}

MOTOR_Status motorEStop(MOTOR_HandleTypedef *motor)
{
    return MOTOR_OK;
}

MOTOR_Status motorSetSpeed(uint16_t setpoint, MOTOR_HandleTypedef *motor) // 0 - min ... 1000 - max
{
    if (motor->power == setpoint)
        return MOTOR_OK;

    if (setpoint >= motor->maxPower)
    {
        setpoint = motor->maxPower;
    };
    if (setpoint <= motor->minPower)
    {
        setpoint = motor->minPower;
    };

    motor->power = setpoint;

#ifdef DEBUG
    char str[80];
    sprintf(str, "%s : %s -> %u", motor->name, "set setpoint", motor->power);
    debugPrint(str);
#endif

    return MOTOR_OK;
}

MOTOR_Status motorSetRotation(MOTOR_Direction rotation, MOTOR_HandleTypedef *motor)
{
    switch (rotation)
    {
    case FORWARD:
        /* code */
        break;

    case REVERSE:
        /* code */
        break;

    default:
        break;
    }

    return MOTOR_OK;
}

uint16_t getMotorPWMSetpoint(uint16_t setpoint, MOTOR_HandleTypedef *motor)
{
    uint16_t pwmSetpoint = (uint16_t)(setpoint * (motor->maxPWM - motor->minPWM) / (motor->maxPower - motor->minPower) + motor->minPWM);

    return pwmSetpoint;
}

void setPWMsetpoint(uint16_t setpoint, MOTOR_HandleTypedef *motor)
{
    if (motor->PWM == setpoint)
        return MOTOR_OK;

    motor->PWM = setpoint;

    switch (motor->pwmCH)
    {
    case PWM_CH1:
        motor->TIM->CCR1 = motor->PWM;
        break;

    case PWM_CH2:
        motor->TIM->CCR2 = motor->PWM;
        break;

    case PWM_CH3:
        motor->TIM->CCR3 = motor->PWM;
        break;

    case PWM_CH4:
        motor->TIM->CCR4 = motor->PWM;
        break;

    default:
        break;
    }

#ifdef DEBUG
    char str[80];
    sprintf(str, "%s : %s -> %u", motor->name, "PWM setpoint", motor->PWM);
    debugPrint(str);
#endif
}

void motorDebugPrint(char *str)
{
}