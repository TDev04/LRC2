#define uint32_t unsigned int
#define uint16_t unsigned short int
#define uint8_t unsigned char

void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void outw(uint16_t port, uint16_t val)
{
    asm volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

void outl(uint16_t port, uint32_t val)
{
    asm volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
	uint8_t ret;
    asm volatile ("inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));
    return ret;
}

uint16_t inw(uint16_t port)
{
	uint16_t ret;
    asm volatile ("inw %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));
    return ret;
}

uint32_t inl(uint16_t port)
{
	uint32_t ret;
    asm volatile ("inl %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));
    return ret;
}

// small wait interval between 1-4ms
void io_wait(void)
{
    outb(0x80, 0);
}

void clear(int sector) {
    outb(0x1F2, 0x00);       // mov	dx, 1F2h; mov	al, 2 ; sector number; out	dx,al
    outb(0x1F3, sector + 1); // inc	dx; out	dx,al
    outb(0x1F4, 0x00);       // inc	dx; xor	ax,ax; out	dx,al
    outb(0x1F5, 0x00);       // inc	dx; out	dx,al
    outb(0x1F6, 0xA0);       // mov	al, 10100000b; inc	dx; out	dx,al
    outb(0x1F7, 0x30);       // inc	dx; mov	al,30h; out	dx,al
    uint16_t *buffer = (uint16_t *)0xC000; // lea	si, [0c000h]
    uint16_t port = 0x1F0;   // mov	dx, 1F0h
    int i;
    for (i = 0; i < 512; i++) {
        outw(port, buffer[i]); // mov	cx, 512; rep	outsw
    }
    return;                  // ret
}
