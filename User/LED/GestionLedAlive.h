/*
 * GestionLedAlive.h
 *
 *  Created on: 9 août 2021
 *  Original Author: j.proux
 *
 *  Updated on: 31 Janv. 2024
 *  Updated by: j.proux
 *
 *  History Usage :
 *-> 09/08/2021 : Added by Jp to RMD_Firmware (STM32G0B1CETx : productprojects/ventilation/tertiaire/rmd/rmd_firmware)
 *-> 06/12/2021 : Added by BC to HII_Manta_App (STM32G070CBTx : productprojects/ventilation/individuel/himalaya2/manta/h2_manta_app)
 *-> 04/01/2022 : Added by Jp to HII_CarteMere_App (STM32F732VETx : productprojects/ventilation/individuel/himalaya2/carte-mere/h2_cartemere_app)
 *-> 10/01/2024 : Added by Jp to HII_CarteMere_Bootloader (STM32F732VETx : productprojects/ventilation/individuel/himalaya2/carte-mere/h2_cartemere_bootloader)
 *
 */

#ifndef LED_GESTIONLEDALIVE_H_
#define LED_GESTIONLEDALIVE_H_

/*******************************************************************************************
* Procédure pour intégrer facilement cette Librairie "GestionLed" dans un nouveau projet : *
********************************************************************************************

 +-----------------------------+
 | Etape I : Configurer CubeMX |
 +-----------------------------+

I.1 ) Dans CubeMX, Configurer la (ou les) pin(s) concernée(s) en "GPIO_Output"

I.2) Dans "System Core" -> "GPIO" -> "GPIO Mode and Configuration" -> Onglet "GPIO",
 Pour chaque pin concernée, configurer les options ainsi :
  -> GPIO output level = "Low"
  -> GPIO mode = "Output Push Pull"
  -> GPIO Pull-up/Pull-down = "No pull-up and no pull-down"
  -> Maximum output speed = "Low" ("Low" est généralement suffisant pour notre usage)
  -> User Label : Indiquer le nom de la fonction associée, par exemple "Status_Led"

I.3) Dans l'onglet général "Project Manager" -> "Advanded Settings" -> "Driver Selector" :
-> s'assurer que GPIO soit bien configuré de type "HAL"


 +-----------------------------------+
 | Etape II : Configurer le Projet : |
 +-----------------------------------+

II.1) Ajouter l'Include du .h dans le "main.c" (par exemple parmi les "USER CODE * Includes"),
 ainsi qu'une Base de Temps appropriée (par exemple dans la zone "USER CODE * Includes" du .c
 de la Librairie "BaseDeTemps") :
	#include "GestionLedAlive.h"

II.2) Ajouter l'appel d'Init dans le "main" du "main.c" (par exemple parmi les "USER CODE * 2") :
	InitGestionLed();

II.3) Ajouter le Handler @ 100ms dans une sous-partie de la Boucle Principale (RT) à 100ms :
(par exemple dans la zone @ 100ms "USER CODE * RT_100ms" de "GestionBaseDeTemps" ("BaseDeTemps.c")
	Handle_GestionLed_RT_100ms();

II.4) Ajouter le Dossier "LED" à l "'IncludePath" pour toutes les Configs de Build
(Attention : CubeIDE a l'habitude de stocker les chemins relatifs au Workspace, et non au Dossier)
-> il est souvent préférable d'utiliser la formulation "../User/LED" (sans les guillemets)

II.5) Vérifier que le Dossier "LED" ne soit "Exclude From Build" d'aucune des Configs.
  (y compris "Debug" & "Release")
Info : Pour vérifier, sélectionner "Properties" du Dossier -> "C/C++ Build" -> "Settings".

=> Félicitations, c'est prêt :-) !

*******************************************************************************************/

typedef enum
{
	E_LED_ETEINTE = 0,		// La Led sera maintenue éteinte
	E_LED_FIXE,				// La Led sera maintenue allumée en permanence
	E_LED_CLIGN_LENT,		// La Led va effectuer un Clignotement lent
	E_LED_CLIGN_RAPIDE_1,	// La Led va effectuer le Clignotement Rapide #1
	E_LED_CLIGN_RAPIDE_2,	// La Led va effectuer le Clignotement Rapide #2
	//---------------
	E_LED_NB_ETATS // A conserver en dernier élément : indique le nb Max d'états possibles
} E_LED_BLINK_MODES;

/********************************************************************************************/

void InitGestionLed(void); 				// A appeler dans la partie Init du "main.c"

void Handle_GestionLed_RT_100ms(void);	// A appeler dans une BaseDeTemps @ 100ms

E_LED_BLINK_MODES GetBlinkMode(void); 				// Pour récupérer le Mode de Clignotement actuel
void SetBlinkMode(E_LED_BLINK_MODES newBlinkMode);	// Pour changer le Mode de Clignotement depuis l'extérieur

#endif /* LED_GESTIONLEDALIVE_H_ */
