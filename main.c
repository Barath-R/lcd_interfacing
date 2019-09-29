#include<pic.h>
unsigned char d[]="INTERFACING LM35";
unsigned char c[]="TEMPERATURE:";
void delay(unsigned int dely){
int i,j;
for(i=0;i<dely;i++){
for(j=0;j<1257;j++);
}
}
void lcdcmd(char y){
PORTD=y;
RC0=0;
RC1=0;
RC2=0;
delay(1);
RC2=1;
}
void write(char x){
PORTD=x;
RC0=1;
RC1=0;
RC2=0;
delay(1);
RC2=1;
}
void display(int x){
int b,a1,i;
b=0x30+(x/0x0A);
a1=0x30+(x%0x0A);
lcdcmd(0x3c);
lcdcmd(0xc0);
for(i=0;i<12;i++){
write(c[i]);
}
lcdcmd(0x01);
write(b);
write(a1);
//write((a1*10)+b);
}
void main(){
unsigned int i;
unsigned int result;
TRISC=0x00;
TRISD=0x00;

ADCON1=0x8E;
ADCON0=0x41;
TRISA=0x01;
TRISB=0x00;
delay(2);
lcdcmd(0x0E);

lcdcmd(0x01);

lcdcmd(0x06);

lcdcmd(0x80);

for(i=0;i<16;i++){
write(d[i]);
}
delay(700);
while(1){
ADGO=1;
while(ADGO);
result=((ADRESH<<8)+ADRESL);
result = result*0.488281;
display(result);

}
}

