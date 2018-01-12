#include <LPC214X.H>
void delay(int j )
{
int i;
//for(j=0;j<600;j++)
for(i=0;i<j;i++);
}
void data_lcd(char ch1)
{
ch1 = ch1<<16; 
IOCLR1=(0X00FF0000);
IOSET1= ch1;
IOSET0 = (1<<24);//RS
IOCLR0 = (1<<25);//RW
IOSET0 = (1<<26);//EN
delay(20);
IOCLR0 = (1<<26);//EN
	
IOCLR1=(0X00FF0000);	
ch1 = ch1<<20; 
IOSET1= ch1;//port-1
IOSET0 = (1<<24);//port-0
IOCLR0 = (1<<25);
IOSET0 = (1<<26);
delay(20);
IOCLR0 = (1<<26);	
}
void cmd_lcd(char ch)
{
ch = ch<<16; 
IOCLR1 =(0X00FF0000);

IOSET1 = ch;// port-1
IOCLR0 = (1<<24);//port-0
IOCLR0 = (1<<25);
IOSET0 = (1<<26);
delay(2);
IOCLR0 = (1<<26);	
	
IOCLR1 =(0X00FF0000);	
ch = ch<<20; 
IOSET1 = ch;
IOCLR0 = (1<<24);
IOCLR0 = (1<<25);
IOSET0 = (1<<26);
delay(2);
IOCLR0 = (1<<26);	
	
	
}
void init_lcd()
{
cmd_lcd(0x38);
cmd_lcd(0x01);
cmd_lcd(0x0c);
cmd_lcd(0x80);
}

void str_lcd(char *str)
{
while(*str)
data_lcd(*str++);
}
void time(void)
{
int i;
cmd_lcd(0x80);
str_lcd("Hour Min Sec");

  cmd_lcd(0xc0);
	i=(48+(HOUR/10));
  data_lcd(i);
	i=(48+(HOUR%10));
	data_lcd(i);

	i=(48+(MIN/10));
  data_lcd(i);
	i=(48+(MIN%10));
	data_lcd(i);

	i=(48+(SEC/10));
	data_lcd(i);
  i=(48+(SEC%10));
	data_lcd(i);

}

void SetTime(void)
{
CCR = 0x02;
HOUR = 0;
MIN = 59;
SEC = 59;
//MONTH=11;
//YEAR=17;
CCR = 0x11;
}
int main(void)
{
SetTime();
PINSEL2 = 0X00;
PINSEL1=0X00;
IODIR0=	(0X07<<24);//pin-P0.24,P0.25,P0.26
IODIR1 = (0xFF<<16);//P1.16-P.31;
init_lcd();
while (1)
{
time();
}
}
