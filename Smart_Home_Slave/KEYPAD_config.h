/***************************************************************/
/***************************************************************/
/********************** AUTHOR:  Ahmed Samir *******************/
/********************** LAYER:  HAL ***************************/
/********************** SWC:  KEYPAD ***************************/
/********************** VERSION:  1.00 *************************/

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define KEYPAD_Port  MDIO_PORTB

#define KEYPAD_Col0Pin  MDIO_PIN0
#define KEYPAD_Col1Pin  MDIO_PIN1
#define KEYPAD_Col2Pin  MDIO_PIN2
#define KEYPAD_Col3Pin  MDIO_PIN3

#define KEYPAD_Row0Pin  MDIO_PIN4
#define KEYPAD_Row1Pin  MDIO_PIN5
#define KEYPAD_Row2Pin  MDIO_PIN6
#define KEYPAD_Row3Pin  MDIO_PIN7



#define KEYPAD_NoPressedKey  0xff

#define KEYPAD_Arr 		{{255,0,'=','+'},{1,2,3,'-'},{4,5,6,'x'},{7,8,9,'/'}}

#endif /* KEYPAD_CONFIG_H_ */
