//[open streaming]
#define END_    0xff

unsigned char mt9v136regs0[]=
{
0xC8,0x16,0x00,0x83, 
0xC8,0x18,0x00,0x9D, 
0xC8,0x1A,0x00,0x01,//0x18, 
0xC8,0x1C,0x00,0x01,//0x14, 
0x00,0x40,0x80,0x02,
			//delay = 30
0xC8,0x1E,0x00,0x03, 
0xC8,0x20,0x00,0x02, 
0xC9,0x16,0x01,0x09, 
0xC9,0x18,0x06,0x2C, 
0xC8,0x50,0x03,0x42, 
0xC8,0xF4,0x00,0x04, 
0xC8,0xF8,0x00,0x82, 
			//delay = 30
0x00,0x30,0x04,0x04, 
0x00,0x30,0x04,0x04, 
0x30,0x1A,0x10,0xD0, 
0x31,0xC0,0x14,0x04, 
0x3E,0xD8,0x87,0x9C, 
0x30,0x42,0x20,0xE1, 
0x30,0xD4,0x80,0x20, 
0x30,0xC0,0x00,0x26, 
0x30,0x1A,0x10,0xD4,
0xA8,0x02,0x00,0xD3, 
0xC8,0x78,0x00,0xA0, 
0xC8,0x76,0x01,0x40, 
0xBC,0x04,0x00,0xFC, 
0xBC,0x38,0x00,0x7f, 
0xBC,0x3A,0x00,0xbf,	
0xBC,0x3C,0x00,0xbf, 
0xBC,0x04,0x00,0xFc,	
0xC9,0x1A,0x00,0x0F, 
0xC9,0x1C,0x00,0x06, 
0xC8,0xFC,0x00,0x0C, 
0xC8,0xFE,0x00,0x30, 
0xC9,0x12,0x00,0x0C, 
0xC9,0x14,0x00,0x4B, 
0xC9,0x16,0x01,0x09, 
0xC9,0x18,0x06,0x2C, 
0xC9,0x07,0xA8,0x01, 
0xC9,0x0A,0x14,0x14, 
0xC9,0x0C,0x14,0x14, 
0xC9,0x0E,0x32,0x32, 
0xC9,0x10,0x32,0x32, 
0xC9,0x1E,0x01,0xF4, 
0xC9,0x20,0x27,0x10,
0xC9,0x00,0x80,0x4a, 
0xC9,0x04,0x08,0x02,  
0xC9,0x06,0x02,0xa8,  
0xC9,0x08,0x07,0x7f,  
0xBC,0x06,0x01,0x5E, 
0xC8,0xE6,0x80,0x80, 
0xC8,0x3E,0x00,0x01, 
0x32,0x80,0x00,0xAA, 
0xC9,0x16,0x01,0x09, 
0xC9,0x18,0x06,0x2C, 
0xC8,0xCE,0x33,0xA1, 
0xC8,0xD0,0xEC,0x08, 
0xC8,0xD2,0xFF,0xC0, 
0xC8,0xDE,0x00,0x33, 
0x00,0x40,0x80,0x02, 
			//delay = 30
0x09,0x82,0x00,0x01, 
0x09,0x8A,0x70,0x00, 
0xF0,0x00,0x72,0xCF, 
0xF0,0x02,0xFF,0x00, 
0xF0,0x04,0x3E,0xD0, 
0xF0,0x06,0x92,0x00, 
0xF0,0x08,0x71,0xCF, 
0xF0,0x0A,0xFF,0xFF, 
0xF0,0x0C,0xF2,0x18, 
0xF0,0x0E,0xB1,0x10, 
0xF0,0x10,0x92,0x05, 
0xF0,0x12,0xB1,0x11, 
0xF0,0x14,0x92,0x04, 
0xF0,0x16,0xB1,0x12, 
0xF0,0x18,0x70,0xCF, 
0xF0,0x1A,0xFF,0x00, 
0xF0,0x1C,0x30,0xC0, 
0xF0,0x1E,0x90,0x00, 
0xF0,0x20,0x7F,0xE0, 
0xF0,0x22,0xB1,0x13, 
0xF0,0x24,0x70,0xCF, 
0xF0,0x26,0xFF,0xFF, 
0xF0,0x28,0xE7,0x1C, 
0xF0,0x2A,0x88,0x36, 
0xF0,0x2C,0x09,0x0F, 
0xF0,0x2E,0x00,0xB3, 
0xF0,0x30,0x69,0x13, 
0xF0,0x32,0xE1,0x80, 
0xF0,0x34,0xD8,0x08, 
0xF0,0x36,0x20,0xCA, 
0xF0,0x38,0x03,0x22, 
0xF0,0x3A,0x71,0xCF, 
0xF0,0x3C,0xFF,0xFF, 
0xF0,0x3E,0xE5,0x68, 
0xF0,0x40,0x91,0x35, 
0xF0,0x42,0x22,0x0A, 
0xF0,0x44,0x1F,0x80, 
0xF0,0x46,0xFF,0xFF, 
0xF0,0x48,0xF2,0x18, 
0xF0,0x4A,0x29,0x05, 
0xF0,0x4C,0x00,0x3E, 
0xF0,0x4E,0x12,0x22, 
0xF0,0x50,0x11,0x01, 
0xF0,0x52,0x21,0x04, 
0xF0,0x54,0x0F,0x81, 
0xF0,0x56,0x00,0x00, 
0xF0,0x58,0xFF,0xF0, 
0xF0,0x5A,0x21,0x8C, 
0xF0,0x5C,0xF0,0x10, 
0xF0,0x5E,0x1A,0x22, 
0xF0,0x60,0x10,0x44, 
0xF0,0x62,0x12,0x20, 
0xF0,0x64,0x11,0x02, 
0xF0,0x66,0xF7,0x87, 
0xF0,0x68,0x22,0x4F, 
0xF0,0x6A,0x03,0x83, 
0xF0,0x6C,0x1A,0x20, 
0xF0,0x6E,0x10,0xC4, 
0xF0,0x70,0xF0,0x09, 
0xF0,0x72,0xBA,0xAE, 
0xF0,0x74,0x7B,0x50, 
0xF0,0x76,0x1A,0x20, 
0xF0,0x78,0x10,0x84, 
0xF0,0x7A,0x21,0x45, 
0xF0,0x7C,0x01,0xC1, 
0xF0,0x7E,0x1A,0x22, 
0xF0,0x80,0x10,0x44, 
0xF0,0x82,0x70,0xCF, 
0xF0,0x84,0xFF,0x00, 
0xF0,0x86,0x3E,0xD0, 
0xF0,0x88,0xB0,0x60, 
0xF0,0x8A,0xB0,0x25, 
0xF0,0x8C,0x7E,0xE0, 
0xF0,0x8E,0x78,0xE0, 
0xF0,0x90,0x71,0xCF, 
0xF0,0x92,0xFF,0xFF, 
0xF0,0x94,0xF2,0x18, 
0xF0,0x96,0x91,0x12, 
0xF0,0x98,0x72,0xCF, 
0xF0,0x9A,0xFF,0xFF, 
0xF0,0x9C,0xE7,0x1C, 
0xF0,0x9E,0x8A,0x57, 
0xF0,0xA0,0x20,0x04, 
0xF0,0xA2,0x0F,0x80, 
0xF0,0xA4,0x00,0x00, 
0xF0,0xA6,0xFF,0xF0, 
0xF0,0xA8,0xE2,0x80, 
0xF0,0xAA,0x20,0xC5, 
0xF0,0xAC,0x01,0x61, 
0xF0,0xAE,0x20,0xC5, 
0xF0,0xB0,0x03,0x22, 
0xF0,0xB2,0xB1,0x12, 
0xF0,0xB4,0x71,0xCF, 
0xF0,0xB6,0xFF,0x00, 
0xF0,0xB8,0x3E,0xD0, 
0xF0,0xBA,0xB1,0x04, 
0xF0,0xBC,0x7E,0xE0, 
0xF0,0xBE,0x78,0xE0, 
0xF0,0xC0,0x70,0xCF, 
0xF0,0xC2,0xFF,0xFF, 
0xF0,0xC4,0xE7,0x1C, 
0xF0,0xC6,0x88,0x57, 
0xF0,0xC8,0x71,0xCF, 
0xF0,0xCA,0xFF,0xFF, 
0xF0,0xCC,0xF2,0x18, 
0xF0,0xCE,0x91,0x13, 
0xF0,0xD0,0xEA,0x84, 
0xF0,0xD2,0xB8,0xA9, 
0xF0,0xD4,0x78,0x10, 
0xF0,0xD6,0xF0,0x03, 
0xF0,0xD8,0xB8,0x89, 
0xF0,0xDA,0xB8,0x8C, 
0xF0,0xDC,0xB1,0x13, 
0xF0,0xDE,0x71,0xCF, 
0xF0,0xE0,0xFF,0x00, 
0xF0,0xE2,0x30,0xC0, 
0xF0,0xE4,0xB1,0x00, 
0xF0,0xE6,0x7E,0xE0, 
0xF0,0xE8,0xC0,0xF1, 
0xF0,0xEA,0x09,0x1E, 
0xF0,0xEC,0x03,0xC0, 
0xF0,0xEE,0xC1,0xA1, 
0xF0,0xF0,0x75,0x08, 
0xF0,0xF2,0x76,0x28, 
0xF0,0xF4,0x77,0x48, 
0xF0,0xF6,0xC2,0x40, 
0xF0,0xF8,0xD8,0x20, 
0xF0,0xFA,0x71,0xCF, 
0xF0,0xFC,0x00,0x03, 
0xF0,0xFE,0x20,0x67, 
0xF1,0x00,0xDA,0x02, 
0xF1,0x02,0x08,0xAE, 
0xF1,0x04,0x03,0xA0, 
0xF1,0x06,0x73,0xC9, 
0xF1,0x08,0x0E,0x25, 
0xF1,0x0A,0x13,0xC0, 
0xF1,0x0C,0x0B,0x5E, 
0xF1,0x0E,0x01,0x60, 
0xF1,0x10,0xD8,0x06, 
0xF1,0x12,0xFF,0xBC, 
0xF1,0x14,0x0C,0xCE, 
0xF1,0x16,0x01,0x00, 
0xF1,0x18,0xD8,0x00, 
0xF1,0x1A,0xB8,0x9E, 
0xF1,0x1C,0x0E,0x5A, 
0xF1,0x1E,0x03,0x20, 
0xF1,0x20,0xD9,0x01, 
0xF1,0x22,0xD8,0x00, 
0xF1,0x24,0xB8,0x9E, 
0xF1,0x26,0x0E,0xB6, 
0xF1,0x28,0x03,0x20, 
0xF1,0x2A,0xD9,0x01, 
0xF1,0x2C,0x8D,0x14, 
0xF1,0x2E,0x08,0x17, 
0xF1,0x30,0x01,0x91, 
0xF1,0x32,0x8D,0x16, 
0xF1,0x34,0xE8,0x07, 
0xF1,0x36,0x0B,0x36, 
0xF1,0x38,0x01,0x60, 
0xF1,0x3A,0xD8,0x07, 
0xF1,0x3C,0x0B,0x52, 
0xF1,0x3E,0x01,0x60, 
0xF1,0x40,0xD8,0x11, 
0xF1,0x42,0x8D,0x14, 
0xF1,0x44,0xE0,0x87, 
0xF1,0x46,0xD8,0x00, 
0xF1,0x48,0x20,0xCA, 
0xF1,0x4A,0x02,0x62, 
0xF1,0x4C,0x00,0xC9, 
0xF1,0x4E,0x03,0xE0, 
0xF1,0x50,0xC0,0xA1, 
0xF1,0x52,0x78,0xE0, 
0xF1,0x54,0xC0,0xF1, 
0xF1,0x56,0x08,0xB2, 
0xF1,0x58,0x03,0xC0, 
0xF1,0x5A,0x76,0xCF, 
0xF1,0x5C,0xFF,0xFF, 
0xF1,0x5E,0xE5,0x40, 
0xF1,0x60,0x75,0xCF, 
0xF1,0x62,0xFF,0xFF, 
0xF1,0x64,0xE5,0x68, 
0xF1,0x66,0x95,0x17, 
0xF1,0x68,0x96,0x40, 
0xF1,0x6A,0x77,0xCF, 
0xF1,0x6C,0xFF,0xFF, 
0xF1,0x6E,0xE5,0x42, 
0xF1,0x70,0x95,0x38, 
0xF1,0x72,0x0A,0x0D, 
0xF1,0x74,0x00,0x01, 
0xF1,0x76,0x97,0x40, 
0xF1,0x78,0x0A,0x11, 
0xF1,0x7A,0x00,0x40, 
0xF1,0x7C,0x0B,0x0A, 
0xF1,0x7E,0x01,0x00, 
0xF1,0x80,0x95,0x17, 
0xF1,0x82,0xB6,0x00, 
0xF1,0x84,0x95,0x18, 
0xF1,0x86,0xB7,0x00, 
0xF1,0x88,0x76,0xCF, 
0xF1,0x8A,0xFF,0xFF, 
0xF1,0x8C,0xE5,0x44, 
0xF1,0x8E,0x96,0x20, 
0xF1,0x90,0x95,0x15, 
0xF1,0x92,0x08,0x13, 
0xF1,0x94,0x00,0x40, 
0xF1,0x96,0x0E,0x1E, 
0xF1,0x98,0x01,0x20, 
0xF1,0x9A,0xD9,0x00, 
0xF1,0x9C,0x95,0x15, 
0xF1,0x9E,0xB6,0x00, 
0xF1,0xA0,0xFF,0xA1, 
0xF1,0xA2,0x75,0xCF, 
0xF1,0xA4,0xFF,0xFF, 
0xF1,0xA6,0xE7,0x1C, 
0xF1,0xA8,0x77,0xCF, 
0xF1,0xAA,0xFF,0xFF, 
0xF1,0xAC,0xE5,0x46, 
0xF1,0xAE,0x97,0x40, 
0xF1,0xB0,0x8D,0x16, 
0xF1,0xB2,0x76,0xCF, 
0xF1,0xB4,0xFF,0xFF, 
0xF1,0xB6,0xE5,0x48, 
0xF1,0xB8,0x8D,0x37, 
0xF1,0xBA,0x08,0x0D, 
0xF1,0xBC,0x00,0x81, 
0xF1,0xBE,0x96,0x40, 
0xF1,0xC0,0x09,0x15, 
0xF1,0xC2,0x00,0x80, 
0xF1,0xC4,0x0F,0xD6, 
0xF1,0xC6,0x01,0x00, 
0xF1,0xC8,0x8D,0x16, 
0xF1,0xCA,0xB7,0x00, 
0xF1,0xCC,0x8D,0x17, 
0xF1,0xCE,0xB6,0x00, 
0xF1,0xD0,0xFF,0xB0, 
0xF1,0xD2,0xFF,0xBC, 
0xF1,0xD4,0x00,0x41, 
0xF1,0xD6,0x03,0xC0, 
0xF1,0xD8,0xC0,0xF1, 
0xF1,0xDA,0x0D,0x9E, 
0xF1,0xDC,0x01,0x00, 
0xF1,0xDE,0xE8,0x04, 
0xF1,0xE0,0xFF,0x88, 
0xF1,0xE2,0xF0,0x0A, 
0xF1,0xE4,0x0D,0x6A, 
0xF1,0xE6,0x01,0x00, 
0xF1,0xE8,0x0D,0x8E, 
0xF1,0xEA,0x01,0x00, 
0xF1,0xEC,0xE8,0x7E, 
0xF1,0xEE,0xFF,0x85, 
0xF1,0xF0,0x0D,0x72, 
0xF1,0xF2,0x01,0x00, 
0xF1,0xF4,0xFF,0x8C, 
0xF1,0xF6,0xFF,0xA7, 
0xF1,0xF8,0xFF,0xB2, 
0xF1,0xFA,0xD8,0x00, 
0xF1,0xFC,0x73,0xCF, 
0xF1,0xFE,0xFF,0xFF, 
0xF2,0x00,0xF2,0x40, 
0xF2,0x02,0x23,0x15, 
0xF2,0x04,0x00,0x01, 
0xF2,0x06,0x81,0x41, 
0xF2,0x08,0xE0,0x02, 
0xF2,0x0A,0x81,0x20, 
0xF2,0x0C,0x08,0xF7, 
0xF2,0x0E,0x81,0x34, 
0xF2,0x10,0xA1,0x40, 
0xF2,0x12,0xD8,0x00, 
0xF2,0x14,0xC0,0xD1, 
0xF2,0x16,0x7E,0xE0, 
0xF2,0x18,0x53,0x51, 
0xF2,0x1A,0x30,0x34, 
0xF2,0x1C,0x20,0x6F, 
0xF2,0x1E,0x6E,0x5F, 
0xF2,0x20,0x73,0x74, 
0xF2,0x22,0x61,0x72, 
0xF2,0x24,0x74,0x5F, 
0xF2,0x26,0x73,0x74, 
0xF2,0x28,0x72,0x65, 
0xF2,0x2A,0x61,0x6D, 
0xF2,0x2C,0x69,0x6E, 
0xF2,0x2E,0x67,0x20, 
0xF2,0x30,0x25,0x64, 
0xF2,0x32,0x20,0x25, 
0xF2,0x34,0x64,0x0A,
0xF2,0x36,0x00,0x00, 
0xF2,0x38,0x00,0x00, 
0xF2,0x3A,0x00,0x00, 
0xF2,0x3C,0x00,0x00, 
0xF2,0x3E,0x00,0x00, 
0xF2,0x40,0xFF,0xFF, 
0xF2,0x42,0xE8,0x28, 
0xF2,0x44,0xFF,0xFF, 
0xF2,0x46,0xF0,0xE8, 
0xF2,0x48,0xFF,0xFF, 
0xF2,0x4A,0xE8,0x08, 
0xF2,0x4C,0xFF,0xFF, 
0xF2,0x4E,0xF1,0x54, 
0x09,0x8E,0x00,0x00, 
0xE0,0x00,0x05,0xD8, 
0xE0,0x02,0x04,0x03, 
0x00,0x40,0xFF,0xF8, 
			//delay = 30
0x00,0x40,0xFF,0xF9, 
			//delay = 30
0x32,0x10,0x00,0xB0, 
0x09,0x8e,0x48,0x26, 
0xc8,0x26,0x01,0x00, 
0xc8,0x6c,0x00,0x80, 
0xc8,0x6e,0x00,0x80, 
0xc8,0x70,0x00,0x20, 
0xc8,0x72,0x28,0x00, 
0xa8,0x0e,0xa8,0x08, 
0x30,0x32,0x01,0x00, 
0x30,0x34,0x01,0x00, 
0x30,0x36,0x01,0x00, 
0x30,0x38,0x01,0x00, 
0xc8,0x22,0x00,0xe0, 
0x00,0x40,0x80,0x02, 
0x00,0x40,0x80,0x04, 
0xc8,0x68,0x02,0x38, 
0xa8,0x0e,0x2a,0x06, 
0xa8,0x12,0x04,0x00, 
0xa4,0x04,0x01,0x01, 
0xC8,0xF4,0x00,0x04, 
0xC8,0xF6,0x00,0x00, 
0xC8,0xF8,0x00,0x82, 
0xC8,0xFA,0x00,0x5E, 
0x00,0x40,0x80,0x04, 
0x32,0x6c,0x10,0x03, 
0x09,0x8E,0x48,0x8A, 
0xC8,0x8A,0x02,0x14, 
0xC8,0x8C,0xFE,0xDE, 
0xC8,0x8E,0x00,0x0D, 
0xC8,0x90,0xFF,0xCB, 
0xC8,0x92,0x01,0x4D, 
0xC8,0x94,0xFF,0xE8, 
0xC8,0x96,0xFF,0xC6, 
0xC8,0x98,0xFF,0x2B, 
0xC8,0x9A,0x02,0x0F, 
0xC8,0x9C,0x00,0x1E, 
0xC8,0x9E,0x00,0x44, 
0xC8,0xA0,0xFF,0xB7, 
0xC8,0xA2,0x00,0x9F, 
0xC8,0xA4,0xFF,0xAA, 
0xC8,0xA6,0x00,0x05, 
0xC8,0xA8,0xFF,0xD3, 
0xC8,0xAA,0x00,0x28, 
0xC8,0xAC,0x00,0x36, 
0xC8,0xAE,0x00,0x67, 
0xC8,0xB0,0xFF,0x63, 
0xC8,0xB2,0x00,0x12, 
0xC8,0xB4,0xFF,0xD9, 
0xC8,0xCA,0x03,0x01, 
0xC8,0xCC,0x00,0x00, 
0xC8,0xCE,0x00,0x00, 
0xC8,0xD0,0x00,0x80, 
0xC8,0xD2,0x1B,0x80, 
0xC8,0xD4,0x16,0x80, 
0xC8,0xD6,0x01,0xAC, 
0xC8,0xD8,0x00,0x3C, 
0xC8,0xDA,0x00,0x00, 
0xC8,0xDC,0x00,0x3C, 
0xC8,0xDE,0x00,0x57, 
0xAC,0x32,0x2E,0x7f,  
0xAC,0x34,0x1B,0x83, 
0x09,0x8E,0xBC,0x0C, 
0xBC,0x02,0x00,0x07, 
0xBC,0x0C,0x00,0x03, 
0xBC,0x08,0x02,0x01, 
0xBC,0x0E,0x0a,0x20, 
0xBC,0x10,0x4f,0x71, 
0xBC,0x12,0x8d,0xa3, 
0xBC,0x14,0xb3,0xc0,
0xBC,0x16,0xcc,0xd5, 
0xBC,0x18,0xdd,0xe4, 
0xBC,0x1A,0xeb,0xf0, 
0xBC,0x1C,0xf6,0xfb, 
0xBC,0x1E,0xFf,0x00, 
//0xc8,0x1c,0x00,0x14, 
0x00,0x40,0x80,0x02, 
0x36,0x40,0x03,0x70,	
0x36,0x42,0x30,0xE8,	
0x36,0x44,0x0A,0xCF,	
0x36,0x46,0x62,0xCC,	
0x36,0x48,0xA4,0x2F,	
0x36,0x4A,0x02,0xD0,	
0x36,0x4C,0xB9,0xAB,	
0x36,0x4E,0x1B,0x0F,	
0x36,0x50,0x1F,0x2B,	
0x36,0x52,0x99,0x0F,	
0x36,0x54,0x02,0xD0,	
0x36,0x56,0xBD,0x89,	
0x36,0x58,0x4F,0x2E,	
0x36,0x5A,0x81,0x2A,	
0x36,0x5C,0xAF,0xCE,	
0x36,0x5E,0x03,0x90,	
0x36,0x60,0x9E,0xC9,	
0x36,0x62,0x16,0xCF,	
0x36,0x64,0x11,0x0D,	
0x36,0x66,0xBF,0xCF,	
0x36,0x80,0x0B,0x8C,	
0x36,0x82,0x94,0x6E,	
0x36,0x84,0xB1,0x4D,	
0x36,0x86,0x51,0xCE,	
0x36,0x88,0x0E,0xEF,	
0x36,0x8A,0x51,0x0A,	
0x36,0x8C,0x85,0x2E,	
0x36,0x8E,0x13,0xAB,	
0x36,0x90,0x20,0xEE,	
0x36,0x92,0x5F,0x6D,	
0x36,0x94,0x07,0xEC,	
0x36,0x96,0xDB,0x4D,	
0x36,0x98,0x03,0xAE,	
0x36,0x9A,0x1F,0xAE,	
0x36,0x9C,0xE3,0xCD,	
0x36,0x9E,0x00,0xED,	
0x36,0xA0,0xC4,0x0D,	
0x36,0xA2,0x46,0xCB,	
0x36,0xA4,0x1F,0x4E,	
0x36,0xA6,0x28,0xAB,	
0x36,0xC0,0x7E,0xED,	
0x36,0xC2,0x09,0x8D,	
0x36,0xC4,0x89,0xF1,	
0x36,0xC6,0x95,0xEE,	
0x36,0xC8,0x47,0xCF,	
0x36,0xCA,0x2B,0xCE,	
0x36,0xCC,0xC7,0x08,	
0x36,0xCE,0x8E,0xD1,	
0x36,0xD0,0x06,0x0D,	
0x36,0xD2,0x21,0xF0,	
0x36,0xD4,0x6D,0x0D,	
0x36,0xD6,0xC7,0x2E,	
0x36,0xD8,0x93,0x71,	
0x36,0xDA,0x05,0xF0,	
0x36,0xDC,0x73,0xD0,	
0x36,0xDE,0x3D,0x8D,	
0x36,0xE0,0x12,0x0D,	
0x36,0xE2,0x89,0xD1,	
0x36,0xE4,0xEB,0xCD,	
0x36,0xE6,0x29,0xD0,	
0x37,0x00,0xA6,0x6E,	
0x37,0x02,0x65,0xCF,	
0x37,0x04,0x02,0x51,	
0x37,0x06,0xC2,0x6F,	
0x37,0x08,0xC2,0xB1,	
0x37,0x0A,0xD9,0x2C,	
0x37,0x0C,0x39,0x8F,	
0x37,0x0E,0x64,0x0E,	
0x37,0x10,0xC3,0xCF,	
0x37,0x12,0x20,0x0E,	
0x37,0x14,0x22,0x4B,	
0x37,0x16,0x1E,0x8F,	
0x37,0x18,0x97,0x30,	
0x37,0x1A,0xA1,0x6F,	
0x37,0x1C,0x33,0x11,	
0x37,0x1E,0xB8,0xAD,	
0x37,0x20,0x4B,0x8F,	
0x37,0x22,0x57,0x8F,	
0x37,0x24,0xCE,0x6F,	
0x37,0x26,0xF4,0xCF,	
0x37,0x40,0x95,0xAE,	
0x37,0x42,0x97,0xAF,	
0x37,0x44,0x71,0xAC,	
0x37,0x46,0x15,0x8D,	
0x37,0x48,0x1F,0x72,	
0x37,0x4A,0x9A,0x4F,	
0x37,0x4C,0xCA,0x6D,	
0x37,0x4E,0x02,0xD1,	
0x37,0x50,0x17,0x8F,	
0x37,0x52,0xF1,0x2F,	
0x37,0x54,0xDC,0xCE,	
0x37,0x56,0x07,0x10,	
0x37,0x58,0x05,0xB2,	
0x37,0x5A,0xDB,0x11,	
0x37,0x5C,0xC6,0x32,	
0x37,0x5E,0x8B,0xCE,	
0x37,0x60,0x99,0x2F,	
0x37,0x62,0x07,0x90,	
0x37,0x64,0x63,0xCD,	
0x37,0x66,0x39,0xD0,	
0x37,0x82,0x00,0xD8,	
0x37,0x84,0x01,0x3C,	
0x32,0x10,0x02,0xb8,	
0x09,0x8E,0x48,0x60, 
0xc8,0x60,0x01,0x00, 
0xc8,0x61,0x00,0x00, 
0x09,0x8E,0x48,0x61, 
0x00,0x40,0x80,0x02, 
0x09,0x8E,0x48,0x02, 
0xc8,0x02,0x00,0x10, 
0xc8,0x06,0x02,0x97, 
0xc8,0x04,0x01,0xf3, 
0xc8,0x14,0x01,0xe3, 
0xc8,0x0e,0x02,0x0d, 
0xc8,0x48,0x00,0x00, 
0xc8,0x4a,0x00,0x00, 
0xc8,0x4c,0x02,0x80, 
0xc8,0x4e,0x01,0xe0, 
0xc8,0x54,0x02,0x80, 
0xc8,0x56,0x01,0xe0, 
0xc8,0x50,0x03,0x42, 
0xc8,0xf0,0x02,0x7f, 
0xc8,0xf2,0x01,0xdf, 
0xc8,0xf4,0x00,0x04, 
0xc8,0xf6,0x00,0x04, 
0xc8,0xf8,0x00,0x7e, 
0xc8,0xfa,0x00,0x5e, 
0xdc,0x00,0x28,0x00, 
//0xc8,0x28,0x00,0x00, //modify by seven 2011-06-22
0xc8,0x28,0x00,0x02, 
		       //delay = 10
0xc9,0x05,0x02,0x00, 
0xc9,0x08,0x03,0x00, 
		       //delay = 10 
0x09,0x8e,0x48,0x18, 
0x09,0x90,0x00,0x9b,  //open streaming


0x09,0x8E,0x48,0x48,  //VGA streaming
0x09,0x90,0x00,0x00,
0x09,0x8E,0x48,0x4A,
0x09,0x90,0x00,0x00,
0x09,0x8E,0x48,0x4C,
0x09,0x90,0x02,0x80,
0x09,0x8E,0x48,0x4E,
0x09,0x90,0x01,0xE0,
0x09,0x8E,0x48,0x54,
0x09,0x90,0x02,0x80,
0x09,0x8E,0x48,0x56,
0x09,0x90,0x01,0xe0,
0x09,0x8E,0xC8,0x50,
0x09,0x90,0x03,0x00,
0x09,0x8E,0x48,0xF0,
0x09,0x90,0x02,0x7F,
0x09,0x8E,0x48,0xF2,
0x09,0x90,0x01,0xdF,
0x09,0x8E,0x48,0xF4,
0x09,0x90,0x00,0x04,
0x09,0x8E,0x48,0xF6,
0x09,0x90,0x00,0x04,
0x09,0x8E,0x48,0xF8,
0x09,0x90,0x00,0x7e,
0x09,0x8E,0x48,0xFA,
0x09,0x90,0x00,0x5e,
0x09,0x8E,0xDC,0x00,
0x09,0x90,0x28,0x00,
0x09,0x8e,0x48,0x16,
0x09,0x90,0x00,0x83,
0xdc,0x00,0x28,0x31,
0x00,0x40,0x80,0x02,
										//delay = 10 //VGA streaming

0x09,0x8E,0x48,0x28,
//0xc8,0x28,0x00,0x00, //modify by seven 2011-06-22
0xc8,0x28,0x00,0x02, 
0xdc,0x00,0x28,0x31, 
0x00,0x40,0x80,0x02, 
										//delay = 30  //normal[flip section]

0x09,0x8E,0x48,0x69,  //brightness
0x09,0x90,0x38,0x00, 

0x09,0x8E,0x48,0x60,  //Hue
0x09,0x90,0x01,0x00,
0x09,0x8E,0x48,0x61,
0x09,0x90,0x00,0x00,
0x00,0x40,0x80,0x02,

0x09,0x8E,0x49,0x05,  //sharpness
0x09,0x90,0x02,0x00,
0x09,0x8E,0x49,0x08,
0x09,0x90,0x02,0x00,
//modify by seven 2011-6-7
//Disable auto exposure
#if 0
0x09,0x8E,0x28,0x04,
0xA8,0x04,0x00,0x00,
0xDC,0x00,0x00,0x28,
0x00,0x40,0x80,0x02,
0x30,0x12,0x01,0x2C,
#endif
//Enable auto exposure
#if 1
0x09,0x8E,0x28,0x04,
0xA8,0x04,0x00,0x1F,
0xDC,0x00,0x00,0x28,
0x00,0x40,0x80,0x02,
#endif

//0xC8,0x1A,0x00,0x06,
//0xC8,0x1C,0x00,0x05,

END_,END_,END_,END_
};

