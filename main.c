
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTA_DATA_R		(*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
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

void LCD_CMD(int command);
void init(void);
void LCD_Datei_Schreib(int Datei);
void Aufschiebung_ms(int zeit);
void Aufschiebung_us(int zeit);


void init(void){
	SYSCTL_RCGC2_R |= 0x00000001;   //fängt die Uhr der beiden Port A und B
	SYSCTL_RCGC2_R |= 0x00000002;
	delay = SYSCTL_RCGC2_R;         //warte auf die Uhr, zu starten
	GPIO_PORTA_DIR_R |= 0x0000001C; //verwend bloß 2,3,4 pins
	GPIO_PORTB_DIR_R |= 0x000000FF; //verwend allen Pins
	GPIO_PORTA_DEN_R |= 0x0000001C; //aktiviere pins 2,3,4, eine digitale Signale zu schicken
	GPIO_PORTB_DEN_R |= 0x000000FF; // aktiviere pins 0,1,2,3,4,5,6,7, eine digitale Signale zu schicken
	GPIO_PORTA_DATA_R &= ~0xFFFFFFFF;  //vorsorglichkeit
	GPIO_PORTB_DATA_R &= ~0xFFFFFFFF;  //vorsorglichkeit
	LCD_CMD(0x38);   //wähle die 8-bit Einstellung
	LCD_CMD(0x01);   //räume das Display
	LCD_CMD(0x0F);	 //cursor zwinkerung
}



void LCD_Datei_Schreib(int Datei){
	GPIO_PORTA_DATA_R |= 0x00000004;  //RS = 1
	GPIO_PORTB_DATA_R = Datei;
	GPIO_PORTA_DATA_R |= 0x00000010;
	GPIO_PORTA_DATA_R &= ~0x00000010;
	Aufschiebung_us(0);
}

void LCD_CMD(int command){
	GPIO_PORTA_DATA_R &= ~0x0000001C;  //RS = 0, R/W = 0, E = 0
	GPIO_PORTB_DATA_R = command;
	GPIO_PORTA_DATA_R |= 0x00000010;  // E=1 damit wir dem Mikrocontroller befehlen, einzuschalten
	Aufschiebung_ms(0);
	GPIO_PORTA_DATA_R &= ~0x00000010; // E=1 damit wir dem Mikrocontroller befehlen, für vorsorglichkeit auszuschalten
	if(command < 4){
		Aufschiebung_ms(0);
	}
	else{
		Aufschiebung_us(0);
	}
}


void Aufschiebung_ms(int zeit){
	int i,j;
	for(i = 0 ; i <= zeit ; i++){
		for(j = 0 ; j < 26240 ; j++){
			// verschwinde zeit
		}
	}
}

void Aufschiebung_us(int zeit){
	int k,l;
	for(k = 0 ; k <= 0 ; k++){
		for(l = 0 ; l < 640 ; l++){
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
	LCD_CMD(0x80);
	while(1){
		Aufschiebung_ms(500);
		LCD_Datei_Schreib('P');
		Aufschiebung_ms(1);
		LCD_CMD(0x06);
		LCD_Datei_Schreib('A');
	}
}
