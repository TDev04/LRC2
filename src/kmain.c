#include "rc2.h"
#include "drv.h"

#define bool unsigned char
void writeCharacter(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y)
{
     unsigned short int attrib = (backcolour << 4) | (forecolour & 0x0F);
     volatile unsigned short int * where;
     where = (volatile unsigned short int *)0xB8000 + (y * 80 + x) ;
     *where = c | (attrib << 8);
}


void writeString(char* str, unsigned char forecolour, unsigned char backcolour, int x, int y){
	while(*str){
		if(x == 80)
		{
			x = 0;
			y++;
		}
		writeCharacter(*str++, forecolour, backcolour, x, y);
		x++;
	}
}

unsigned char arrBytes[] = {
    0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
    0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80
};

void begin(bool boolval) {
    unsigned arrSize = sizeof(arrBytes);
    // calculate num of blocks
    int blocks = arrSize / BLOCK;
    if (arrSize % BLOCK != 0) {
        ++blocks;
    }

    if(boolval == 1) {
        for(int i = 0; i < blocks; i++) {
            encr(32, (unsigned int*)(&arrBytes[i * BLOCK]), key);
        }
    } else {
        for(int i = 0; i < blocks; i++) {
            decr(32, (unsigned int*)(&arrBytes[i * BLOCK]), key);
        }
    }
}

void kmain(){
    int arrsize = sizeof(arrBytes);
    writeString("Current array: ", 0x0F, 0x00, 0, 0);
    for(int i = 0; i < arrsize; i++) {
        writeCharacter(arrBytes[i], 0x0F, 0x00, 15 + i, 0);
    }

    begin(1); // decrypt

    writeString("Applyied decryption: ", 0x0F, 0x00, 0, 1);
    for(int i = 0; i < arrsize; i++) {
        writeCharacter((char)(arrBytes[i]), 0x0F, 0x00, 21 + i, 1);
    }

    // 33554430
    // a * 100 / 33554430 = b
    
    while(1) {
        asm("hlt");
    }
}