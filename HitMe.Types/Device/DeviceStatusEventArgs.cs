namespace HitMe.Types.Device
{
    using System;

    public class DeviceStatusEventArgs : EventArgs
    {
        public bool valid = false;
        
        public DeviceMeasurementConfig DeviceMeasurementConfig { get; set; } = DeviceMeasurementConfig.Default;

        public DeviceNetConfig DeviceNetConfig { get; set; } = DeviceNetConfig.Default;
    }
}
