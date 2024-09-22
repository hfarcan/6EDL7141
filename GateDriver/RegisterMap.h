/*
@autor: Habib Furkan Arcan
It has been created based on the register map taken from 
the datasheet of Infineon’s 3-phase motor control gate driver, MOTIX™ 6EDL7141.

*/

#ifndef	SPIEDL7141_H
#define	SPIEDL7141_H

typedef enum
{
/*  Status register address, read-only   */
	REG_FAULT_ST = 0x00,
	REG_TEMP_ST,
	REG_SUPPLY_ST,
	REG_FUNCT_ST,
	REG_OTP_ST,
	REG_ADC_ST,
	REG_CP_ST,
	REG_DEVICE_ID,
	
/*Configurable register address        */
	REG_FAULTS_CLR =  0x10,
	REG_SUPPLY_CFG, 
	REG_ADC_CFG,
	REG_PWM_CFG,
	REG_SENSOR_CFG,
	REG_WD_CFG,
	REG_WD_CFG2,
	REG_IDRIVE_CFG,
	REG_IDRIVE_PRE_CFG,
	REG_TDRIVE_SRC_CFG,
	REG_TDRIVE_SINK_CFG,
	REG_DT_CFG,
	REG_CP_CFG,
	REG_CSAMP_CFG,
	REG_CSAMP_CFG2,

/*  OTP program command and user ID      */
	REG_OTP_PROG,
	MAX_NUM_REGS,
	
	NB_CFG_REGS   =     REG_CSAMP_CFG2 - REG_FAULTS_CLR + 1,
	NB_ST_REGS    =     REG_CP_ST - REG_FAULT_ST + 1
}tRegAddrs;


typedef struct      
{
  union
  {
		tU16 Reg; 
    struct
    {
      tU16 CS_OCP_FLT     : 3;     // 2:0 Current sense amplifier OCP fault status
      tU16 CP_FLT         : 1;     // 3:3 Charge pumps fault status
      tU16 DVDD_OCP_FLT   : 1;     // 4:4 DVDD OCP (Over-Current Protection) fault status
      tU16 DVDD_UV_FLT    : 1;     // 5:5 DVDD UVLO (Under-Voltage Lock-Out) fault status
      tU16 DVDD_OV_FLT    : 1;     // 6:6 DVDD OVLO (Over-Voltage Lock-Out)fault status
      tU16 BK_OCP_FLT     : 1;     // 7:7 Buck OCP fault status
      tU16 OTS_FLT        : 1;     // 8:8 Over-temperature shutdown fault status
      tU16 OTW_FLT        : 1;     // 9:9 Over-temperature warning status
      tU16 RLOCK_FLT      : 1;     // 10:10 Locked rotor fault status
      tU16 WD_FLT         : 1;     // 11:11 Watchdog fault status
      tU16 OTP_FLT        : 1;     // 12:12 OTP status
      tU16 RESERVED0      : 1;     // 15:13 Reserved
    };
  };
}tFaultStatReg;


typedef struct      
{
  union
  {
    tU16 Reg;                     
		struct
    {
      tU16 TEMP_VAL       : 7;     // 6:0 Temperature reading
      tU16 RESERVED0      : 9;     // 15:7 Reserved
    };
  };
}tTempStatReg;


typedef struct                     
{
  union
  {
		tU16 Reg;
    struct
    {
      tU16 VCCLS_UVST     : 1;     // 0:0 Charge Pump low side UVLO status
      tU16 VCCHS_UVST     : 1;     // 1:1 Charge Pump high side UVLO status
      tU16 DVDD_UVST      : 1;     // 2:2 DVDD UVLO status
      tU16 DVDD_OVST      : 1;     // 3:3 DVDD OVLO (Over-Voltage Lock-Out) status
      tU16 VDDB_UVST      : 1;     // 4:4 VDDB UVLO status
      tU16 VDDB_OVST      : 1;     // 5:5 VDDB OVLO status
      tU16 PVDD_VAL       : 7;     // 12:6 PVDD ADC result reading value
      tU16 RESERVED0      : 3;     // 15:13 Reserved
    };
  };
}tSupplyStatReg;


typedef struct                     
{
  union
  {
		tU16 Reg;                   
    struct
    {
      tU16 HALLIN_ST      : 3;     // 2:0 Hall sensor inputs status
      tU16 HALLPOL_ST     : 1;     // 3:3 Hall sensor polarity equal indicator
      tU16 DVDD_ST        : 1;     // 4:4 DVDD set point status
      tU16 CS_GAIN_ST     : 3;     // 7:5 Status of the current sense amplifiers gain
      tU16 RESERVED0      : 8;     // 15:8 Reserved
    };
  };
}tFuncStatReg;

