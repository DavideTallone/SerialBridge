//--------------------------------------------------
//
//Copyright Narda Safety Test Solution
//
//--------------------------------------------------

/**
 *
 *	Utils.h for project ER9000
 *	This is the header file for Utils.c
 *
 *	Date 03/04/2020
 *	Author Davide Tallone
 *	Ver. 1.0
 *	Platform agnostic
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef _WIN32

#define SECTION(...) section(__VA_ARGS__)
//#define DEBUG
#else
#define DEBUG
//#define SECTION(...)
#endif



#define UTILS_OK 	(1)
#define UTILS_KO 	(0)
#define XOR			0
#define MOD_256		1
#define COMP_2		2
#define DET_NOT_AVAILABLE (0xC000)

#define str(x) #x
#define VarNameToString(x) str(x)	//extract the variable name and return it as a string of character

#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)
#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define IS_CONTAINED_IN(n,x,y) ((x) < (n) && (y) > (n) ? 1 : 0)
#define IS_CONTAINED_IN_EXTREME(n,x,y) ((x) <= (n) && (y) >= (n) ? 1 : 0)
#define DIMENSION_OF(a)    (sizeof(a) / sizeof(a[0]))
#define BIT_TO_MASK(bit)   (1u << bit)
#define BIT_TO_MASK8(bit)  (uint8_t)(1u << bit)
#define BIT_TO_MASK16(bit) (uint16_t)(1u << bit)
#define BIT_TO_MASK32(bit) (uint32_t)(1u << bit)
#define BIT_TO_MASK64(bit) (uint64_t)(1u << bit)


#define UINT32_BYTE3(w)    ((w >> 24) & 0x00FF)
#define UINT32_BYTE2(w)    ((w >> 16) & 0x00FF)
#define UINT32_BYTE1(w)    ((w >>  8) & 0x00FF)
#define UINT32_BYTE0(w)    ((w      ) & 0x00FF)

#define BYTE0(b)           ((uint32_t)(b)& 0xFF000000)
#define BYTE1(b)           ((uint32_t)(b)& 0x00FF0000)
#define BYTE2(b)           ((uint32_t)(b)& 0x0000FF00)
#define BYTE3(b)           ((uint32_t)(b)& 0x000000FF)

#define BYTE0_TO_UINT32(b) (((uint32_t)(b) << 24)& 0xFF000000)
#define BYTE1_TO_UINT32(b) (((uint32_t)(b) << 16)& 0x00FF0000)
#define BYTE2_TO_UINT32(b) (((uint32_t)(b) <<  8)& 0x0000FF00)
#define BYTE3_TO_UINT32(b) (((uint32_t)(b)      )& 0x000000FF)

/*print debug information formatted as "(APP)(ERR) [Function wher error was triggered] [Code line that triggered the print]"*/
#ifdef DEBUG
#define DBG_ERR(...)            do{printf("(APP)(ERR)[%s][%d]",__FUNCTION__,__LINE__); printf(__VA_ARGS__);printf("\r");}while(0)
#define DBG_CHECKPT(...)        do{printf("\033[0;32m%(APP)(CKP) reached [%s]\033[0m",__FUNCTION__);printf("\r");}while(0)
#define DBG_GENERAL(...)        do{printf("(APP)(GEN)"); printf(__VA_ARGS__);printf("\r");}while(0)
#else
#define DBG_ERR(...)
#define DBG_CHECKPT(...)
#define DBG_GENERAL(...)
#endif

#ifndef _WIN32
void 	UTILS_DECtoASCII	(int value, char *str);
int * 	UTILS_ASCIIParser 	(char *buf, int len);
int 	UTILS_HEX_to_ASCIIstring(uint8_t data,char *str);
int 	UTILS_HEXtoASCII	(int value);
int 	UTILS_CheckSum8		(uint8_t* data,size_t numOfElements,uint8_t* checksum,uint8_t checksumType);
int 	UTILS_toBigEndian	(char firstChar,char secondChar);
int 	UTILS_toSmallEndian	(char firstChar,char secondChar);
char 	UTILS_getRandom		(void);
#endif

uint64_t UTILS_power(int base, unsigned int exp);
#endif //__RFMODULEMANAGER_H__

