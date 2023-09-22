/*
 * Utils.h
 *
 *  Created on: Apr 14, 2023
 *      Author: ALTAWKEL
 */

#ifndef UTILS_H_
#define UTILS_H_


/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

#define READ_BIT(REG,BIT) ((REG>>BIT) & 1)

#endif /* UTILS_H_ */