typedef struct      
{
  union
  {
		tU16 Reg;
    struct
    {
      tU16 OTP_USED       : 1;     // bits 0:0 OTP used
      tU16 OTP_PASS       : 1;     // bits 1:1 User OTP programming status
      tU16 OTP_PROG_BLOCK : 1;     // bits 1:1 User OTP programming blocked
      tU16 OTP_PROG_FAIL  : 1;     // bits 1:1 OTP Programming fail
      tU16 RESERVED0      : 12;    // bits 15:4 Reserved
    };
  };
}tOTPStatReg;


typedef struct      
{
  union
  {
		tU16 Reg;       
    struct
    {
      tU16 ADC_OD_RDY     : 1;     // bits 0:0 ADC on demand conversion result ready
      tU16 ADC_OD_VAL     : 7;     // bits 7:1 ADC on demand result value
      tU16 RESERVED0      : 8;     // bits 15:8 Reserved
    };
  };
}tAdcStatReg;


typedef struct      
{
  union
  {
		tU16 Reg;                      
    struct
    {
      tU16 VCCHS_VAL      : 7;     // bits 6:0 VCCHS ADC result reading value
      tU16 VCCLS_VAL      : 7;     // bits 13:7 VCCLS ADC result reading value
      tU16 RESERVED0      : 2;     // bits 15:14 Reserved
    };
    
  };
}tChargePumpStatReg;


typedef struct      
{
  union
  { 
		tU16 Reg;       
    struct
    {
      tU16 DEV_ID         : 4;     // bits 3:0 Device ID
      tU16 ADCTV_Y        : 12;    // bits 15:4 Reserved
    };
    
  };
}tDeviceIdReg;


typedef struct      
{
  union
  {
		tU16 Reg;       
    struct
    {
      tU16 CLR_FLTS       : 1;     // bits 0:0 Clear all faults
      tU16 CLR_LATCH      : 1;     // bits 1:1 Clear all latched faults
      tU16 RESERVED0      : 14;    // bits 15:2 Reserved
    };
   };
}tFaultClrReg;

typedef struct      
{
  union
  {
		 tU16 Reg;                      
    struct
    {
      tU16 PVCC_SETPT       : 2;   // bits 1;0 PVCC set point
      tU16 CS_REF_CFG       : 2;   // bits 3:2 Current sense reference configuration (internal VREF voltage)
      tU16 DVDD_OCP_CFG     : 2;   // bits 5:4 DVDD OCP threshold configuration
      tU16 DVDD_SFTSTRT     : 4;   // bits 9:6 DVDD soft-start configuration
      tU16 DVDD_SETPT       : 2;   // bits 11:10 DVDD set point configuration
      tU16 BK_FREQ          : 1;   // bits 12:12 Buck converter switching frequency selection
      tU16 DVDD_TON_DELAY   : 2;   // bits 14:13 DVDD turn on delay configuration
      tU16 CP_PRECHARGE_EN  : 1;   // bits 15:15 Charge pump pre-charge configuration
    };
   
  };
}tSupplyCfgReg;


typedef struct      
{
  union
  {
		tU16 Reg;
    struct
    {
      tU16 ADC_OD_REQ         : 1; // bits 0:0 ADC on demand conversion request
      tU16 ADC_OD_INSEL       : 2; // bits 2:1 ADC input selection for on demand conversions
      tU16 ADC_EN_FILT        : 1; // bits 3:3 Enable filtering for on demand ADC measurement
      tU16 ADC_FILT_CFG       : 2; // bits 5:4 ADC generic filtering configuration
      tU16 ADC_FILT_CFG_PVDD  : 2; // bits 7:6 PVDD ADC measurement result filtering configuration
      tU16 RESERVED0          : 8; // bits 15:8 Reserved
    };
            
  };
}tAdcCfgReg;

typedef struct      
{
  union
  {
		tU16 Reg;
    struct
    {
      tU16 PWM_MODE       : 3;     // bits 2:0 PWM commutation mode selection
      tU16 PWM_FREEW_CFG  : 1;     // bits 3:3 PWM freewheeling configuration
      tU16 BRAKE_CFG      : 2;     // bits 5:4 Brake configuration
      tU16 PWM_RECIRC     : 1;     // bits 6:6 PWM recirculation selection (only if PWM_MODE = b011:)
      tU16 RESERVED0      : 9;     // bits 15:7 Reserved
    };
  };
}tPwmCfgReg;

