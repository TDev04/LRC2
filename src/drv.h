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
