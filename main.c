
#include <stdint.h>
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTA_DATA_R		(*((volatile unsigned long *)0x40004000))
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x40005000))
#define GPIO_PORTA_DIR_R		(*((volatile unsigned long *)0x40004400))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTA_DEN_R		(*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define clear_display     		0x01
#define returnHome        		0x02
#define moveCursorRight   		0x06
#define moveCursorLeft    		0x08
#define shiftDisplayRight 		0x1C
#define shiftDisplayLeft  		0x18
#define cursorBlink       		0x0F
#define cursorOff         		0x0C
#define cursorOn          		0x0E
#define Function_set_4bit 		0x28
#define Function_set_8bit 		0x38
#define Entry_mode        		0x06
#define Function_8_bit    		0x32
#define Set5x7FontSize    		0x20
#define FirstRow          		0x80
unsigned long delay;
void LCD_CMD(unsigned char c);
void init(void);
void LCD_Datei_Schreib(unsigned char Datei);
void Aufschiebung_ms(uint16_t zeit);
void Aufschiebung_us(uint8_t zeit);

void init(void){
	SYSCTL_RCGC2_R |= 0x00000003;   //fängt die Uhr der beiden Port A und B
	delay = SYSCTL_RCGC2_R;         //warte auf die Uhr, zu starten
	GPIO_PORTA_DIR_R |= 0x0000001C; //verwend bloß 2,3,4 pins
	GPIO_PORTB_DIR_R |= 0x000000FF; //verwend allen Pins
	GPIO_PORTA_DEN_R |= 0x0000001C;
	GPIO_PORTB_DEN_R |= 0x000000FF;
	LCD_CMD(0x20);   //verwend ein Display von 5 pixel länge und 7 pixel breit
	LCD_CMD(0x38);   //wähle die 4-bit Einstellung
	LCD_CMD(0x01);   //räume das Display
	LCD_CMD(0x0F);	 //cursor zwinkerung
}

void LCD_Datei_Schreib(unsigned char Datei){
	GPIO_PORTA_DATA_R = 0x00000004;
	GPIO_PORTB_DATA_R = Datei;
	GPIO_PORTA_DATA_R |= 0x00000010;
	GPIO_PORTA_DATA_R = 0x00000000;
	Aufschiebung_us(0);
}

void LCD_CMD(unsigned char command){
	GPIO_PORTA_DATA_R = 0x00000000;
	GPIO_PORTB_DATA_R = command;
	GPIO_PORTA_DATA_R = 0x00000010;
	Aufschiebung_us(0);
	GPIO_PORTA_DATA_R = 0x00000000;
	if(command < 4){
		Aufschiebung_ms(2);
	}
	else{
		Aufschiebung_us(40);
	}
}


void Aufschiebung_ms(uint16_t zeit){
	int i,j;
	for(i = 0 ; i < zeit ; i++){
		for(j = 0 ; j < 3180 ; j++){
			// verschwinde zeit
		}
	}
}

void Aufschiebung_us(uint8_t zeit){
	int k,l;
	for(k = 0 ; k < zeit ; k++){
		for(l = 0 ; l < 3 ; l++){
			// verschwinde zeit
		}
	}
}
/**
 * main.c
 */
int main(void)
{
	init();
	while(1){
		LCD_CMD(0x01);
		LCD_CMD(0x80);
		Aufschiebung_ms(500);
		LCD_Datei_Schreib('P');
		Aufschiebung_ms(1);
	}
}
