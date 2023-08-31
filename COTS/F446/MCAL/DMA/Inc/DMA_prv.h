
#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

typedef void (*IntCallBack_t) (void);

enum {
	DMA_SxCR_EN = 0,
	DMA_SxCR_DMEIE = 1,
	DMA_SxCR_TEIE = 2,
	DMA_SxCR_HTIE = 3,
	DMA_SxCR_TCIE = 4,
	DMA_SxCR_PFCTRL = 5,
	DMA_SxCR_DIR = 6,
	DMA_SxCR_CIRC = 8,
	DMA_SxCR_PINC = 9,
	DMA_SxCR_MINC = 10,
	DMA_SxCR_PSIZE = 11,
	DMA_SxCR_MSIZE = 13,
	DMA_SxCR_PINCOS = 15,
	DMA_SxCR_PL = 16,
	DMA_SxCR_DBM = 18,
	DMA_SxCR_CT = 19,
	DMA_SxCR_PBURST = 21,
	DMA_SxCR_MBURST = 23,
	DMA_SxCR_CHSEL = 25
};
enum {
	DMA_SxFCR_FTH = 0,
	DMA_SxFCR_DMDIS=2,
	DMA_SxFCR_FS=4,
	DMA_SxFCR_FEIE=7,
};





#endif