unsigned char mt9v136regs1[]=
{
#if 1
0x09,0x8E,0x28,0x04,
0xA8,0x04,0x00,0x00,
0xDC,0x00,0x00,0x28,
0x00,0x40,0x80,0x02,
0x30,0x12,0x01,0x2C,
#endif
0xC8,0x16,0x00,0x83, 
0xC8,0x18,0x00,0x9D, 
0xC8,0x1A,0x00,0x18, 
0xC8,0x1C,0x00,0x14, 
0x00,0x40,0x80,0x02,
			//delay = 30
0xC8,0x1E,0x00,0x04, 
0xC8,0x20,0x00,0x03, 
0xC9,0x16,0x01,0x09, 
0xC9,0x18,0x06,0x2C, 
0xC8,0x50,0x03,0x42, 
0xC8,0xF4,0x00,0x04, 
0xC8,0xF8,0x00,0x82, 
			//delay = 30
0x00,0x30,0x04,0x04, 
0x00,0x30,0x04,0x04, 
0x30,0x1A,0x10,0xD0, 
0x31,0xC0,0x14,0x04, 
0x3E,0xD8,0x87,0x9C, 
0x30,0x42,0x20,0xE1, 
0x30,0xD4,0x80,0x20, 
0x30,0xC0,0x00,0x26, 
0x30,0x1A,0x10,0xD4,
0xA8,0x02,0x00,0xD3, 
0xC8,0x78,0x00,0xA0, 
0xC8,0x76,0x01,0x40, 
0xBC,0x04,0x00,0xFC, 
0xBC,0x38,0x00,0x7f, 
0xBC,0x3A,0x00,0xbf,	
0xBC,0x3C,0x00,0xbf, 
0xBC,0x04,0x00,0xFc,	
0xC9,0x1A,0x00,0x0F, 
0xC9,0x1C,0x00,0x06, 
0xC8,0xFC,0x00,0x0C, 
0xC8,0xFE,0x00,0x30, 
0xC9,0x12,0x00,0x0C, 
0xC9,0x14,0x00,0x4B, 
0xC9,0x16,0x01,0x09, 
0xC9,0x18,0x06,0x2C, 
0xC9,0x07,0xA8,0x01, 
0xC9,0x0A,0x14,0x14, 
0xC9,0x0C,0x14,0x14, 
0xC9,0x0E,0x32,0x32, 
0xC9,0x10,0x32,0x32, 
0xC9,0x1E,0x01,0xF4, 
0xC9,0x20,0x27,0x10,
0xC9,0x00,0x80,0x4a, 
0xC9,0x04,0x08,0x02,  
0xC9,0x06,0x02,0xa8,  
0xC9,0x08,0x07,0x7f,  
0xBC,0x06,0x01,0x5E, 
0xC8,0xE6,0x80,0x80, 
0xC8,0x3E,0x00,0x01, 
0x32,0x80,0x00,0xAA, 
0xC9,0x16,0x01,0x09, 
0xC9,0x18,0x06,0x2C, 
0xC8,0xCE,0x33,0xA1, 
0xC8,0xD0,0xEC,0x08, 
0xC8,0xD2,0xFF,0xC0, 
0xC8,0xDE,0x00,0x33, 
0x00,0x40,0x80,0x02, 
			//delay = 30
0x09,0x82,0x00,0x01, 
0x09,0x8A,0x70,0x00, 
0xF0,0x00,0x72,0xCF, 
0xF0,0x02,0xFF,0x00, 
0xF0,0x04,0x3E,0xD0, 
0xF0,0x06,0x92,0x00, 
0xF0,0x08,0x71,0xCF, 
0xF0,0x0A,0xFF,0xFF, 
0xF0,0x0C,0xF2,0x18, 
0xF0,0x0E,0xB1,0x10, 
0xF0,0x10,0x92,0x05, 
0xF0,0x12,0xB1,0x11, 
0xF0,0x14,0x92,0x04, 
0xF0,0x16,0xB1,0x12, 
0xF0,0x18,0x70,0xCF, 
0xF0,0x1A,0xFF,0x00, 
0xF0,0x1C,0x30,0xC0, 
0xF0,0x1E,0x90,0x00, 
0xF0,0x20,0x7F,0xE0, 
0xF0,0x22,0xB1,0x13, 
0xF0,0x24,0x70,0xCF, 
0xF0,0x26,0xFF,0xFF, 
0xF0,0x28,0xE7,0x1C, 
0xF0,0x2A,0x88,0x36, 
0xF0,0x2C,0x09,0x0F, 
0xF0,0x2E,0x00,0xB3, 
0xF0,0x30,0x69,0x13, 
0xF0,0x32,0xE1,0x80, 
0xF0,0x34,0xD8,0x08, 
0xF0,0x36,0x20,0xCA, 
0xF0,0x38,0x03,0x22, 
0xF0,0x3A,0x71,0xCF, 
0xF0,0x3C,0xFF,0xFF, 
0xF0,0x3E,0xE5,0x68, 
0xF0,0x40,0x91,0x35, 
0xF0,0x42,0x22,0x0A, 
0xF0,0x44,0x1F,0x80, 
0xF0,0x46,0xFF,0xFF, 
0xF0,0x48,0xF2,0x18, 
0xF0,0x4A,0x29,0x05, 
0xF0,0x4C,0x00,0x3E, 
0xF0,0x4E,0x12,0x22, 
0xF0,0x50,0x11,0x01, 
0xF0,0x52,0x21,0x04, 
0xF0,0x54,0x0F,0x81, 
0xF0,0x56,0x00,0x00, 
0xF0,0x58,0xFF,0xF0, 
0xF0,0x5A,0x21,0x8C, 
0xF0,0x5C,0xF0,0x10, 
0xF0,0x5E,0x1A,0x22, 
0xF0,0x60,0x10,0x44, 
0xF0,0x62,0x12,0x20, 
0xF0,0x64,0x11,0x02, 
0xF0,0x66,0xF7,0x87, 
0xF0,0x68,0x22,0x4F, 
0xF0,0x6A,0x03,0x83, 
0xF0,0x6C,0x1A,0x20, 
0xF0,0x6E,0x10,0xC4, 
0xF0,0x70,0xF0,0x09, 
0xF0,0x72,0xBA,0xAE, 
0xF0,0x74,0x7B,0x50, 
0xF0,0x76,0x1A,0x20, 
0xF0,0x78,0x10,0x84, 
0xF0,0x7A,0x21,0x45, 
0xF0,0x7C,0x01,0xC1, 
0xF0,0x7E,0x1A,0x22, 
0xF0,0x80,0x10,0x44, 
0xF0,0x82,0x70,0xCF, 
0xF0,0x84,0xFF,0x00, 
0xF0,0x86,0x3E,0xD0, 
0xF0,0x88,0xB0,0x60, 
0xF0,0x8A,0xB0,0x25, 
0xF0,0x8C,0x7E,0xE0, 
0xF0,0x8E,0x78,0xE0, 
0xF0,0x90,0x71,0xCF, 
0xF0,0x92,0xFF,0xFF, 
0xF0,0x94,0xF2,0x18, 
0xF0,0x96,0x91,0x12, 
0xF0,0x98,0x72,0xCF, 
0xF0,0x9A,0xFF,0xFF, 
0xF0,0x9C,0xE7,0x1C, 
0xF0,0x9E,0x8A,0x57, 
0xF0,0xA0,0x20,0x04, 
0xF0,0xA2,0x0F,0x80, 
0xF0,0xA4,0x00,0x00, 
0xF0,0xA6,0xFF,0xF0, 
0xF0,0xA8,0xE2,0x80, 
0xF0,0xAA,0x20,0xC5, 
0xF0,0xAC,0x01,0x61, 
0xF0,0xAE,0x20,0xC5, 
0xF0,0xB0,0x03,0x22, 
0xF0,0xB2,0xB1,0x12, 
0xF0,0xB4,0x71,0xCF, 
0xF0,0xB6,0xFF,0x00, 
0xF0,0xB8,0x3E,0xD0, 
0xF0,0xBA,0xB1,0x04, 
0xF0,0xBC,0x7E,0xE0, 
0xF0,0xBE,0x78,0xE0, 
0xF0,0xC0,0x70,0xCF, 
0xF0,0xC2,0xFF,0xFF, 
0xF0,0xC4,0xE7,0x1C, 
0xF0,0xC6,0x88,0x57, 
0xF0,0xC8,0x71,0xCF, 
0xF0,0xCA,0xFF,0xFF, 
0xF0,0xCC,0xF2,0x18, 
0xF0,0xCE,0x91,0x13, 
0xF0,0xD0,0xEA,0x84, 
0xF0,0xD2,0xB8,0xA9, 
0xF0,0xD4,0x78,0x10, 
0xF0,0xD6,0xF0,0x03, 
0xF0,0xD8,0xB8,0x89, 
0xF0,0xDA,0xB8,0x8C, 
0xF0,0xDC,0xB1,0x13, 
0xF0,0xDE,0x71,0xCF, 
0xF0,0xE0,0xFF,0x00, 
0xF0,0xE2,0x30,0xC0, 
0xF0,0xE4,0xB1,0x00, 
0xF0,0xE6,0x7E,0xE0, 
0xF0,0xE8,0xC0,0xF1, 
0xF0,0xEA,0x09,0x1E, 
0xF0,0xEC,0x03,0xC0, 
0xF0,0xEE,0xC1,0xA1, 
0xF0,0xF0,0x75,0x08, 
0xF0,0xF2,0x76,0x28, 
0xF0,0xF4,0x77,0x48, 
0xF0,0xF6,0xC2,0x40, 
0xF0,0xF8,0xD8,0x20, 
0xF0,0xFA,0x71,0xCF, 
0xF0,0xFC,0x00,0x03, 
0xF0,0xFE,0x20,0x67, 
0xF1,0x00,0xDA,0x02, 
0xF1,0x02,0x08,0xAE, 
0xF1,0x04,0x03,0xA0, 
0xF1,0x06,0x73,0xC9, 
0xF1,0x08,0x0E,0x25, 
0xF1,0x0A,0x13,0xC0, 
0xF1,0x0C,0x0B,0x5E, 
0xF1,0x0E,0x01,0x60, 
0xF1,0x10,0xD8,0x06, 
0xF1,0x12,0xFF,0xBC, 
0xF1,0x14,0x0C,0xCE, 
0xF1,0x16,0x01,0x00, 
0xF1,0x18,0xD8,0x00, 
0xF1,0x1A,0xB8,0x9E, 
0xF1,0x1C,0x0E,0x5A, 
0xF1,0x1E,0x03,0x20, 
0xF1,0x20,0xD9,0x01, 
0xF1,0x22,0xD8,0x00, 
0xF1,0x24,0xB8,0x9E, 
0xF1,0x26,0x0E,0xB6, 
0xF1,0x28,0x03,0x20, 
0xF1,0x2A,0xD9,0x01, 
0xF1,0x2C,0x8D,0x14, 
0xF1,0x2E,0x08,0x17, 
0xF1,0x30,0x01,0x91, 
0xF1,0x32,0x8D,0x16, 
0xF1,0x34,0xE8,0x07, 
0xF1,0x36,0x0B,0x36, 
0xF1,0x38,0x01,0x60, 
0xF1,0x3A,0xD8,0x07, 
0xF1,0x3C,0x0B,0x52, 
0xF1,0x3E,0x01,0x60, 
0xF1,0x40,0xD8,0x11, 
0xF1,0x42,0x8D,0x14, 
0xF1,0x44,0xE0,0x87, 
0xF1,0x46,0xD8,0x00, 
0xF1,0x48,0x20,0xCA, 
0xF1,0x4A,0x02,0x62, 
0xF1,0x4C,0x00,0xC9, 
0xF1,0x4E,0x03,0xE0, 
0xF1,0x50,0xC0,0xA1, 
0xF1,0x52,0x78,0xE0, 
0xF1,0x54,0xC0,0xF1, 
0xF1,0x56,0x08,0xB2, 
0xF1,0x58,0x03,0xC0, 
0xF1,0x5A,0x76,0xCF, 
0xF1,0x5C,0xFF,0xFF, 
0xF1,0x5E,0xE5,0x40, 
0xF1,0x60,0x75,0xCF, 
0xF1,0x62,0xFF,0xFF, 
0xF1,0x64,0xE5,0x68, 
0xF1,0x66,0x95,0x17, 
0xF1,0x68,0x96,0x40, 
0xF1,0x6A,0x77,0xCF, 
0xF1,0x6C,0xFF,0xFF, 
0xF1,0x6E,0xE5,0x42, 
0xF1,0x70,0x95,0x38, 
0xF1,0x72,0x0A,0x0D, 
0xF1,0x74,0x00,0x01, 
0xF1,0x76,0x97,0x40, 
0xF1,0x78,0x0A,0x11, 
0xF1,0x7A,0x00,0x40, 
0xF1,0x7C,0x0B,0x0A, 
0xF1,0x7E,0x01,0x00, 
0xF1,0x80,0x95,0x17, 
0xF1,0x82,0xB6,0x00, 
0xF1,0x84,0x95,0x18, 
0xF1,0x86,0xB7,0x00, 
0xF1,0x88,0x76,0xCF, 
0xF1,0x8A,0xFF,0xFF, 
0xF1,0x8C,0xE5,0x44, 
0xF1,0x8E,0x96,0x20, 
0xF1,0x90,0x95,0x15, 
0xF1,0x92,0x08,0x13, 
0xF1,0x94,0x00,0x40, 
0xF1,0x96,0x0E,0x1E, 
0xF1,0x98,0x01,0x20, 
0xF1,0x9A,0xD9,0x00, 
0xF1,0x9C,0x95,0x15, 
0xF1,0x9E,0xB6,0x00, 
0xF1,0xA0,0xFF,0xA1, 
0xF1,0xA2,0x75,0xCF, 
0xF1,0xA4,0xFF,0xFF, 
0xF1,0xA6,0xE7,0x1C, 
0xF1,0xA8,0x77,0xCF, 
0xF1,0xAA,0xFF,0xFF, 
0xF1,0xAC,0xE5,0x46, 
0xF1,0xAE,0x97,0x40, 
0xF1,0xB0,0x8D,0x16, 
0xF1,0xB2,0x76,0xCF, 
0xF1,0xB4,0xFF,0xFF, 
0xF1,0xB6,0xE5,0x48, 
0xF1,0xB8,0x8D,0x37, 
0xF1,0xBA,0x08,0x0D, 
0xF1,0xBC,0x00,0x81, 
0xF1,0xBE,0x96,0x40, 
0xF1,0xC0,0x09,0x15, 
0xF1,0xC2,0x00,0x80, 
0xF1,0xC4,0x0F,0xD6, 
0xF1,0xC6,0x01,0x00, 
0xF1,0xC8,0x8D,0x16, 
0xF1,0xCA,0xB7,0x00, 
0xF1,0xCC,0x8D,0x17, 
0xF1,0xCE,0xB6,0x00, 
0xF1,0xD0,0xFF,0xB0, 
0xF1,0xD2,0xFF,0xBC, 
0xF1,0xD4,0x00,0x41, 
0xF1,0xD6,0x03,0xC0, 
0xF1,0xD8,0xC0,0xF1, 
0xF1,0xDA,0x0D,0x9E, 
0xF1,0xDC,0x01,0x00, 
0xF1,0xDE,0xE8,0x04, 
0xF1,0xE0,0xFF,0x88, 
0xF1,0xE2,0xF0,0x0A, 
0xF1,0xE4,0x0D,0x6A, 
0xF1,0xE6,0x01,0x00, 
0xF1,0xE8,0x0D,0x8E, 
0xF1,0xEA,0x01,0x00, 
0xF1,0xEC,0xE8,0x7E, 
0xF1,0xEE,0xFF,0x85, 
0xF1,0xF0,0x0D,0x72, 
0xF1,0xF2,0x01,0x00, 
0xF1,0xF4,0xFF,0x8C, 
0xF1,0xF6,0xFF,0xA7, 
0xF1,0xF8,0xFF,0xB2, 
0xF1,0xFA,0xD8,0x00, 
0xF1,0xFC,0x73,0xCF, 
0xF1,0xFE,0xFF,0xFF, 
0xF2,0x00,0xF2,0x40, 
0xF2,0x02,0x23,0x15, 
0xF2,0x04,0x00,0x01, 
0xF2,0x06,0x81,0x41, 
0xF2,0x08,0xE0,0x02, 
0xF2,0x0A,0x81,0x20, 
0xF2,0x0C,0x08,0xF7, 
0xF2,0x0E,0x81,0x34, 
0xF2,0x10,0xA1,0x40, 
0xF2,0x12,0xD8,0x00, 
0xF2,0x14,0xC0,0xD1, 
0xF2,0x16,0x7E,0xE0, 
0xF2,0x18,0x53,0x51, 
0xF2,0x1A,0x30,0x34, 
0xF2,0x1C,0x20,0x6F, 
0xF2,0x1E,0x6E,0x5F, 
0xF2,0x20,0x73,0x74, 
0xF2,0x22,0x61,0x72, 
0xF2,0x24,0x74,0x5F, 
0xF2,0x26,0x73,0x74, 
0xF2,0x28,0x72,0x65, 
0xF2,0x2A,0x61,0x6D, 
0xF2,0x2C,0x69,0x6E, 
0xF2,0x2E,0x67,0x20, 
0xF2,0x30,0x25,0x64, 
0xF2,0x32,0x20,0x25, 
0xF2,0x34,0x64,0x0A,
0xF2,0x36,0x00,0x00, 
0xF2,0x38,0x00,0x00, 
0xF2,0x3A,0x00,0x00, 
0xF2,0x3C,0x00,0x00, 
0xF2,0x3E,0x00,0x00, 
0xF2,0x40,0xFF,0xFF, 
0xF2,0x42,0xE8,0x28, 
0xF2,0x44,0xFF,0xFF, 
0xF2,0x46,0xF0,0xE8, 
0xF2,0x48,0xFF,0xFF, 
0xF2,0x4A,0xE8,0x08, 
0xF2,0x4C,0xFF,0xFF, 
0xF2,0x4E,0xF1,0x54, 
0x09,0x8E,0x00,0x00, 
0xE0,0x00,0x05,0xD8, 
0xE0,0x02,0x04,0x03, 
0x00,0x40,0xFF,0xF8, 
			//delay = 30
0x00,0x40,0xFF,0xF9, 
			//delay = 30
0x32,0x10,0x00,0xB0, 
0x09,0x8e,0x48,0x26, 
0xc8,0x26,0x01,0x00, 
0xc8,0x6c,0x00,0x80, 
0xc8,0x6e,0x00,0x80, 
0xc8,0x70,0x00,0x20, 
0xc8,0x72,0x01,0x00, 
0xa8,0x0e,0xa8,0x08, 
0x30,0x32,0x01,0x00, 
0x30,0x34,0x01,0x00, 
0x30,0x36,0x01,0x00, 
0x30,0x38,0x01,0x00, 
0xc8,0x22,0x00,0xe0, 
0x00,0x40,0x80,0x02, 
0x00,0x40,0x80,0x04, 
0xc8,0x68,0x02,0x38, 
0xa8,0x0e,0x2a,0x06, 
0xa8,0x12,0x04,0x00, 
0xa4,0x04,0x01,0x01, 
0xC8,0xF4,0x00,0x04, 
0xC8,0xF6,0x00,0x00, 
0xC8,0xF8,0x00,0x82, 
0xC8,0xFA,0x00,0x5E, 
0x00,0x40,0x80,0x04, 
0x32,0x6c,0x10,0x03, 
0x09,0x8E,0x48,0x8A, 
0xC8,0x8A,0x02,0x14, 
0xC8,0x8C,0xFE,0xDE, 
0xC8,0x8E,0x00,0x0D, 
0xC8,0x90,0xFF,0xCB, 
0xC8,0x92,0x01,0x4D, 
0xC8,0x94,0xFF,0xE8, 
0xC8,0x96,0xFF,0xC6, 
0xC8,0x98,0xFF,0x2B, 
0xC8,0x9A,0x02,0x0F, 
0xC8,0x9C,0x00,0x1E, 
0xC8,0x9E,0x00,0x44, 
0xC8,0xA0,0xFF,0xB7, 
0xC8,0xA2,0x00,0x9F, 
0xC8,0xA4,0xFF,0xAA, 
0xC8,0xA6,0x00,0x05, 
0xC8,0xA8,0xFF,0xD3, 
0xC8,0xAA,0x00,0x28, 
0xC8,0xAC,0x00,0x36, 
0xC8,0xAE,0x00,0x67, 
0xC8,0xB0,0xFF,0x63, 
0xC8,0xB2,0x00,0x12, 
0xC8,0xB4,0xFF,0xD9, 
0xC8,0xCA,0x03,0x01, 
0xC8,0xCC,0x00,0x00, 
0xC8,0xCE,0x00,0x00, 
0xC8,0xD0,0x00,0x80, 
0xC8,0xD2,0x1B,0x80, 
0xC8,0xD4,0x16,0x80, 
0xC8,0xD6,0x01,0xAC, 
0xC8,0xD8,0x00,0x3C, 
0xC8,0xDA,0x00,0x00, 
0xC8,0xDC,0x00,0x3C, 
0xC8,0xDE,0x00,0x57, 
0xAC,0x32,0x2E,0x7f,  
0xAC,0x34,0x1B,0x83, 
0x09,0x8E,0xBC,0x0C, 
0xBC,0x02,0x00,0x07, 
0xBC,0x0C,0x00,0x03, 
0xBC,0x08,0x02,0x01, 
0xBC,0x0E,0x0a,0x20, 
0xBC,0x10,0x4f,0x71, 
0xBC,0x12,0x8d,0xa3, 
0xBC,0x14,0xb3,0xc0,
0xBC,0x16,0xcc,0xd5, 
0xBC,0x18,0xdd,0xe4, 
0xBC,0x1A,0xeb,0xf0, 
0xBC,0x1C,0xf6,0xfb, 
0xBC,0x1E,0xFf,0x00, 
0xc8,0x1c,0x00,0x14, 
0x00,0x40,0x80,0x02, 
0x36,0x40,0x03,0x70,	
0x36,0x42,0x30,0xE8,	
0x36,0x44,0x0A,0xCF,	
0x36,0x46,0x62,0xCC,	
0x36,0x48,0xA4,0x2F,	
0x36,0x4A,0x02,0xD0,	
0x36,0x4C,0xB9,0xAB,	
0x36,0x4E,0x1B,0x0F,	
0x36,0x50,0x1F,0x2B,	
0x36,0x52,0x99,0x0F,	
0x36,0x54,0x02,0xD0,	
0x36,0x56,0xBD,0x89,	
0x36,0x58,0x4F,0x2E,	
0x36,0x5A,0x81,0x2A,	
0x36,0x5C,0xAF,0xCE,	
0x36,0x5E,0x03,0x90,	
0x36,0x60,0x9E,0xC9,	
0x36,0x62,0x16,0xCF,	
0x36,0x64,0x11,0x0D,	
0x36,0x66,0xBF,0xCF,	
0x36,0x80,0x0B,0x8C,	
0x36,0x82,0x94,0x6E,	
0x36,0x84,0xB1,0x4D,	
0x36,0x86,0x51,0xCE,	
0x36,0x88,0x0E,0xEF,	
0x36,0x8A,0x51,0x0A,	
0x36,0x8C,0x85,0x2E,	
0x36,0x8E,0x13,0xAB,	
0x36,0x90,0x20,0xEE,	
0x36,0x92,0x5F,0x6D,	
0x36,0x94,0x07,0xEC,	
0x36,0x96,0xDB,0x4D,	
0x36,0x98,0x03,0xAE,	
0x36,0x9A,0x1F,0xAE,	
0x36,0x9C,0xE3,0xCD,	
0x36,0x9E,0x00,0xED,	
0x36,0xA0,0xC4,0x0D,	
0x36,0xA2,0x46,0xCB,	
0x36,0xA4,0x1F,0x4E,	
0x36,0xA6,0x28,0xAB,	
0x36,0xC0,0x7E,0xED,	
0x36,0xC2,0x09,0x8D,	
0x36,0xC4,0x89,0xF1,	
0x36,0xC6,0x95,0xEE,	
0x36,0xC8,0x47,0xCF,	
0x36,0xCA,0x2B,0xCE,	
0x36,0xCC,0xC7,0x08,	
0x36,0xCE,0x8E,0xD1,	
0x36,0xD0,0x06,0x0D,	
0x36,0xD2,0x21,0xF0,	
0x36,0xD4,0x6D,0x0D,	
0x36,0xD6,0xC7,0x2E,	
0x36,0xD8,0x93,0x71,	
0x36,0xDA,0x05,0xF0,	
0x36,0xDC,0x73,0xD0,	
0x36,0xDE,0x3D,0x8D,	
0x36,0xE0,0x12,0x0D,	
0x36,0xE2,0x89,0xD1,	
0x36,0xE4,0xEB,0xCD,	
0x36,0xE6,0x29,0xD0,	
0x37,0x00,0xA6,0x6E,	
0x37,0x02,0x65,0xCF,	
0x37,0x04,0x02,0x51,	
0x37,0x06,0xC2,0x6F,	
0x37,0x08,0xC2,0xB1,	
0x37,0x0A,0xD9,0x2C,	
0x37,0x0C,0x39,0x8F,	
0x37,0x0E,0x64,0x0E,	
0x37,0x10,0xC3,0xCF,	
0x37,0x12,0x20,0x0E,	
0x37,0x14,0x22,0x4B,	
0x37,0x16,0x1E,0x8F,	
0x37,0x18,0x97,0x30,	
0x37,0x1A,0xA1,0x6F,	
0x37,0x1C,0x33,0x11,	
0x37,0x1E,0xB8,0xAD,	
0x37,0x20,0x4B,0x8F,	
0x37,0x22,0x57,0x8F,	
0x37,0x24,0xCE,0x6F,	
0x37,0x26,0xF4,0xCF,	
0x37,0x40,0x95,0xAE,	
0x37,0x42,0x97,0xAF,	
0x37,0x44,0x71,0xAC,	
0x37,0x46,0x15,0x8D,	
0x37,0x48,0x1F,0x72,	
0x37,0x4A,0x9A,0x4F,	
0x37,0x4C,0xCA,0x6D,	
0x37,0x4E,0x02,0xD1,	
0x37,0x50,0x17,0x8F,	
0x37,0x52,0xF1,0x2F,	
0x37,0x54,0xDC,0xCE,	
0x37,0x56,0x07,0x10,	
0x37,0x58,0x05,0xB2,	
0x37,0x5A,0xDB,0x11,	
0x37,0x5C,0xC6,0x32,	
0x37,0x5E,0x8B,0xCE,	
0x37,0x60,0x99,0x2F,	
0x37,0x62,0x07,0x90,	
0x37,0x64,0x63,0xCD,	
0x37,0x66,0x39,0xD0,	
0x37,0x82,0x00,0xD8,	
0x37,0x84,0x01,0x3C,	
0x32,0x10,0x02,0xb8,	
0x09,0x8E,0x48,0x60, 
0xc8,0x60,0x01,0x00, 
0xc8,0x61,0x00,0x00, 
0x09,0x8E,0x48,0x61, 
0x00,0x40,0x80,0x02, 
0x09,0x8E,0x48,0x02, 
0xc8,0x02,0x00,0x10, 
0xc8,0x06,0x02,0x97, 
0xc8,0x04,0x01,0xf3, 
0xc8,0x14,0x01,0xe3, 
0xc8,0x0e,0x02,0x0d, 
0xc8,0x48,0x00,0x00, 
0xc8,0x4a,0x00,0x00, 
0xc8,0x4c,0x02,0x80, 
0xc8,0x4e,0x01,0xe0, 
0xc8,0x54,0x02,0x80, 
0xc8,0x56,0x01,0xe0, 
0xc8,0x50,0x03,0x42, 
0xc8,0xf0,0x02,0x7f, 
0xc8,0xf2,0x01,0xdf, 
0xc8,0xf4,0x00,0x04, 
0xc8,0xf6,0x00,0x04, 
0xc8,0xf8,0x00,0x7e, 
0xc8,0xfa,0x00,0x5e, 
0xdc,0x00,0x28,0x00, 
//0xc8,0x28,0x00,0x00, 	//modify by seven 2011-06-22
0xc8,0x28,0x00,0x02, 
		       //delay = 10
0xc9,0x05,0x02,0x00, 
0xc9,0x08,0x03,0x00, 
		       //delay = 10 
0x09,0x8e,0x48,0x18, 
0x09,0x90,0x00,0x9b,  //open streaming


0x09,0x8E,0x48,0x48,  //VGA streaming
0x09,0x90,0x00,0x00,
0x09,0x8E,0x48,0x4A,
0x09,0x90,0x00,0x00,
0x09,0x8E,0x48,0x4C,
0x09,0x90,0x02,0x80,
0x09,0x8E,0x48,0x4E,
0x09,0x90,0x01,0xE0,
0x09,0x8E,0x48,0x54,
0x09,0x90,0x02,0x80,
0x09,0x8E,0x48,0x56,
0x09,0x90,0x01,0xe0,
0x09,0x8E,0xC8,0x50,
0x09,0x90,0x03,0x00,
0x09,0x8E,0x48,0xF0,
0x09,0x90,0x02,0x7F,
0x09,0x8E,0x48,0xF2,
0x09,0x90,0x01,0xdF,
0x09,0x8E,0x48,0xF4,
0x09,0x90,0x00,0x04,
0x09,0x8E,0x48,0xF6,
0x09,0x90,0x00,0x04,
0x09,0x8E,0x48,0xF8,
0x09,0x90,0x00,0x7e,
0x09,0x8E,0x48,0xFA,
0x09,0x90,0x00,0x5e,
0x09,0x8E,0xDC,0x00,
0x09,0x90,0x28,0x00,
0x09,0x8e,0x48,0x16,
0x09,0x90,0x00,0x83,
0xdc,0x00,0x28,0x31,
0x00,0x40,0x80,0x02,
										//delay = 10 //VGA streaming

0x09,0x8E,0x48,0x28,
//0xc8,0x28,0x00,0x00, //modify by seven 2011-06-22
0xc8,0x28,0x00,0x02, 
0xdc,0x00,0x28,0x31, 
0x00,0x40,0x80,0x02, 
										//delay = 30  //normal[flip section]

0x09,0x8E,0x48,0x69,  //brightness
0x09,0x90,0x38,0x00, 

0x09,0x8E,0x48,0x60,  //Hue
0x09,0x90,0x01,0x00,
0x09,0x8E,0x48,0x61,
0x09,0x90,0x00,0x00,
0x00,0x40,0x80,0x02,

0x09,0x8E,0x49,0x05,  //sharpness
0x09,0x90,0x02,0x00,
0x09,0x8E,0x49,0x08,
0x09,0x90,0x02,0x00,
//modify by seven 2011-6-7
//Enable auto exposure
#if 0
0x09,0x8E,0x28,0x04,
0xA8,0x04,0x00,0x1F,
0xDC,0x00,0x00,0x28,
0x00,0x40,0x80,0x02,
#endif
END_,END_,END_,END_
};

