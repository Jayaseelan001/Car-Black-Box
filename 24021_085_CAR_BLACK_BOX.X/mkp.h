#ifndef MKP_H
#define	MKP_H

#define         LEVEL           0
#define         STATE_CHANGE    1

#define         ALL_RELEASED    0

#define         R0              RB5
#define         R1              RB6
#define         R2              RB7
#define         C0              RB1
#define         C1              RB2
#define         C2              RB3
#define         C3              RB4

void init_matrix_keypad(void);
unsigned char read_matrix_keypad(unsigned char);

#endif	/* MKP_H */

