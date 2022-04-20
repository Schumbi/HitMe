namespace HitMe.Device
{
    using System.Threading.Tasks;

    using HitMe.Types;

    public class Device : IDevice
    {




        public Task<DeviceNetConfig> ConfigureNet(DeviceNetConfig config)
        {
            throw new NotImplementedException();
        }

        public Task<DeviceNetConfig> GetDeviceConfig()
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