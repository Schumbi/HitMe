namespace HitMe.Device
{
    using System.Threading.Tasks;

    using HitMe.Types;
    using HitMe.Types.Device;

    using LanguageExt;

    public class Device : IDevice
    {
        private DeviceStatusListener _statusListener = new();

        public Task<Option<DeviceConfig>> Configure(DeviceConfig config)
        {
            throw new NotImplementedException();
        }

        public Task<Option<DeviceConfig>> GetDeviceConfig()
        {
            throw new NotImplementedException();
        }

        public Task<bool> IsConnected()
        {
            throw new NotImplementedException();
        }

        public Task<bool> IsReady()
        {
            throw new NotImplementedException();
        }

        public Task<bool> IsRunning()
        {
            throw new NotImplementedException();
        }

        public Task<bool> Start()
        {
            throw new NotImplementedException();
        }

        public Task<bool> Stop()
        {
            throw new NotImplementedException();
        }
    }
}