
#include "spiedl.h"


void	spiEdlInit(void)
{
tSpiEdl* pspiedl;	
const tIoDef* piodef;
const tSpiDef* pspidef;	
tSpiEdlCfg* pcfg;
tU32 i;	
	
		pspiedl = PoSystemGetContext()->pSpiEdl;
		
		pcfg = &pspiedl->Cfg;
		
		pspidef = &Mcu.pProd->SpiEdlDef;
		for( i = 0 ; i < pcfg->IoCnt; i++)
		{
			piodef = pcfg->IoList[i];
			McuPinConfig(piodef->Port, piodef->Pin, GPIO_Mode_AF, piodef->AF, GPIO_PuPd_NOPULL);
		}
		//GK-> Derleme probleminden dolayi out taski calistirilmadiginda. Spi calismasi icin gerekli pinlerin manual config edilmesi gerekiyor.
		//piodef = McuGetPinDef(DIGOUT_DRV_EN);		McuPinConfig(piodef->Port, piodef->Pin, GPIO_Mode_OUT, 0, GPIO_PuPd_DOWN);
		//piodef = McuGetPinDef(DIGOUT_SPI_NSS);	McuPinConfig(piodef->Port, piodef->Pin, GPIO_Mode_OUT, 0, GPIO_PuPd_DOWN);
		//piodef = McuGetPinDef(DIGOUT_TP1);			McuPinConfig(piodef->Port, piodef->Pin, GPIO_Mode_OUT, 0, GPIO_PuPd_DOWN);
	
		
		McuSpiEdlInit(pcfg->BrKhz, pspidef->Mode);				
				
}																

void	spiPeriodicEdl(tSpiEdlCfg* pCfg, tSpiEdlDyn* pDyn)
{
tRegAddrs	streg;
tU16*		pdst;	
		
		EdlParse(pCfg, pDyn);
		pdst = &pDyn->StatusValList[pDyn->StatusRegIdx];
		*pdst = 256* pDyn->RcvBuf[1] + pDyn->RcvBuf[2];
		
		pDyn->StatusRegIdx++;
		if(pDyn->StatusRegIdx >= pCfg->StatusRegCnt)
			pDyn->StatusRegIdx = 0;
	
		streg = (tRegAddrs)pCfg->StatusRegList[pDyn->StatusRegIdx];	
		EdlReadRegister(streg, &pDyn->XmtBuf[0], pDyn->RcvBuf);
		
		
}


void	spiEdlTickMs(tSpiEdl* pSpiEdl)
{
tSpiEdlCfg* pcfg;
tSpiEdlDyn* pdyn;
tOut *pout;

		pout = PoSystemGetContext()->pOut;		
	
		//GK-> Derleme probleminden dolayi out taski calistirilmadiginda pinlerin manuel surulmesi gerekiyor.
		//McuSetPinLevel(McuGetPinDef(DIGOUT_SPI_NSS), 1);
		//McuSetPinLevel(McuGetPinDef(DIGOUT_SPI_NSS), 0);
		pout->SetDigout(DIGOUT_SPI_NSS, 1);
		pout->SetDigout(DIGOUT_SPI_NSS, 0);	
		pcfg = &pSpiEdl->Cfg;
		pdyn = &pSpiEdl->Dyn;		

		pdyn->WaitCnt++;
		spiPeriodicEdl(pcfg, pdyn);	
		
		McuSpiEdlTransferStart();	
}



void	spiEdlConfig(void)
{
tSpiEdl* pspiedl;	
	
			pspiedl = PoSystemGetContext()->pSpiEdl;
			pspiedl->Cfg.BrKhz = 500; 	
			pspiedl->Cfg.SendPeriodMs = 10,			
			pspiedl->Cfg.IoCnt = 3;
			pspiedl->Cfg.IoList[0] = McuGetPinDef(COM_SPI_SCK); 
			pspiedl->Cfg.IoList[1] = McuGetPinDef(COM_SPI_MISO);
			pspiedl->Cfg.IoList[2] = McuGetPinDef(COM_SPI_MOSI);
			EdlPrepStatusRegs(&pspiedl->Cfg);
			EdlPrepCfgRegs(&pspiedl->Cfg);
}

void	spiEdlSendDefaultVals(tSpiEdl* pSpiEdl)
{
tU32	i;	
tSpiEdlCfg* pcfg;
tSpiEdlDyn* pdyn;
tRegAddrs	cfgreg;
tU16		val;
		
		val = 0;
		pcfg = &pSpiEdl->Cfg;
		pdyn = &pSpiEdl->Dyn;
		for(i = 0; i < pcfg->CfgRegCnt; i++)
		{
			cfgreg = (tRegAddrs)pcfg->CfgRegList[i];
			val = pcfg->CfgValList[i];
			McuSpiEdlTransferStop();
			EdlWriteRegister(cfgreg, pdyn->XmtBuf, val);
			McuSpiEdlTransferStart();
			CoreDelay(1);
		}	
}

/* Prototype for any OS. it will be your task
void	TaskSpiEdl(void)
{
tSpiEdl* pspiedl;

		pspiedl = PoSystemGetContext()->pSpiEdl;
		pspiedl->Dyn.Flags = 0;
		spiEdlConfig();
		spiEdlInit();
		spiEdlSendDefaultVals(pspiedl);
		
	
		McuSetPinLevel(McuGetPinDef(DIGOUT_DRV_EN), 1);
		McuSetPinLevel(McuGetPinDef(DIGOUT_TP1), 1);
		PoSystemGetContext()->pOut->SetDigout(DIGOUT_DRV_EN, 1);
		PoSystemGetContext()->pOut->SetDigout(DIGOUT_BREAK, 1);
	
		pspiedl->Dyn.Flags |= PO_FLAG_READY;
	
		while(1)
		{
      // your task system
		}	
}


