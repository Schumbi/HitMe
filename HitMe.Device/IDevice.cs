namespace HitMe.Device
{

    using HitMe.Types;

    public interface IDevice
    {

        /// <summary>
        /// Configures the sensor.
        /// </summary>
        /// <param name="config">Config to use.</param>
        /// <returns>Set configuration of the device.</returns>
        public Task<DeviceNetConfig> ConfigureNet(DeviceNetConfig config);

        /// <summary>
        /// Current configuration of the device.
        /// </summary>
        public Task<DeviceNetConfig> GetDeviceConfig();

        /// <summary>
        /// Start measurement.
        /// </summary>
        /// <returns></returns>
        public Task<bool> Start();

        /// <summary>
        /// Stop measurement.
        /// </summary>
        /// <returns></returns>
        public Task<bool> Stop();

        /// <summary>
        /// Show state of connection.
        /// </summary>
        public Task<bool> IsConnected();

        /// <summary>
        /// State of measurement.
        /// </summary>
        public Task<bool> IsRunning();

        /// <summary>
        /// Is not running but connected and can be started.
        /// </summary>
        public Task<bool> IsReady();

    }
}
