namespace HitMe.Types
{
    using System.Net;

    public class DeviceNetConfig
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

    }
}