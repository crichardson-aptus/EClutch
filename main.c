/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/tmr1.h"

/*
                         Main application
 */

uint16_t dutyCycle, PotV, count, Phase, OldPhase, PauseTime;
bool flag, Forward;

void SetPhase(void);
void DriveForward(void);
void DriveReverse(void);
void TMR1ISR(void);

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    ADC1_Initialize();
    
    ADC1_Enable();
    ADC1_ChannelSelect(SpeedRef);
    TMR1_SetInterruptHandler(TMR1ISR);
    //ADC1_SoftwareTriggerEnable();
    
    dutyCycle = 0xC000;
    
    __delay32(1000);
    
    while (1)
    {
        // Add your application code
        //PWM_GeneratorEnable(PWM_A);
        
        PotV = ADC1_ConversionResultGet(SpeedRef);
        
        dutyCycle = abs(PotV-0x07FC) * 16;
        
         
        if(dutyCycle > 0xFF00)
            dutyCycle = 0xFF00;
        if(dutyCycle < 0x1000)
            dutyCycle = 0x1000;
        
        
        if(PotV > 0x07FF)
            Forward = true;
        else
            Forward = false;
        
        
        if(!SW1_GetValue()){   //!SW1_GetValue()
            LED1_SetHigh();
            
            SetPhase();
//            OldPhase = Phase;
//            
//            if(PauseTime > 8){
//                PauseTime = 0;
//                Phase = Phase + 1;
//                if(Phase > 6){
//                    Phase = 1;
//                }
//            }
            
            if(Forward){
                DriveForward();
            }
            else
                DriveReverse();
        }
            
        else{
            LED1_SetLow();
            PauseTime = 0;
            PWM_Disable();
//            PWM_GeneratorDisable(PWM_B);
//            PWM_GeneratorDisable(PWM_C);
            
            
            A_High_SetLow();
            A_Low_SetLow();
            B_High_SetLow();
            B_Low_SetLow();
            C_High_SetLow();
            C_Low_SetLow();
            PWM_GeneratorEnable(PWM_A);
            PWM_DutyCycleSet(PWM_A, 0x0000);
            PWM_Disable();
        }
        
     
    }
    return 1; 
}

void SetPhase(void)
{
    //Phase1
    if(HALL_C_GetValue() && !HALL_B_GetValue() && HALL_A_GetValue()){
        Phase = 1;

    }

    //Phase 2
    else if(HALL_C_GetValue() && !HALL_B_GetValue() && !HALL_A_GetValue()){
        Phase = 2;
    }

    //Phase 3
    else if(HALL_C_GetValue() && HALL_B_GetValue() && !HALL_A_GetValue()){
        Phase = 3;
    }

    //Phase 4
    else if(!HALL_C_GetValue() && HALL_B_GetValue() && !HALL_A_GetValue()){
        Phase = 4;
    }

    //Phase 5
    else if(!HALL_C_GetValue() && HALL_B_GetValue() && HALL_A_GetValue()){
        Phase = 5;
    }

    //Phase 6
    else if(!HALL_C_GetValue() && !HALL_B_GetValue() && HALL_A_GetValue()){
        Phase = 6;
    }
}
void DriveForward(void)
{
    //Phase1
    if(Phase == 1){
        PWM_GeneratorDisable(PWM_B);
        PWM_GeneratorDisable(PWM_C);
        PWM_GeneratorEnable(PWM_A);
        PWM_DutyCycleSet(PWM_A, dutyCycle);

        
        
        B_Low_SetHigh();   
        
        //A_High_SetLow();
        B_High_SetLow();
        C_High_SetLow();
        
        //A_Low_SetLow();
        //B_Low_SetLow();
        C_Low_SetLow();

    }

    //Phase 2
    else if(Phase == 2){
        PWM_GeneratorDisable(PWM_A);
        PWM_GeneratorDisable(PWM_B);
        PWM_GeneratorEnable(PWM_C);
        PWM_DutyCycleSet(PWM_C, dutyCycle);

        
        
        B_Low_SetHigh();

        A_High_SetLow();
        A_Low_SetLow();
        B_High_SetLow();
        //B_Low_SetLow();
        //C_High_SetLow();
        //C_Low_SetLow();
    }

    //Phase 3
    else if(Phase == 3){
        PWM_GeneratorDisable(PWM_A);
        PWM_GeneratorDisable(PWM_B);
        PWM_GeneratorEnable(PWM_C);
        PWM_DutyCycleSet(PWM_C, dutyCycle);

        

        A_Low_SetHigh();

        A_High_SetLow();
        //A_Low_SetLow();
        B_High_SetLow();
        B_Low_SetLow();
        //C_High_SetLow();
        //C_Low_SetLow();
    }

    //Phase 4
    else if(Phase == 4){
        PWM_GeneratorDisable(PWM_A);
        PWM_GeneratorDisable(PWM_C);
        PWM_GeneratorEnable(PWM_B);
        PWM_DutyCycleSet(PWM_B, dutyCycle);

        

        A_Low_SetHigh();

        A_High_SetLow();
        //A_Low_SetLow();
        //B_High_SetLow();
        //B_Low_SetLow();
        C_High_SetLow();
        C_Low_SetLow();
    }

    //Phase 5
    else if(Phase == 5){
        PWM_GeneratorDisable(PWM_A);
        PWM_GeneratorDisable(PWM_C);
        PWM_GeneratorEnable(PWM_B);
        PWM_DutyCycleSet(PWM_B, dutyCycle);

        

        C_Low_SetHigh();

        A_High_SetLow();
        A_Low_SetLow();
        //B_High_SetLow();
        //B_Low_SetLow();
        C_High_SetLow();
        //C_Low_SetLow();
    }

    //Phase 6
    else if(Phase == 6){
        PWM_GeneratorDisable(PWM_B);
        PWM_GeneratorDisable(PWM_C);
        PWM_GeneratorEnable(PWM_A);
        PWM_DutyCycleSet(PWM_A, dutyCycle);

        

        C_Low_SetHigh();

        //A_High_SetLow();
        //A_Low_SetLow();
        B_High_SetLow();
        B_Low_SetLow();
        C_High_SetLow();
        //C_Low_SetLow();
    }
}

