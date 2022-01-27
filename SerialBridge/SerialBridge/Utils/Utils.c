//--------------------------------------------------
//
//Copyright Narda Safety Test Solution
//
//--------------------------------------------------

/**
 *
 *	Utils.c for project ER9000
 *
 *	A file that contains the code for functions of general
 *	usage.
 *
 *	Date 03/04/2020
 *	Author Davide Tallone
 *	Ver. 0.1
 *	Platform agnostic
 *
 */

#include "Utils.h"

int * UTILS_ASCIIParser(char* ASCIIString,int len){
    //this function is used to convert a a string of a ginven len into
    //a set of number. Said number are represented in the ascii string, separated by either ';' or ':'.
    //any non numeric char will be ignored


    int i,c=0;
    static int parsedValue[7];  //modify to enable the conversion of more number
    bool isNegative=false;
    parsedValue[0]=DET_NOT_AVAILABLE;
    parsedValue[1]=DET_NOT_AVAILABLE;
    parsedValue[2]=DET_NOT_AVAILABLE;
    parsedValue[3]=DET_NOT_AVAILABLE;
    parsedValue[4]=DET_NOT_AVAILABLE;
    parsedValue[5]=DET_NOT_AVAILABLE;
    parsedValue[6]=0; //number of det available
	short int multiplier=10;
    for (i=0; i<len && c<=(sizeof(parsedValue)/sizeof(int)-1);i++){

        switch (ASCIIString[i]) {
        case '0': case '1' :case '2':case '3': case '4' :case '5':case '6': case '7' :case '8':case '9':
        	if(parsedValue[c]==DET_NOT_AVAILABLE){parsedValue[c]=0;}
            parsedValue[c]=multiplier*parsedValue[c]+ASCIIString[i]-'0';
            break;
        case ';':case ':' :
            if(isNegative){
            	parsedValue[c]*=(-1);}
            isNegative=false;
            if(parsedValue[c]!=-DET_NOT_AVAILABLE){
            	parsedValue[6]|=(1<<c);
            }

        	c++;
            break;
        case '-':
        	isNegative=true;
        	break;
        default:
            break;

        }

    }
    return parsedValue;

}

/**
 * @file Utils.c
 * @author Davide Tallone
 *  @date   19/02/2019
 *  \~english @brief Functions for the conversion of data from/to ASCII
 *  \~italian @brief  funzioni per la conversione da/a e viceversa di valori decimali e caratteri ASCII
 */

void UTILS_DECtoASCII(int bin, char* ASCIIString) {


    int integer,pow;
    int i,remainder;
    char TempArray[10];
    memset(TempArray, 0, sizeof(TempArray));
    i=0;
    if(bin<0){
        bin=bin*(-1);
        TempArray[0]=0x2D;
        i++;
    }

    pow=1;
    integer=bin;

    while (integer%pow != bin){         //calculate the exponent
        pow*=10;

    }
    pow=pow/10;

    while (pow>=1){
        remainder=integer-integer%pow;
        TempArray[i]=UTILS_HEXtoASCII (remainder/pow);
        pow=pow/10;
        integer=integer-remainder;
        i++;

    }
    memset(ASCIIString, 0, sizeof(ASCIIString));
    strcat(ASCIIString,TempArray);

    //if (P2OUT & BIT0){ strcat(ASCIIString,"H");}

}

/**
 * @file Utils.c
 * @author Davide Tallone
 *  @date   19/02/2019
 *  \~english @brief Functions for the conversion of data from/to ASCII
 *  \~italian @brief  funzioni per la conversione da/a e viceversa di valori decimali e caratteri ASCII
 */

int UTILS_HEXtoASCII(int c){
    //A simple function for translating an hexadecimal int to an ascii character
    const char HEXString[16]="0123456789ABCDEF";
    return HEXString[c];
}

