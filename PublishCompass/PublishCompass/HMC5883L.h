/*
 * HMC5883L library code
 *
* I2C Routines
* 00 Configuration register A   R/W  00011100 &H1C
* 01 Configuration register B   R/W  00000000 &H00
* 02 Mode register              R/W  00000000 &H00
* 03 Data Output X MSB Register Read
* 04 Data Output X LSB Register Read
* 05 Data Output Z MSB Register Read
* 06 Data Output Z LSB Register Read
* 07 Data Output Y MSB Register Read
* 08 Data Output Y LSB Register Read
* 09 Status Register            Read
* 10 Identification Register A  Read
* 11 Identification Register B  Read
* 12 Identification Register C  Read
*/

#define		HMC5883L_ADDR	0x3C
#define		WRITE_ADDRESS	0x3C
#define		READ_ADDRESS	0x3D
#define		CONF_A_REG		0x00
#define		CONF_B_REG		0x01
#define		CONF_M_REG		0x02
#define		X_LSB_REG		0x03
#define		Y_LSB_REG		0x07
#define		Z_LSB_REG		0x05

void HMC5883L_init()
{
	char x = 0x00;
	// Write 0x70 to HMC5883L register A
	i2c_start(WRITE_ADDRESS);
	//i2c_write(WRITE_ADDRESS);
	//i2c_start_wait(WRITE_ADDRESS);
	//i2c_write(CONF_A_REG);
	i2c_write(x);
	i2c_write(0x70);	// avg 8 samples, 15Hz, Normal measurement
	i2c_write(0x20);
	i2c_write(0x00);
	i2c_stop();
	_delay_us(1000); 
// 	
// 	i2c_start(WRITE_ADDRESS);
// 	i2c_write(0x70);	// avg 8 samples, 15Hz, Normal measurement
// 	i2c_stop();			// release bus
// 	
// 	// Write 0xE0 to HMC5883L register B
// 	i2c_start_wait(WRITE_ADDRESS);
// 	i2c_write(CONF_B_REG);
// 	i2c_write(0x20);	/* 
// 						 */
// 	i2c_stop();			// release bus
// 	
// 	// Write 0x00 to HMC5883L Mode register
// 	i2c_start_wait(WRITE_ADDRESS);
// 	i2c_write(CONF_M_REG);
// 	i2c_write(0x00);	// slow I2C, continuous measurement mode
// 	i2c_stop();			// release bus
}

void readCompass(uint16_t *value) 
{
	uint16_t temp;
	//i2c_start_wait(WRITE_ADDRESS);
	i2c_start(WRITE_ADDRESS);
	i2c_write(0x03);
	i2c_start_wait(READ_ADDRESS);
	// Read x axis
	temp = i2c_readAck();
	temp = (temp << 8) | i2c_readAck();
	value[0] = temp;
	
	// Read z
	temp = i2c_readAck();
	temp = (temp << 8) | i2c_readAck();
	value[2] = temp;
	
	// Read y axis
	temp = i2c_readAck();
	temp = (temp << 8) | i2c_readNak();
	value[1] = temp;

	i2c_stop();
}