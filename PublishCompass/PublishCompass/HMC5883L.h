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

#define		HMC5883L_ADDR	0x3C // I2C address for device. 
#define		WRITE_ADDRESS	0x3C
#define		READ_ADDRESS	0x3D
#define		CONF_A_REG		0x00 // Addresses for configuration registers.
#define		CONF_B_REG		0x01 // 
#define		CONF_M_REG		0x02 //
#define		X_MSB_REG		0x03 // Addresses for MSB of axis registers.
#define		Y_MSB_REG		0x07 // 
#define		Z_MSB_REG		0x05 // 

void HMC5883L_init()
/* 
 * This function initiates the HMC5883L by setting configuration registers.
 */
{
	// Write 0x70 to HMC5883L register  A
	//	"	 0x20 to	"		"		B
	//	"	 0x00 to	"		"		Mode
	i2c_start(HMC5883L_ADDR+I2C_WRITE); // start I2C with addcess of HMC5883L 
	i2c_write(CONF_A_REG);  // Write to CONF_A_REG
	i2c_write(0x70);	// avg 8 samples, 15Hz, Normal measurement
	i2c_write(0x20);    // +/-1.3Ga scale. 
	i2c_write(0x00);    // Continuous measurement mode. 
	i2c_stop();			// Release the bus. 
	_delay_ms(1);       // Delay 
}

void readCompass(int16_t *value) 
/* Given an int16_t array value of size 3, readCompass will read values stored 
 * on each axis register of the HMC5883L and store x, y, and z values at index
 * locations 0, 1, and 2 of value array respectively. 
 */ 
{
	int16_t temp;   // temp variable to store current read
	i2c_start(HMC5883L_ADDR+I2C_WRITE); // start I2C write with address to HMC5883L
	i2c_write(X_MSB_REG);   // Begin reading from address X_MSB_REG
	i2c_start_wait(HMC5883L_ADDR+I2C_READ); // Read x axis
	temp = i2c_readAck();   // Read X_MSB
	temp = (temp<<8) | i2c_readAck();//read X_LSB, OR it with MSB shifted to left by 8
	value[0] = temp;    // store in value for index X.
	
	// Read z
	temp = i2c_readAck();   // Read Z_MSB
	temp = (temp<<8) | i2c_readAck();//read X_LSB, OR it with MSB shifted to left by 8
	value[2] = temp;        // store in value for index X.
	
	// Read y axis
	temp = i2c_readAck();   // Read Y_MSB
	temp = (temp << 8) | i2c_readNak();//read X_LSB, OR it with MSB shifted to left by 8
	value[1] = temp;        // store in value for index X.

	i2c_stop();             // Release I2C bus. 
}
