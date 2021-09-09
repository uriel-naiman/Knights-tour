/******************************************************************
* File Name: bit_array.h										  *
* Name: Uriel Naiman											  *
* Topic: Bit Array C file										  *
*******************************************************************/
#include <stddef.h>	/* size_t */

#define BITS_IN_WORD (sizeof(size_t) * 8)
#define BITS_IN_BYTE 8
#define BYTES_IN_WORD (sizeof(size_t))

typedef size_t bit_array_t; 

bit_array_t BitArrSetAll(bit_array_t arr)
{
	return (arr | (~0));
}

bit_array_t BitArrResetAll(bit_array_t arr)
{
	return (arr & 0);
}

bit_array_t BitArrSetOn(bit_array_t arr, size_t index)
{
	return (arr | ((size_t)1 << (index - 1)));
} 

bit_array_t BitArrSetOff(bit_array_t arr, size_t index)
{
	return (arr & (((size_t)(~0)) ^ ((size_t)1 << (index - 1))));
}

bit_array_t BitArrSetBit(bit_array_t arr, size_t index, int 
boolean_value)
{
	return ( (0 == boolean_value) ? BitArrSetOff(arr, index) : 
	BitArrSetOn(arr, index) );
}

bit_array_t BitArrFlip(bit_array_t arr, size_t index)
{
	return (arr ^ ((size_t)(1 << (index - 1))));
}

int BitArrIsOn(bit_array_t arr, size_t index)
{
	return ( (arr & ((size_t)1 << (index - 1))) ? 1 : 0 );
}

int BitArrIsOff(bit_array_t arr, size_t index)
{
	return ( (arr & ((size_t)1 << (index - 1))) ? 0 : 1 );
}

bit_array_t BitArrRotR(bit_array_t arr, size_t num_to_shift)
{
	size_t temp = arr;
	
	if (num_to_shift > BITS_IN_WORD)
	{
		num_to_shift %= BITS_IN_WORD;
	}
	arr >>= num_to_shift;
	temp <<= (BITS_IN_WORD - num_to_shift);
	return (arr | temp);
}
	
bit_array_t BitArrRotL(bit_array_t arr, size_t num_to_shift)
{
	size_t temp = arr | 0;
	
	if (num_to_shift > BITS_IN_WORD)
	{
		num_to_shift %= BITS_IN_WORD;
	}
	arr <<= num_to_shift;
	temp >>= (BITS_IN_WORD - num_to_shift);
	return (arr | temp);
}

size_t BitArrCountOn(bit_array_t arr)
{
	int count_bits = 0;
		
	while (arr)
	{
		arr &= (arr-1);
		++count_bits;
	}
	return (count_bits);
}

size_t BitArrCountOnLUT(bit_array_t arr)
{
	static unsigned char init_flag = 0;
	static unsigned char count_on_lut[256] = {'0'};
	unsigned char mask = 0xFF;
	unsigned char curr_byte = 0;
	size_t i = 0;
	size_t sum = 0;

	if(0 == init_flag)
	{
		for(i = 0; i < 256; ++i)
		{
			count_on_lut[i] = BitArrCountOn(i);
		}
		init_flag = 1;
	}
	
	for(i = 0; i < 8; ++i)
	{
		curr_byte = (mask & arr);
		sum += count_on_lut[curr_byte];
		arr >>= BITS_IN_BYTE;
	}
	
	return (sum);
}

size_t BitArrCountOff(bit_array_t arr)
{
	int count_bits = 0;
		
	while (arr)
	{
		arr &= (arr-1);
		++count_bits;
	}
	return (BITS_IN_WORD - count_bits);
}

bit_array_t BitArrMirror(bit_array_t arr)
{
	char *num = (char*)&arr;
	char *temp_num = num;
	unsigned int i = 0;
	
	for (i = 0; 8 > i; ++i)
	{
		*num = ((*num & 0x0f) << 7)
		| ((*num & 0x02) << 5)
		| ((*num & 0x04) << 3)
		| ((*num & 0x08) << 1)
		| ((*num & 0x10) >> 1)
		| ((*num & 0x20) >> 3)
		| ((*num & 0x40) >> 5)
		| ((*num & 0x80) >> 7);
		++num;
	}
	 --num;
		
	for (i = 0; (BYTES_IN_WORD/2) > i; ++i)
	{
		char temp = *num;
		*num = *temp_num;
		*temp_num = temp;
		--num;
		++temp_num;
	}
	
	num -= (BYTES_IN_WORD / 2 - 1);
	arr = *(size_t*)num;
	return (arr);
}

static char ByteMirror(int num)
{
	num = ((num & 0x0f) << 7)
	| ((num & 0x02) << 5)
	| ((num & 0x04) << 3)
	| ((num & 0x08) << 1)
	| ((num & 0x10) >> 1)
	| ((num & 0x20) >> 3)
	| ((num & 0x40) >> 5)
	| ((num & 0x80) >> 7);
	
	return (*(char*)(&num));
}

bit_array_t BitArrMirrorLUT(bit_array_t arr)
{

	static unsigned char init_flag = 0;
	static unsigned char mirror_lut[256] = {'0'};
	unsigned char mask = 0XFF;
	unsigned char curr_byte = 0;
	size_t mirrored_word = 0;
	size_t i = 0;

	if (0 == init_flag)
	{
		for(i = 0; 256 > i; ++i)
		{
			mirror_lut[i] = ByteMirror(i);
		}
		init_flag = 1;
	}
		
	for (i = 0; (BYTES_IN_WORD - 1) > i; ++i)
	{
		curr_byte = (mask & arr);
		mirrored_word += mirror_lut[curr_byte];
		mirrored_word <<= BITS_IN_BYTE;
		arr >>= BITS_IN_BYTE;
	}
	
	return (mirrored_word);
}

char *BitArrToString(bit_array_t arr, char *dest)
{
	size_t mask = 0x8000000000000000;
	int i = 0;
	char *temp = dest;
	
	for(i = 0; 64 > i; ++i)
	{
		(arr & mask) ? (*temp = '1') : (*temp = '0');
		arr <<= 1;
		++temp;
	}
	*temp = '\0';
	
	return (dest);
}

