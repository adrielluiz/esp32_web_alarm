#include <Arduino.h>
#include <EEPROM.h>
#include "hw.h"

extern volatile int num_alarms_saved;
extern Alarme alarme[MAX_ALARMES];

void hw_eeprom_zero(void)
{
	EEPROM.begin(EEPROM_SIZE);
	for(uint16_t i=0; i<=EEPROM_SIZE; i++)
	{
		EEPROM.write(i,0);
        Serial.print("Erasing byte: ");
        Serial.println(i);
    }
	EEPROM.commit();
    Serial.println("Full memory erase!");
}

void hw_eeprom_save_num_total(void)
{
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.write(EEPROM_NUM_ALARMS_POS, num_alarms_saved);
    EEPROM.commit();
    
    Serial.print("Save total de alarmes: ");
    Serial.println(num_alarms_saved);
    
}

void hw_eeprom_read_num_total(void)
{
     EEPROM.begin(EEPROM_SIZE);
     num_alarms_saved = EEPROM.read(EEPROM_NUM_ALARMS_POS);
     
     Serial.print("Read total de alarmes: ");
     Serial.println(num_alarms_saved);

}

void hw_eeprom_save_alarm(int numero_alarme)
{
    int salto = 1 + numero_alarme*10;
    EEPROM.begin(EEPROM_SIZE);
   
    EEPROM.write(0+salto , alarme[numero_alarme].hora);
    EEPROM.write(1+salto , alarme[numero_alarme].minuto);
    EEPROM.write(2+salto , alarme[numero_alarme].dia_semana[0]);
    EEPROM.write(3+salto , alarme[numero_alarme].dia_semana[1]);
    EEPROM.write(4+salto , alarme[numero_alarme].dia_semana[2]);
    EEPROM.write(5+salto , alarme[numero_alarme].dia_semana[3]);
    EEPROM.write(6+salto , alarme[numero_alarme].dia_semana[4]);
    EEPROM.write(7+salto , alarme[numero_alarme].dia_semana[5]);
    EEPROM.write(8+salto , alarme[numero_alarme].dia_semana[6]);
    EEPROM.write(9+salto , alarme[numero_alarme].acionado);

    EEPROM.commit();
    //salto = salto+10;    
	
    Serial.print("Alarme salvo: ");
    Serial.println(num_alarms_saved);
}

void hw_eeprom_save_all_alarms(void)
{
    static uint32_t deslocamento = 1;
    EEPROM.begin(EEPROM_SIZE);

    for (uint16_t pos=0; pos < num_alarms_saved; pos++)
    {
        EEPROM.write(0 + deslocamento, alarme[pos].hora);
        EEPROM.write(1 + deslocamento, alarme[pos].minuto);
        EEPROM.write(2 + deslocamento, alarme[pos].dia_semana[0]);
        EEPROM.write(3 + deslocamento, alarme[pos].dia_semana[1]);
        EEPROM.write(4 + deslocamento, alarme[pos].dia_semana[2]);
        EEPROM.write(5 + deslocamento, alarme[pos].dia_semana[3]);
        EEPROM.write(6 + deslocamento, alarme[pos].dia_semana[4]);
        EEPROM.write(7 + deslocamento, alarme[pos].dia_semana[5]);
        EEPROM.write(8 + deslocamento, alarme[pos].dia_semana[6]);
        EEPROM.write(9 + deslocamento, alarme[pos].acionado);

        EEPROM.commit();
        deslocamento = deslocamento + 10;
    }
}

void hw_eeprom_read_alarms(void)
{
    static uint32_t salto_posicao = 1;
    EEPROM.begin(EEPROM_SIZE);
    
    for(uint32_t indice=0; indice<num_alarms_saved; indice++)
    {
        alarme[indice].hora = EEPROM.read(indice+salto_posicao);
        alarme[indice].minuto = EEPROM.read(indice+salto_posicao+1);
        alarme[indice].dia_semana[0] = EEPROM.read(indice+salto_posicao+2);
        alarme[indice].dia_semana[1] = EEPROM.read(indice+salto_posicao+3);
        alarme[indice].dia_semana[2] = EEPROM.read(indice+salto_posicao+4);
        alarme[indice].dia_semana[3] = EEPROM.read(indice+salto_posicao+5);
        alarme[indice].dia_semana[4] = EEPROM.read(indice+salto_posicao+6);
        alarme[indice].dia_semana[5] = EEPROM.read(indice+salto_posicao+7);
        alarme[indice].dia_semana[6] = EEPROM.read(indice+salto_posicao+8);
        alarme[indice].acionado = EEPROM.read(indice+salto_posicao+9);
        
        salto_posicao = salto_posicao+9;      
        
        Serial.print("Alarme lido ");
        Serial.print(indice);
        Serial.print(": ");
        Serial.print(alarme[indice].hora);
        Serial.print("\t");
        Serial.print(alarme[indice].minuto);
        Serial.print("\n");
    }

}

bool hw_eeprom_read_flag_reiniciar(void)
{
    EEPROM.begin(EEPROM_SIZE);
    return EEPROM.readBool(POSICAO_FLAG_REINICIAR);     
}

void hw_eeprom_write_flag_reiniciar(bool value)
{
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.writeBool(POSICAO_FLAG_REINICIAR, value);
    EEPROM.commit();
}