typedef struct      
{
  union
  {
		tU16 Reg;
    struct
    {
      tU16 HALL_DEGLITCH  : 4;     // bits 3:0 Hall Sensor deglitch
      tU16 OTS_DIS        : 1;     // bits 4:4 Over-temperature shutdown disable
      tU16 CS_TMODE       : 2;     // bits 6:5 Current sense amplifier timing mode
      tU16 RESERVED0      : 9;     // bits 15:7 Reserved
    };
  };
}tSensorCfgReg;


typedef struct      
{
  union
  {
	 tU16 Reg;
    struct
    {
      tU16 WD_EN        : 1;       // bits 0:0 Watchdog enable
      tU16 WD_INSEL     : 3;       // bits 3:1 Watchdog input selection
      tU16 WD_FLTCFG    : 1;       // bits 4:4 Watchdog fault configuration
      tU16 WD_TIMER_T   : 10;      // bits 14:5 Watchdog timer period value
      tU16 RESERVED0    : 1;       // bits 15:15 Reserved
    };
  };
}tWdCfgReg;


typedef struct      
{
  union
  {
	  tU16 Reg;
    struct
    {
      tU16 WD_BRAKE           : 1; // bits 0:0 Brake on watchdog timer overflow
      tU16 WD_EN_LATCH        : 1; // bits 1:1 Enable latching of watchdog fault
      tU16 WD_DVDD_RSTRT_ATT  : 2; // bits 3:2 Restart delay for DVDD
      tU16 WD_DVDD_RSTRT_DLY  : 4; // bits 7:4 DVDD restart delay
      tU16 WD_RLOCK_EN        : 1; // bits 8:8 Enable rotor locked detection
      tU16 WD_RLOCK_T         : 3; // bits 11:9 Rotor locked watchdog timeout
      tU16 WD_BK_DIS          : 1; // bits 12:12 Buck watchdog disable
      tU16 RESERVED0          : 3; // bits 15:13 Reserved
    };
  };
}tWdCfgReg2;

typedef struct      
{
  union
  {
		tU16 Reg;                      
    struct
    {
      tU16 IHS_SRC    : 4;         // bits 3:0 High-side source current (default b1011 - 200mA)
      tU16 IHS_SINK   : 4;         // bits 7:4 High-side sink current (default b1011 - 200mA)
      tU16 ILS_SRC    : 4;         // bits 11:8 Low-side source current (default b1011 - 200mA)
      tU16 ILS_SINK   : 4;         // bits 15:12 Low-side sink current (default b1011 - 200mA)
    };
  };
}tIDriveCurCtrlReg;

typedef struct      
{
  union
  {
		tU16 Reg;  
    struct
    {
      tU16 I_PRE_SRC  : 4;         // bits 3:0 Pre-charge source current setting (TDRIVE1) (default b1011 - 200mA)
      tU16 I_PRE_SINK : 4;         // bits 7:4 Pre-charge sink current setting (TDRIVE3) (default b1011 - 200mA)
      tU16 I_PRE_EN   : 1;         // bits 8:8 Gate driver pre-charge mode enable
      tU16 RESERVED0  : 7;         // bits 15:9 Reserved
    };
  };
}tIDrivePreCurCtrlReg;

typedef struct      
{
  union
  {
	 tU16 Reg;                      
    struct
    {
      tU16 TDRIVE1  : 8;           // bits 7:0 TDRIVE1 timing
      tU16 TDRIVE2  : 8;           // bits 15:8 TDRIVE2 timing
    };
     };
}tTdriveSrcReg;


typedef struct                       
{
  union
  {
		tU16 Reg;                      
    struct
    {
      tU16 TDRIVE3  : 8;           // bits 7:0 TDRIVE3 timing
      tU16 TDRIVE4  : 8;           // bits 15:8 TDRIVE4 timing
    };
    
  };
}tTdriveSinkReg;

typedef struct                       
{
  union
  {
    tU16 Reg;                      
		struct
    {
      tU16 DT_RISE  : 8;           // bits 7:0 Dead time rise (of phase node voltage)
      tU16 DT_FALL  : 8;           // bits 15:8 Dead time fall (of phase node voltage)
    };
    
  };
}tDeadTimeReg;

