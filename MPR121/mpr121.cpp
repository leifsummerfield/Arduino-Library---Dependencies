/*
Separated from i2c.cpp 
by Russ Crowther 12/05/2012
*/

#include "mpr121.h"
#include <i2c.h>


unsigned int mpr121Read(uint8_t address)
{
  unsigned int data;
  
  i2cSendStart();
  i2cSendByte(MPR121_W);	// write 0xB4
  i2cSendByte(address);		// write register address
  i2cSendStart();
  i2cSendByte(MPR121_R);	// write 0xB5
  
  data = i2cReceiveByte(0);
 
  i2cSendStop();
  cbi(TWCR, TWEN);	// Disable TWI
  sbi(TWCR, TWEN);	// Enable TWI
  return data;
}

unsigned int mpr121Read_word(uint8_t address)
{
  unsigned int data, dataL;
  
  i2cSendStart();
  i2cSendByte(MPR121_W);	// write 0xB4
  i2cSendByte(address);	// write register address
  i2cSendStart();
  i2cSendByte(MPR121_R);	// write 0xB5
  
  dataL = i2cReceiveByte(1);		//read LSB
  data = i2cReceiveByte(0);			//read msb	
 
  i2cSendStop();
  cbi(TWCR, TWEN);	// Disable TWI
  sbi(TWCR, TWEN);	// Enable TWI
  data = (data << 8);
  data |= dataL;
  
  return data;
}

void mpr121Write(unsigned char address, unsigned char data)
{
  i2cSendStart();
  i2cSendByte(MPR121_W);// write 0xB4
  i2cSendByte(address);	// write register address
  i2cSendByte(data);
  i2cSendStop();
}

void mpr121QuickConfig(void)
{
  // Section A
  // This group controls filtering when data is > baseline.
  mpr121Write(MHD_R, 0x01);
  mpr121Write(NHD_R, 0x01);
  mpr121Write(NCL_R, 0x00);
  mpr121Write(FDL_R, 0x00);

  // Section B
  // This group controls filtering when data is < baseline.
  mpr121Write(MHD_F, 0x01);
  mpr121Write(NHD_F, 0x01);
  mpr121Write(NCL_F, 0xFF);
  mpr121Write(FDL_F, 0x02);
  
  // Section C
  // This group sets touch and release thresholds for each electrode
  mpr121Write(ELE0_T, TOU_THRESH);
  mpr121Write(ELE0_R, REL_THRESH);
  mpr121Write(ELE1_T, TOU_THRESH);
  mpr121Write(ELE1_R, REL_THRESH);
  mpr121Write(ELE2_T, TOU_THRESH);
  mpr121Write(ELE2_R, REL_THRESH);
  mpr121Write(ELE3_T, TOU_THRESH);
  mpr121Write(ELE3_R, REL_THRESH);
  mpr121Write(ELE4_T, TOU_THRESH);
  mpr121Write(ELE4_R, REL_THRESH);
  mpr121Write(ELE5_T, TOU_THRESH);
  mpr121Write(ELE5_R, REL_THRESH);
  mpr121Write(ELE6_T, TOU_THRESH);
  mpr121Write(ELE6_R, REL_THRESH);
  mpr121Write(ELE7_T, TOU_THRESH);
  mpr121Write(ELE7_R, REL_THRESH);
  mpr121Write(ELE8_T, TOU_THRESH);
  mpr121Write(ELE8_R, REL_THRESH);
  mpr121Write(ELE9_T, TOU_THRESH);
  mpr121Write(ELE9_R, REL_THRESH);
  mpr121Write(ELE10_T, TOU_THRESH);
  mpr121Write(ELE10_R, REL_THRESH);
  mpr121Write(ELE11_T, TOU_THRESH);
  mpr121Write(ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  mpr121Write(FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Enable 6 Electrodes and set to run mode
  // Set ELE_CFG to 0x00 to return to standby mode
 // mpr121Write(ELE_CFG, 0x0C);	// Enables all 12 Electrodes
    mpr121Write(ELE_CFG, 0x06);		// Enable first 6 electrodes
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*mpr121Write(ATO_CFG0, 0x0B);
  mpr121Write(ATO_CFGU, 0xC9);	// USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   mpr121Write(ATO_CFGL, 0x82);	// LSL = 0.65*USL = 0x82 @3.3V
  mpr121Write(ATO_CFGT, 0xB5);*/	// Target = 0.9*USL = 0xB5 @3.3V
}
