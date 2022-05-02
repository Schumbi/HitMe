namespace HitMe.Types.Device
{
    using System.Net;

    /// <summary>
    /// Device configuration.
    /// </summary>
    /// <param name="Net">Network config.</param>
    /// <param name="Measurement">Measurement config.</param>
    public record DeviceConfig(DeviceConfig.DeviceNetConfig Net, DeviceConfig.DeviceMeasurementConfig Measurement)
    {
        public static DeviceConfig Default => new(DeviceNetConfig.Default, DeviceMeasurementConfig.Default);

        /// <summary>
        /// Timestamp coming from controller.
        /// </summary>
        public int RemoteTimeStamp_ms { get; init; }

        /// <summary>
        /// Configuration of device measurement.
        /// </summary>
        /// <param name="Range">Range to use.</param>
        /// <param name="Bandwidth">Bandwidth to use.</param>
        public record DeviceMeasurementConfig(BMA020Range Range, BMA020Bandwidth Bandwidth, bool Start)
        {
            public static DeviceMeasurementConfig Default => new(BMA020Range.BMA020_RANGE_8G, BMA020Bandwidth.BMA020_BW_25HZ, false);
        }

        public class DeviceNetConfig : ICloneable
        {

            /// <summary>
            ///  Ip of the Hitme sensor device.
            /// </summary>
            public IPAddress DeviceIP { get; init; } = IPAddress.None;

            /// <summary>
            /// Port to control the device.
            /// </summary>
            public int DeviceCtrlPort { get; init; } = 10001;

            /// <summary>
            /// Port device transmits to.
            /// </summary>
            public int DeviceDataPort { get; init; } = 10000;

            /// <summary>
            /// Default type.
            /// </summary>
            public static DeviceNetConfig Default => new();

            public object Clone()
            {
                return new DeviceNetConfig()
                {
                    DeviceIP = DeviceIP,
                    DeviceCtrlPort = DeviceCtrlPort,
                    DeviceDataPort = DeviceDataPort
                };
            }
        }
    }
}