void DriveReverse(void)
{
    //Phase1
    if(Phase == 1){  
        PWM_GeneratorDisable(PWM_A);
        PWM_GeneratorDisable(PWM_C);
        PWM_GeneratorEnable(PWM_B);
        PWM_DutyCycleSet(PWM_B, dutyCycle);

        
        
        A_Low_SetHigh();  
        
        A_High_SetLow();
        //A_Low_SetLow();
        //B_High_SetLow();
        //B_Low_SetLow();
        C_High_SetLow();
        C_Low_SetLow();

    }

    //Phase 2
    else if(Phase == 2){
        PWM_GeneratorDisable(PWM_A);
        PWM_GeneratorDisable(PWM_C);
        PWM_GeneratorEnable(PWM_B);
        PWM_DutyCycleSet(PWM_B, dutyCycle);

        
        
        C_Low_SetHigh();

        A_High_SetLow();
        A_Low_SetLow();
        //B_High_SetLow();
        //B_Low_SetLow();
        C_High_SetLow();
        //C_Low_SetLow();
    }

    //Phase 3
    else if(Phase == 3){
        PWM_GeneratorDisable(PWM_C);
        PWM_GeneratorDisable(PWM_B);
        PWM_GeneratorEnable(PWM_A);
        PWM_DutyCycleSet(PWM_A, dutyCycle);

        


        C_Low_SetHigh();

        //A_High_SetLow();
        //A_Low_SetLow();
        B_High_SetLow();
        B_Low_SetLow();
        C_High_SetLow();
        //C_Low_SetLow();
    }

    //Phase 4
    else if(Phase == 4){
        PWM_GeneratorDisable(PWM_B);
        PWM_GeneratorDisable(PWM_C);
        PWM_GeneratorEnable(PWM_A);
        PWM_DutyCycleSet(PWM_A, dutyCycle);

        

        B_Low_SetHigh();

        //A_High_SetLow();
        //A_Low_SetLow();
        B_High_SetLow();
        //B_Low_SetLow();
        C_High_SetLow();
        C_Low_SetLow();
    }

    //Phase 5
    else if(Phase == 5){
        PWM_GeneratorDisable(PWM_B);
        PWM_GeneratorDisable(PWM_A);
        PWM_GeneratorEnable(PWM_C);
        PWM_DutyCycleSet(PWM_C, dutyCycle);

        

        B_Low_SetHigh();

        A_High_SetLow();
        A_Low_SetLow();
        B_High_SetLow();
        //B_Low_SetLow();
        //C_High_SetLow();
        //C_Low_SetLow();
    }

    //Phase 6
    else if(Phase == 6){
        PWM_GeneratorDisable(PWM_B);
        PWM_GeneratorDisable(PWM_A);
        PWM_GeneratorEnable(PWM_C);
        PWM_DutyCycleSet(PWM_C, dutyCycle);

        

        A_Low_SetHigh();

        A_High_SetLow();
        //A_Low_SetLow();
        B_High_SetLow();
        B_Low_SetLow();
        //C_High_SetLow();
        //C_Low_SetLow();
    }
}

void TMR1ISR(void)
{
    PauseTime++;
}
/**
 End of File
*/

