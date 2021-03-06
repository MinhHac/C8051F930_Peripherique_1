
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_C8051F930_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]

#include "variables_globales.h"
#include "pin_test.h"
#include "time.h"

#include "clavier.h"



// [Generated Includes]$

//-----------------------------------------------------------------------------
// Prototypes de fonctions
//-----------------------------------------------------------------------------
void scheduler(void);
//-----------------------------------------------------------------------------
// Wrapper
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main (void){
	if((RSTSRC&0x02)==0x00){
		if((RSTSRC&0x08)==0x08)
		   NOP();
	}
	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();
	PCA0CPH5=0;

	IE_EA=1;

	while (1) 
   {
	while(new_task==0);
	new_task=0;
	scheduler();
   }
}

char getchar(void){
	return(get_touche());
}

void scheduler(void){

    uint8_t key;
    static uint8_t key_memoire = 0, etat_key = 0;

	static unsigned int nb_appels=0;            // declaration la variable de i qui compte pour 200 fois delay
	static unsigned int i;                      // declaration la variable de i qui compte pour 200 fois delay
	PCA0CPH5=0;                                 //
	switch(scheduler_ct) {
	    case 0: {
// etap 1
	    	//TEST=!TEST;                       // pour mesurer sur oscilloscope
	    	key = getchar();                    // fonction getchar()
	    	//TEST=!TEST;                       // pour mesurer sur oscilloscope
	    	//NOP();
// etap 2
	    	if(key==0 && etat_key!=0){
	    		key_memoire=etat_key;
	    	    etat_key=0;
	    	}else if(key!=0){
	    		etat_key=key;
	    	}
	    	if(key_memoire != 0){
	    		//TEST=!TEST;
	    		key_memoire = 0;
		    	//NOP();
	    	}
	    	break;
	    }

		case 7: {
			/*
			nb_appels++;                        // incremente nb_appels a chaque fois de case 7
			if(nb_appels==50){
				for(i=0;i<100;i++) delay(120);  //fonction delay pour 1 microseconde, pour 12 ms = 100*120 us
			}
			break;*/
		}

	}
	scheduler_ct++;
	if(scheduler_ct==10) scheduler_ct=0;

}

INTERRUPT(TIMER3_ISR,TIMER3_IRQn) {			// Timer 3 base de temps de 10ms
	TMR3CN&=~0x80;
	new_task=1;
	//TEST=!TEST;
}

