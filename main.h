#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdint.h>

#define POLY 0xC599U // The CAN protocol uses the CRC-15 with this polynomial
#define MSG_LENGTH_MIN 1
#define MSG_LENGTH_MAX 14
#define PADDING 2 //15 bits

#define BITS 8
#define MSB 0x8000U
#define LSB 0x01U

/**
 * @brief Calculates crc, also checks crc if return is 0, crc check good!
 * 
 * @param msg 
 * @param len 
 * @return uint16_t 
 */
uint16_t crc(uint8_t msg[], uint8_t len);
/**
 * @brief Reverse a byte. ie 01000001 => 10000010
 * 
 * @param b 
 * @return uint8_t 
 */
uint8_t reverse(uint8_t b);
#endif