typedef struct                       
{
  union
  {
	  tU16 Reg;                      
    struct
    {
      tU16 CP_CLK_CFG     : 2;     // bits 1:0 Charge pump clock frequency configuration
      tU16 CP_CLK_SS_DIS  : 1;     // bits 2:2 Charge pump clock spread spectrum disable
      tU16 RESERVED0      : 13;    // bits 15:3 Reserved
    };
  };
}tChargePumpCfgReg;

typedef struct                       
{
  union
  {
  	tU16 Reg;                      
    struct
    {
      tU16 CS_GAIN          : 3;   // bits 2:0 Gain of current sense amplifiers
      tU16 CS_GAIN_ANA      : 1;   // bits 3:3 CS Gain analogue programming enable
      tU16 CS_EN            : 3;   // bits 6:4 Enable of each current shunt amplifier
      tU16 CS_BLANK         : 4;   // bits 10:7 Current shunt amplifier blanking time
      tU16 CS_EN_DCCAL      : 1;   // bits 11:11 Enable DC Calibration of CS amplifier
      tU16 CS_OCP_DEGLITCH  : 2;   // bits 13:12 Current sense amplifier OCP deglitch
      tU16 CS_OCPFLT_CFG    : 2;   // bits 15:14 Current sense amplifier OCP fault trigger configuration
    };  
  };
} tCsAmpCfgReg;

typedef struct                       
{
  union
  {
		tU16 Reg;  
    struct
    {
      tU16 CS_OCP_PTHR      : 4;   // bits 3:0 Current sense amplifier OCP positive thresholds
      tU16 CS_OCP_NTHR      : 4;   // bits 7:4 Current sense amplifier OCP negative thresholds
      tU16 CS_OCP_LATCH     : 1;   // bits 8:8 OCP latch choice
      tU16 CS_MODE          : 1;   // bits 9:9 Current sense amplifier sensing mode
      tU16 CS_OCP_BRAKE     : 1;   // bits 10:10 Current sense amplifier brake on OCP configuration
      tU16 CS_TRUNC_DIS     : 1;   // bits 11:11 PWM truncation disable
      tU16 VREF_INSEL       : 1;   // bits 12:12 VREF source selection
      tU16 CS_NEG_OCP_DIS   : 1;   // bits 13:13 Current sense negative OCP disable
      tU16 CS_AZ_CFG        : 2;   // bits 15:14 Current sense Auto-Zero configuration
    };                               
    
  };                                 
}tCsAmpCfgReg2;                      
																		 
typedef struct                       
{                                    
  union                              
  {    
		tU16 Reg; 
    struct                           
    {                                
      tU16 OTP_PROG     : 1;       // bits 0:0 Program OTP
      tU16 USER_ID      : 4;       // bits 4:1 User ID
      tU16 RESERVED0    : 11;      // bits 15:5 Reserved
    };                               
                       
  };
}tOtpProgramReg;


typedef struct
{
		tCsAmpCfgReg						CalibrStart;
		tCsAmpCfgReg						CalibrStop;
		tFaultStatReg         	FaultStat;
		tTempStatReg 						TempStat;     
		tSupplyStatReg        	SupplyStat;
		tFuncStatReg          	FuncStat;
		tAdcStatReg           	AdcStat;
		tChargePumpStatReg    	ChargePumpStat;
		tDeviceIdReg						DeviceId;      
		tFaultClrReg          	FaultClr;  
		tSupplyCfgReg         	SupplyCfg; 
		tAdcCfgReg 							AdcCfg;       
		tPwmCfgReg							PwmCfg;        
		tSensorCfgReg         	SensorCfg;     
		tWdCfgReg								WdCfg;        
		tWdCfgReg2            	WdCfg2;
		tIDriveCurCtrlReg     	CurCtrlCfg;      
		tIDrivePreCurCtrlReg		PreCurCtrlCfg;    
		tTdriveSrcReg         	TdriveCtrlCfg;
		tTdriveSinkReg      		TdriveSinkCfg;
		tDeadTimeReg          	DeadTimeCfg;
		tChargePumpCfgReg     	ChargePumpCfg;
		tCsAmpCfgReg				  	SensAmpfCfg;       
		tCsAmpCfgReg2			 			SensAmpfCfg2;      
		tOtpProgramReg        	OtpProgram;
}tEdlRegisters;



















#endif //SPIEDL7141_H

