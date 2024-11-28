/*
 * GestionLedAlive.c
 *
 *  Created on: 9 août 2021
 *  Original Author: j.proux
 *
 *  Updated on: 19 Déc. 2023
 *  Updated by: j.proux
 *
 *  Pour intégrer facilement cette Librairie "GestionLed" dans un nouveau Projet :
 *   -> Suivre la Procédure décrite dans "GestionLed.h"
 *
 */

#include <stdint.h>				// Pour les types "int*_t" & "uint*_t"
#include "GestionLedAlive.h"	// Pour accès à nos propres déclarations publiques
#include "main.h"				// Pour accès au GPIO des Leds

// Configuration de la Fonction "bas niveau" pour Allumer & Eteindre la Led concernée (cf. main.h) :
#define UPDATE_LED_STATE(a,b)	HAL_GPIO_WritePin(a##_GPIO_PORT, a##_PIN, b)
#define SET_GREEN_LED_STATE(b)	UPDATE_LED_STATE(LED1, b)

/******************************************************************************/
// Private variables :

uint16_t sabLed;
uint16_t curLed;
E_LED_BLINK_MODES BlinkMode;

/******************************************************************************/

inline __attribute__((always_inline)) void InitGestionLed(void)
{
	sabLed = 0;
	curLed = 0;
	BlinkMode = E_LED_CLIGN_LENT;	// => Clignotement "lent" en Applicatif
}

/******************************************************************************/

inline __attribute__((always_inline)) void Handle_GestionLed_RT_100ms(void) // Gestion Clignotement Led de vie
{
	if(sabLed <= 0) // <= 0 car décomptage systématique en fin de Traitement (mettre "<=1" si c'est dans Else)
	{
		curLed++;

		switch (BlinkMode) {
			case E_LED_ETEINTE:
				curLed += (curLed & 1); // Retomber sur un chiffre pair pour être sûr de la maintenir éteinte
				sabLed = 5; // Recalculer dans 5*100ms = 500ms
				break;
			case E_LED_FIXE:
				curLed |= 1; // Forcer ON
				sabLed = 5; // Recalculer dans 5*100ms = 500ms
				break;
			case E_LED_CLIGN_LENT:
				sabLed = (curLed & 1) ? 5 : 5; // 5=500ms => 500ms ON + 500ms OFF
				break;
			case E_LED_CLIGN_RAPIDE_1:
				sabLed = (curLed & 1) ? 1 : 1; // 1=100ms => 100ms ON + 100ms OFF
				break;
			case E_LED_CLIGN_RAPIDE_2:
				sabLed = (curLed & 1) ? 2 : 2; // 2=200ms => 200ms ON + 200ms OFF
				break;
			default:
				// Normalement, on ne devrait jamais passer par ici
				sabLed = 10; // Recalculer dans 10*100ms = 1s
				break;
		}
		SET_GREEN_LED_STATE(curLed & 1);
	}
	sabLed--;
}

/******************************************************************************/

E_LED_BLINK_MODES GetBlinkMode(void){
	return BlinkMode;
}

void SetBlinkMode(E_LED_BLINK_MODES newBlinkMode){
	BlinkMode = newBlinkMode;
}
