/*
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

#include "cli.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "common.h"

#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))
#define MAX_COMMAND_LENGHT 32

uint8_t cliRxBuffer[APP_RX_DATA_SIZE] = {0};
uint8_t cliTxBuffer[APP_TX_DATA_SIZE] = {0};

#define CLI_COMMAND_DEF(name, description, args, cliCommand) \
    {                                                        \
        name,                                                \
            description,                                     \
            args,                                            \
            cliCommand                                       \
    }

const clicmd_t cliCmdTable[] = {
    CLI_COMMAND_DEF("status", "get current status", "[name]", cliGetStatus)};

void cliGet(const char *cmdName, const char *cmdline)
{
    cliPrint("Response");

    return;
}

void cliGetStatus(const char *cmdName, const char *cmdline)
{
    cliPrint("Ready");

    return;
}


void cliHandler(const char *cmdString)
{
    char command[MAX_COMMAND_LENGHT] = {0};

    sscanf(cmdString, "%s", command);

    const char *ptr = strchr(cmdString, ' ');

    for (uint8_t i = 0; i < sizeof(cliCmdTable) / sizeof(clicmd_t); i++)
    {
        if (!strcmp(command, cliCmdTable[i].name))
        {
            cliCmdTable[i].cliCommand(cmdString, ptr);

            return;
        }
    }

    cliPrint("Command not found");
}

void cliPrint(const char *printString)
{
    debugPrint(printString);
}

