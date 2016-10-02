#include "\\SERVER\Centro de Datos\Sistemas\Emiliano Borghi\Software\Guinche\main.h"

#int_EXT
void  EXT_isr(void) 
{
   // Si se detecta una persona, se activa la interrupción externa.
   // Se debe apagar el relé durante un cierto tiempo.
   // Para ello, se activa un timer de 2,5 segundos.
   output_high(ACTIVACION_RELE);
   timer1_ON();
}

#INT_TIMER1
void TIMER1_ISR(void)   // Interrumpe aprox. cada 500 ms
{
   tiempoTimer++;
   
   if(calibracion){
      if(tiempoTimer >= (BYTE)(SEG_CALIBRACION*2)){
         tiempoTimer = 0;
         calibracion = FALSE;
      }
      else output_toggle(LEDS);
   }
      
   else if (tiempoTimer >= (BYTE)(SEG_PARADA*2)){
      tiempoTimer = 0;   // TIEMPO = 2,5 segundos
      output_low(ACTIVACION_RELE);
      timer1_OFF();      // Apaga Timer hasta nueva interrupción
   }
}

void main()
{
   initAll();
   
   while(TRUE){};
}
