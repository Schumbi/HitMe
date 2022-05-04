namespace HitMe.Types.Device
{
    using System.Net;

    /// <summary>
    /// Device configuration.
    /// </summary>
    /// <param name="Net">Network config.</param>
    /// <param name="Measurement">Measurement config.</param>
    public class DeviceConfig : IEquatable<DeviceConfig>
    {
        public DeviceNetConfig Net { get; init; } = DeviceNetConfig.Default;

        public DeviceMeasurementConfig Measurement { get; init; } = DeviceMeasurementConfig.Default;


        public DeviceConfig(DeviceNetConfig net, DeviceMeasurementConfig measurement)
        {
            Net = (DeviceNetConfig)net.Clone();
            Measurement = measurement;
        }

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

        public class DeviceNetConfig : ICloneable, IEquatable<DeviceNetConfig>
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

            public bool Equals(DeviceNetConfig? other)
            {
                if (other is null) return false;
                
                return other.DeviceIP != DeviceIP || other.DeviceCtrlPort != DeviceCtrlPort || other.DeviceDataPort != DeviceDataPort;
            }

        }

        public bool Equals(DeviceConfig? other)
        {
            if(other is null) return false;

            if(Measurement != other.Measurement) return false;

            if(!Net.Equals(other.Net)) return false;

            return true;
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as DeviceConfig);
        }

        public override int GetHashCode()
        {
            throw new NotImplementedException();
        }
    }
}
