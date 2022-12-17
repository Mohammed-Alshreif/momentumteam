////PORT B
//#define PORTB (*(volatile unsigned int*)(0x25))
//#define DDRB (*(volatile unsigned int*)(0x24))
//#define PINB (*(volatile unsigned int*)(0x23))
////PORT C
//#define PORTC (*(volatile unsigned int*)(0x28))
//#define DDRC (*(volatile unsigned int*)(0x27))
//#define PINC (*(volatile unsigned int*)(0x26))
////PORT D
//#define PORTD (*(volatile unsigned int*)(0x2B))
//#define DDRD (*(volatile unsigned int*)(0x2A))
//#define PIND (*(volatile unsigned int*)(0x29))

//===============================================================================

#define setpit(port,pin)    (port|=(1<<pin))
#define clearpit(port,pin)  (port&=~(1<<pin))
#define toglpit(port,pin)   (port^=(1<<pin))
#define readpit(port,pin)   ((port>>pin)&1)
#define setport(port)       (port=0xff)

//===============================================================================

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define KEYPAD_PORT PORTD
#define DataDir_KEYPAD_PORT DDRD
#define keypadPIN PIND
//================================================================================

#define  lCD_PORT PORTB
#define  lCD_DDR DDRB
#define  lCD_PIN PINB
#define E  0
#define RW 1
#define RS 2
#define D4 4
#define D5 5
#define D6 6
#define D7 7


#define LCD_FUNCTION_8BIT_2LINES            (0x38)
#define LCD_FUNCTION_4BIT_2LINES            (0x28)
#define LCD_MOVE_DISP_RIGHT                 (0x1C)
#define LCD_MOVE_DISP_LEFT                  (0x18)
#define LCD_MOVE_CURSOR_RIGHT               (0x14)
#define LCD_MOVE_CURSOR_LEFT                (0x10)
#define LCD_DISP_OFF                        (0x08)
#define LCD_DISP_ON_CURSOR                  (0x0E)
#define LCD_DISP_ON_CURSOR_BLINK            (0x0F)
#define LCD_DISP_ON_BLINK                   (0x0D)
#define LCD_DISP_ON                         (0x0C)
#define LCD_ENTRY_DEC                       (0x04)
#define LCD_ENTRY_DEC_SHIFT                 (0x05)
#define LCD_ENTRY_INC_                      (0x06)
#define LCD_ENTRY_INC_SHIFT                 (0x07)
#define LCD_BEGIN_AT_FIRST_ROW              (0x80)
#define LCD_BEGIN_AT_SECOND_ROW             (0xC0)
#define LCD_CLEAR_SCREEN                    (0x01)
#define LCD_ENTRY_MODE                      (0x06)
//===============================================================================
int Key_padRow[] = {R0, R1, R2, R3}; //rows of the keypad
int Key_padCol[] = {C0, C1, C2, C3};//columns
char flag1 = 1;
//===============================================================================
static unsigned flag_init=0;
//===============================================================================
  int i=10;    
  float f =10.5;
//===============================================================================
void Keypad_init() {
  DataDir_KEYPAD_PORT &= ~((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
  DataDir_KEYPAD_PORT |= ((1 << C0) | (1 << C1) | (1 << C2) | (1 << C3));
  KEYPAD_PORT = 0xFF;
}

char Keypad_getkey() {
  int i, j;
  for (i = 0; i < 4; i++) {
    KEYPAD_PORT |= ((1 << Key_padCol[0]) | (1 << Key_padCol[1]) | (1 << Key_padCol[2]) | (1 << Key_padCol[3]));
    KEYPAD_PORT &= ~(1 << Key_padCol[i]);
    for (j = 0; j < 4; j++) {
      if (!(keypadPIN & (1 << Key_padRow[j])))
      {
        if (flag1 == 1) {
          flag1 = 0;
          switch (i) {
            case (0):
              if (j == 0) return '7';
              else if (j == 1) return '4';
              else if (j == 2) return '1';
              else if (j == 3) return '?';
              break;
            case (1):
              if (j == 0) return '8';
              else if (j == 1) return '5';
              else if (j == 2) return '2';
              else if (j == 3) return '0';
              break;
            case (2):
              if (j == 0) return '9';
              else if (j == 1) return '6';
              else if (j == 2) return '3';
              else if (j == 3) return '=';
              break;
            case (3):
              if (j == 0) return '/';
              else if (j == 1) return '*';
              else if (j == 2) return '-';
              else if (j == 3) return '+';
              break;
          }
        }

      }
      else flag1 = 1;
    }
  }
  return 'A';
}

//===============================================================================
void LCD_SEND_EN(){
  setpit(lCD_PORT,E);
  delay (1);
  clearpit(lCD_PORT,E);
}
void LCD_write_CMD(char CMD){
  clearpit(lCD_PORT,RS);
  clearpit(lCD_PORT,RW);
  //for left 4 pit HSP 
  lCD_PORT &=~(0b1111<<4);
  lCD_PORT |=((CMD>>4)<<4);
  LCD_SEND_EN();
  
  if(flag_init)
  {
    //for right 4 pit LSP 
  lCD_PORT &=~(0b1111<<4);
  lCD_PORT |=(CMD<<4);
  LCD_SEND_EN();
  
  }
  delay (2);
}
void LCD_Init(){
  flag_init=0;
  setport(lCD_DDR);
  delay (20);
  LCD_write_CMD(0x20);
  LCD_write_CMD(0x20);
  LCD_write_CMD(0x80);// 2 line and 5x7 pixel N=1 f=0
  delay (1);
  LCD_write_CMD(0x00);
  LCD_write_CMD(0xC0);//cerser
  delay (1);
  LCD_write_CMD(0x00);
  LCD_write_CMD(0x10);
  delay (2);
  
  flag_init=1;
}
void LCD_write_data(char data){
  setpit(lCD_PORT,RS);
  clearpit(lCD_PORT,RW);
  //for left 4 pit HSP
  lCD_PORT &=~(0b1111<<4);
  lCD_PORT |=((data>>4)<<4);
  LCD_SEND_EN();
  
  //for right 4 pit LSP
  lCD_PORT &=~(0b1111<<4);
  lCD_PORT |=(data<<4);
  LCD_SEND_EN();
    
  
  delay (1);
}
void LCD_write_string(char* data){
  setpit(lCD_PORT,RS);
  clearpit(lCD_PORT,RW);
  
  while((*data)!=0){
    
  LCD_write_data(*data);
    data++;
  }
  
}
void LCD_setcerser(char ROW , char COL){
  volatile unsigned char addres ;
  if(ROW<2 && COL<16){
    addres =(0x40 * ROW) + COL ;
    setpit(addres,7);
  }
  
  LCD_write_CMD(addres);
}
void LCD_clear(){
  LCD_write_CMD(LCD_CLEAR_SCREEN);
}

void LCD_write_FLOATnumber(float num,unsigned char digit){
  char text[20];
  dtostrf(num,0,digit,text);
  LCD_write_string(text);
}
void LCD_write_INTnumber(int num){
  char text[20];
  sprintf(text,"%d",num);
  LCD_write_string(text);
}
//===============================================================================
//===============================================================================

void setup() {
  LCD_Init();
  Keypad_init();
}

void loop() {
    delay (1);
    LCD_write_data(Keypad_getkey());
    LCD_write_string(" moalshreif ");
    LCD_write_INTnumber(i);
    LCD_setcerser(1,0);
    LCD_write_FLOATnumber(f,4);
    LCD_write_string("m");
    delay (1);
    LCD_clear();
    i--;
    f=f-.5f;
}
