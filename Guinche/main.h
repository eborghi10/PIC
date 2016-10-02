#include <12F675.h>

#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO
#FUSES NOCPD                    //No EE protection
#FUSES NOPROTECT                //Code not protected from reading
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BANDGAP_HIGH          
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=4000000)

#define GP0   PIN_A0
#define GP1   PIN_A1
#define GP2   PIN_A2
#define GP3   PIN_A3
#define GP4   PIN_A4
#define GP5   PIN_A5

#ROM 0x3FF={0x342C}  // VALOR DE OSCCAL PARA EL PIC12F675!!!

#define LEDS                 GP0      // LEDs indicadores de presencia/funcionamiento
#define ACTIVACION_RELE      GP1      // Salida de Relé
#define SENSOR_MOVIMIENTO    GP2      // Entrada de Interrupción externa

#define SEG_PARADA      5
#define SEG_CALIBRACION 60

BYTE tiempoTimer = 0;
BOOLEAN calibracion = TRUE;

void timer1_ON(void)
{
   tiempoTimer = 0;
   output_high(LEDS);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   enable_interrupts(INT_TIMER1);
   set_timer1(0x0BDC);
}

void timer1_OFF(void)
{
   setup_timer_1(T1_DISABLED);
   output_low(LEDS);
}

void initAll(void)
{
   set_tris_a(0b00111110);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_EXT);
   ext_int_edge(L_TO_H);
   enable_interrupts(GLOBAL);
   // NO HABILITO EL TIMER 1 !!!
   output_high(ACTIVACION_RELE);    // El relÃ© comienzo activado por defecto
   output_high(LEDS);
}
