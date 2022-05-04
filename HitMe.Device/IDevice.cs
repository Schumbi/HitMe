namespace HitMe.Device
{

    using HitMe.Types;
    using HitMe.Types.Device;

    using LanguageExt;

    using static HitMe.Device.DeviceStatusListener;

    public interface IDevice
    {

        /// <summary>
        /// Configures the sensor.
        /// </summary>
        /// <param name="config">Config to use.</param>
        /// <returns>Set configuration of the device.</returns>
        public Task<bool> Configure(DeviceConfig config);

        /// <summary>
        /// Current configuration of the device.
        /// </summary>
        public Task<Option<DeviceConfig>> GetDeviceConfig();

        /// <summary>
        /// Start measurement.
        /// </summary>
        /// <returns></returns>
        public bool Start();

        /// <summary>
        /// Stop measurement.
        /// </summary>
        /// <returns></returns>
        public void Stop();

        /// <summary>
        /// Show state of connection.
        /// </summary>
        public Task<bool> IsConnected();

        /// <summary>
        /// State of measurement.
        /// </summary>
        public Task<bool> IsRunning();

    }
}
