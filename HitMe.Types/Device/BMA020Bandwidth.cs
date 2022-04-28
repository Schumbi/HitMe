namespace HitMe.Types.Device
{
    public enum BMA020BANDWIDTH
    {
        /// <summary>
        /// Sampling freq: ~25Hz
        /// </summary>
        BMA020_BW_25HZ = 0x00,  // 000b (mean 23 Hz)

        /// <summary>
        /// Sampling freq: 
        /// </summary>
        BMA020_BW_50HZ = 0x01,  // 001b (mean 47 Hz)

        /// <summary>
        /// Sampling freq: ~100Hz
        /// </summary>
        BMA020_BW_100HZ = 0x02, // 010b (mean 94 Hz)

        /// <summary>
        /// Sampling freq:  ~190Hz
        /// </summary>
        BMA020_BW_190HZ = 0x03, // 011b (mean 188 Hz)

        /// <summary>
        /// Sampling freq:  375Hz
        /// </summary>
        BMA020_BW_375HZ = 0x04, // 100b (mean 375 Hz)

        /// <summary>
        /// Sampling freq:  750Hz
        /// </summary>
        BMA020_BW_750HZ = 0x05, // 101b (mean 750 Hz)

        /// <summary>
        /// Sampling freq: 1500Hz 
        /// </summary>
        BMA020_BW_1500HZ = 0x06 // 110b (mean 1500 Hz)
    };

}