/**
 * @file Utils.c
 * @author Davide Tallone
 *  int UTILS_toBigEndian(char firstChar,char secondChar)
 *
 *  \~english @brief Combine two 8 bit value into a Big endian 16 bit variable
 *  \~italian @brief Crea un valore a 16 bit big endian partenda da due valori a otto bit
 *	\return int temp The combined values of the two parameters (format 0xaabb) where
 *			firstChar is 0xaa and secondChar is 0xbb.
 */
int UTILS_toBigEndian(char firstChar,char secondChar){
	int combined;
	combined=firstChar&0xFF;
	combined<<=8;
	combined|=secondChar&0xFF;

	return combined;
}

/**
 * @file Utils.c
 * @author Davide Tallone
 *  int UTILS_toSmallEndian(char firstChar,char secondChar)
 *
 *  \~english @brief Combine two 8 bit value into a Big endian 16 bit variable
 *  \~italian @brief Crea un valore a 16 bit big endian partenda da due valori a otto bit
 *	\return int temp The combined values of the two parameters (format 0xbbaa) where
 *			firstChar is 0xaa and secondChar is 0xbb.
 */

int UTILS_toSmallEndian(char firstChar,char secondChar){
	int combined=0;
	combined=secondChar&0xFF;
	combined<<=8;
	combined|=firstChar&0xFF;

	return combined;
}

/**
 * @file Utils.c
 * @author Davide Tallone
 *  int UTILS_CheckSum8(uint8_t *data,size_t numOfElements,uint8_t *checksum,uint8_t checksumType)
 *
 *  \~english @brief Calculate the 8 bit checksum of an array.
 *  \~italian @brief Calcola il checksum 8 di un array di dati
 *	\param	uint8_t *data Pointer to the array of data wich checksum will be calculated
 *	\param	size_t numOfElements 	Number of elements to be considered for the checksum calculation
 *	\param 	uint8_t *checksum pointer to the location where the checksum value will be stored
 *	\param	uint8_t checksumType possible values :XOR (0);MOD_256(1);COMP_2(2);
 *	\return int one if no error
 *
 */

int UTILS_CheckSum8(uint8_t *data,size_t numOfElements,uint8_t *checksum,uint8_t checksumType){
	size_t i=0;
	uint16_t tmp=0;
	for(i=0;i<numOfElements;i++){
		tmp+=*(data+i);
	}
	switch(checksumType){
		case XOR:
			*checksum=((tmp>>8)&0x00FF)^(tmp&0x00FF);
		break;
		case MOD_256:
			*checksum=tmp%0x100;
		break;
		case COMP_2:
			tmp^=0xFFFF;
			tmp+=1;
			*checksum=tmp&0xFF;
		break;
		default:
		return UTILS_KO;
		break;
	}


	return UTILS_OK;
}

/**
 * @file Utils.c
 * @author Davide Tallone
 *  UTILS_HEX_to_ASCIIstring(uint8_t data,char* string)
 *
 *  \~english @brief Create a string from a byte.
 *  \~italian @brief Crea una stringa da un byte.
 *	\param	uint8_t data Byte used for the calculation
 *	\param	char* string String that will contains the two letters
 *	\return int one if no error
 *			for example, by passing 0xA5 as data, this function will put "A5" in string.
 */
int UTILS_HEX_to_ASCIIstring(uint8_t data,char* string){
	if(sizeof(string)<2){return UTILS_KO;}
	char table[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	string[0]=table[((data>>4)&0x0F)];
	string[1]=table[(data&0xF)];
	return UTILS_OK;

}

 /**
 * @file Utils.c
 * uint64_t UTILS_power(int base, unsigned int exp)
 *
 *  \~english @brief Given base and exponent, return the power
 *	\param	int base
 *	\param	unsigned int exp
 *	\return uint64_t base^(exp)
 *
 */


uint64_t UTILS_power(int base, unsigned int exp){

    if (exp == 0)  { return 1; }
    uint64_t temp = UTILS_power(base, exp/2);
    if (exp%2 == 0){  return temp*temp; }
    else { return base*temp*temp; }

}
