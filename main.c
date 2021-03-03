#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

uint16_t crc(uint8_t msg[], uint8_t len)
{
    uint16_t reg = 0;
    len = len + PADDING; // Message length + added bytes

    for (uint8_t pos = 0; pos < len; pos++)
    {
        for (uint8_t bit = 0; bit < BITS; bit++)
        {
            reg <<= 1;

            if ((msg[pos] & (LSB << bit)))
                reg ^= LSB;

            if (reg & MSB)
                reg ^= POLY;
        }
    }
    return reg;
}

uint8_t reverse(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

int main(void)
{
    uint8_t message[MSG_LENGTH_MAX + PADDING] = {0};
    fgets(message, sizeof(message), stdin);

    uint8_t len = strlen(message) - 1;
    message[len] = '\0';

    if (len)
    {
        uint16_t checksum = crc(message, len);

        // Append REVERSED Bytes
        message[len] = reverse(checksum >> 8);
        message[len + 1] = reverse(checksum & 0x00FF);

        //Check, alter message and check again
        printf("\n Data is%s Ok", crc(message, len) ? " not" : "");
        message[1] = 'a';
        printf("\n Data is%s Ok", crc(message, len) ? " not" : "");
    }

    return 0;
}