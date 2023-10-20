
#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

typedef void (*IntCallBack_t) (void);

typedef enum {
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2,
	EXTI_INT3,
	EXTI_INT4,
	EXTI_INT5,
	EXTI_INT6,
	EXTI_INT7,
	EXTI_INT8,
	EXTI_INT9,
	EXTI_INT10,
	EXTI_INT11,
	EXTI_INT12,
	EXTI_INT13,
	EXTI_INT14,
	EXTI_INT15,
	EXTI_INT16,
	EXTI_INT17,
	EXTI_INT18,
	EXTI_INT19,
}EXTI_Int_Type;

typedef enum {
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC,
	EXTI_PORTD,
	EXTI_PORTE,
	EXTI_PORTF,
	EXTI_PORTG,


}EXTI_EXTIPortCFG_t;

typedef enum {
	EXTI_Rising_edge,
	EXTI_Falling_edge,
	EXTI_Rising_Falling_edge,


}EXTI_TriggerEdge_t;
typedef enum {
	EXTI_Enabled,
	EXTI_Disabled,

}EXTI_InterruptState_t;
typedef struct {
	EXTI_InterruptState_t InterruptState;
	EXTI_Int_Type IntNumber;
	EXTI_TriggerEdge_t IntTriggerEdge;
	EXTI_EXTIPortCFG_t IntPortLine;
	IntCallBack_t IntCallBack;
}EXTI_EXTIConfig_t;

#endif
