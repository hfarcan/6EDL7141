//Need Configure for your projects
#ifndef	SPIEDL_H
#define	SPIEDL_H

#include "spi.h"
#include "edl7141.h"


#define NB_EDL_REGS 32 //(NB_CFG_REGS + NB_ST_REGS)

typedef struct
{
	tU32						BrKhz;
	tU32						IoCnt;
	const tIoDef*		IoList[3];
	tU32						SendPeriodMs;
	tU32						SendCnt;
	tU32						StatusRegCnt;
	tU8							StatusRegList[NB_EDL_REGS];
	tU32						CfgRegCnt;
	tU8							CfgRegList[NB_EDL_REGS];
	tU16						CfgValList[NB_EDL_REGS];
}tSpiEdlCfg;


typedef struct
{
	tU32						Flags;
	tU32						WaitCnt;
	tU32						StatusRegIdx;
	tU16						StatusValList[25];
	tU32						CfgRegIdx;
	tU16						CfgValList[NB_EDL_REGS];
	tU8 						XmtBuf[3];
	tU8   						RcvBuf[3];
	float 						PVDD;
	float						Temp;
	float						VCCLS;
	float						VCCHS;
	float						Idig;
	float 						VDDB;
	float 						VDDD;
}tSpiEdlDyn;	


typedef struct
{
	tSpiEdlCfg		Cfg;
	tSpiEdlDyn		Dyn;
}tSpiEdl;

void 	EdlReadRegister(tRegAddrs RegAddr, tU8* pSrc, tU8 *pDst);
void 	EdlWriteRegister(tRegAddrs RegAddr, tU8* pDst, tU16 Val);
void	EdlPrepStatusRegs(tSpiEdlCfg *pCfg);
void	EdlPrepCfgRegs(tSpiEdlCfg *pCfg);
void 	EdlParse(tSpiEdlCfg *pCfg, tSpiEdlDyn *pDyn);
void	EdlPrepStatusRegs(tSpiEdlCfg *pCfg);
void	EdlPrepCfgRegs(tSpiEdlCfg *pCfg);
float GetRegVal(tSpiEdlCfg *pCfg, tSpiEdlDyn *pDyn, tRegAddrs RegAddr);

#endif //SPI_H

