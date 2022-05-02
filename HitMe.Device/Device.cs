namespace HitMe.Device
{
    using System.Threading.Tasks;

    using HitMe.Types;

    public class Device : IDevice
    {
        private DeviceStatusListener _statusListener;


        public Task<DeviceNetConfig> ConfigureNet(DeviceNetConfig config)
        {
            if(_statusListener.Running)
            {
                _statusListener.Stop();
            }

            _statusListener = new DeviceStatusListener()
            {
                Ipe = System.Net.IPEndPoint.Parse($"{config.DeviceIP}:{config.DeviceCtrlPort}"),
            };

            throw new NotImplementedException();

        }

        public Task<DeviceNetConfig> GetDeviceNetConfig()
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