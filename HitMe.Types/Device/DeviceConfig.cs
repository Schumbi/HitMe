namespace HitMe.Types.Device
{
    /// <summary>
    /// Device configuration.
    /// </summary>
    /// <param name="Net">Network config.</param>
    /// <param name="Measurement">Measurement config.</param>
    public record DeviceConfig(DeviceNetConfig Net, DeviceMeasurementConfig Measurement)
    {
        public static DeviceConfig Default => new(DeviceNetConfig.Default, DeviceMeasurementConfig.Default);

        /// <summary>
        /// Timestamp coming from controller.
        /// </summary>
        public int RemoteTimeStamp_ms { get; init; }
    }
}
