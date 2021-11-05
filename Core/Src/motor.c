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

MOTOR_HandleTypedef Motor1 = {};
MOTOR_HandleTypedef Motor2 = {};

MOTOR_Status motorInit(void)
{
    return MOTOR_OK;
}

void motorHandler(void)
{

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

MOTOR_Status motorSetSpeed(MOTOR_HandleTypedef *motor) // 0 - min ... 1000 - max
{
    return MOTOR_OK;
}

MOTOR_Status motorSetRotation(MOTOR_Direction rotation, MOTOR_HandleTypedef *motor)
{
    return MOTOR_OK;
}