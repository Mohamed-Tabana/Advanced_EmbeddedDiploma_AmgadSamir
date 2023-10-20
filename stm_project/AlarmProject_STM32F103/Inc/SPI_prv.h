
#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

typedef void (*IntCallBack_t) (void);

 enum
{
    // CR1 register
    SPI_CR1_CPHA = 0,
    SPI_CR1_CPOL,
    SPI_CR1_MSTR,
    SPI_CR1_BR,
    SPI_CR1_SPE=6,
    SPI_CR1_LSBFIRST,
    SPI_CR1_SSI,
    SPI_CR1_SSM,
    SPI_CR1_RXONLY,
    SPI_CR1_DFF,
    SPI_CR1_CRCNEXT,
    SPI_CR1_CRCEN,
    SPI_CR1_BIDIOE,
    SPI_CR1_BIDIMODE,

    // CR2 register
    SPI_CR2_RXDMAEN = 0,
    SPI_CR2_TXDMAEN,
    SPI_CR2_SSOE,
    SPI_CR2_ERRIE=5,
    SPI_CR2_RXNEIE,
    SPI_CR2_TXEIE,

    // SR register
    SPI_SR_RXNE = 0,
    SPI_SR_TXE,
    SPI_SR_CHSIDE,
    SPI_SR_UDR,
    SPI_SR_CRCERR,
    SPI_SR_MODF,
    SPI_SR_OVR,
    SPI_SR_BSY,

    // DR register

    // CRCPR register

    // RXCRCR register

    // TXCRCR register

} ;



#endif
