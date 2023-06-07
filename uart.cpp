#include "uart.h"

void USART2_Init(void){

 RCC->APB1ENR  |=  0x20000; //enabling the power interface clock R/W

 RCC->AHB1ENR   |=0x01; //enabling Timer

 
GPIOA->MODER &=~0x00F0; //clears mode settings for configuration
GPIOA->MODER |= 0x00A0; //configure for alternate function

 GPIOA->AFR[0] &= ~0xFF00; //clear GPIOA function
 GPIOA->AFR[0] |= 0x7700; //set GPIOA function to 


USART2->BRR  =  0x0683;
USART2->CR1  =  0x000C; //enable RE and TE
USART2->CR2  =  0x000; //clearing CR2
USART2->CR3  =  0x000; //clearing CR3
USART2->CR1  |=  0x2000; //enable LIN-mode for CR1
	
	

}

int USART2_write(int ch){

	while(!(USART2->SR & 0x0080)){} // while USART2 Serial register has not detected a LIN-break flag, continue
	USART2->DR = (ch & 0xFF); // enabling reading and writing to the Data Registers 8bits, in this case writing
	
  return ch; //returning the stored value from DR
}

int USART2_read(void){
  while(!(USART2->SR & 0x0020)){} // While transmission is NOT complete, continue
	return USART2->DR; //returning bits from Data register
}

struct __FILE { int handle; };
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};


int fgetc(FILE *f) {
    int c;

    c = USART2_read();      

    if (c == '\r') {        
        USART2_write(c);    
        c = '\n';
    }

    USART2_write(c);        

    return c;
}



int fputc(int c, FILE *f) {
    return USART2_write(c);  
}


int n;
char str[80];
		
void test_setup(void){
	
	printf("please enter a number: ");
	scanf("%d", &n);
	printf("the number entered is: %d\r\n", n);
	printf("please type a character string: ");
	gets(str);
	printf("the character string entered is: ");
	puts(str);
	printf("\r\n");
	
}
