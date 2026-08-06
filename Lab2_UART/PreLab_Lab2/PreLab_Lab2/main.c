/*
 * PreLab_Lab2.c
 *
 * Created: 30/07/2026 4:39:28 pm
 * Author : Mayita Denenga
 */ 

#include <avr/io.h>
#include <stdbool.h>

bool check_prime(uint16_t chk_no);

int main(void)
{
	uint16_t count = 1;
	uint16_t myPrimes[63] = {1};
		
    for (uint16_t num=2; num<=300; num++){
	    if (check_prime(num)){
		    myPrimes[count] = num;
			count++;
	    }
    }
	while (1) 
    {
	}
}

bool check_prime(uint16_t chk_no){
	for(uint16_t i=2; i < chk_no; i++){
		if ((chk_no % i) == 0){
			return false;
		}
	}
	return true;
}

