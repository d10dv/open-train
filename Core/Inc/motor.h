/*
 * motor.h
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

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_
#include "main.h"
#include "config.h"

typedef struct
{
    char * name;
    GPIO_TypeDef* motorIn1Port;
    GPIO_TypeDef* motorIn2Port;
    TIM_TypeDef* TIM;
    uint32_t prevCallTime;
    uint16_t pwmCH;
    uint16_t maxPWM;
    uint16_t minPWM;
    uint16_t maxPower;
    uint16_t minPower;
    uint16_t motorIn1Pin;
    uint16_t motorIn2Pin;
    uint16_t PWM;
    uint16_t power;
    uint16_t currentPower;
    uint16_t rampDuration;
} MOTOR_HandleTypedef;

typedef enum
{
    FORWARD,
    REVERSE
} MOTOR_RotationEnum;

typedef enum
{
    MOTOR_OK,
    MOTOR_FAIL,
} MOTOR_StatusEnum;

typedef enum
{
    PWM_CH1,
    PWM_CH2,
    PWM_CH3,
    PWM_CH4
} MOTOR_pwmCHenum;

typedef uint16_t MOTOR_Status;
typedef uint16_t MOTOR_Direction;

extern MOTOR_HandleTypedef Motor1;
extern MOTOR_HandleTypedef Motor2;

void motorsHandler(void);

void motorHandler(MOTOR_HandleTypedef *motor);

void motorDebugPrint(char* str);

MOTOR_Status motorsInit(void);

MOTOR_Status motorInit(void);

MOTOR_Status motorStart(MOTOR_HandleTypedef *motor);

MOTOR_Status motorStop(MOTOR_HandleTypedef *motor);

MOTOR_Status motorEStop(MOTOR_HandleTypedef *motor);

MOTOR_Status motorSetSpeed(uint16_t setpoint, MOTOR_HandleTypedef *motor); // 0 - min ... 1000 - max

MOTOR_Status motorSetRotation(MOTOR_Direction rotation, MOTOR_HandleTypedef *motor);

void setPWMsetpoint (uint16_t setpoint, MOTOR_HandleTypedef *motor);

uint16_t  getMotorPWMSetpoint(uint16_t setpoint, MOTOR_HandleTypedef *motor);

#endif //__H_MOTOR__