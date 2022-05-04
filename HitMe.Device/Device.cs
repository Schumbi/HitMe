namespace HitMe.Device
{
    using System.Threading.Tasks;
    using System.Timers;

    using HitMe.Device.Extensions;
    using HitMe.Types;
    using HitMe.Types.Device;


    using LanguageExt;

    using static LanguageExt.Prelude;

    public class Device : IDevice
    {
        private DeviceStatusListener _statusListener = new();

        public async Task<bool> Configure(DeviceConfig config)
        {
            _statusListener.Configure(config);
            return await _statusListener.GetLastConfig().Match(
                Some: async last => await last.WaitFor((old) =>
                _statusListener.GetLastConfig()
                    .Match(Some: l => l, () => DeviceConfig.Default),
                config,
                TimeSpan.FromMilliseconds(500),
                5),
                None: () => Task.Run(() => false));
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

        public bool Start()
        {

            _statusListener = new()
            {
                Ipe = System.Net.IPEndPoint.Parse("10.8.1.228:10001"),
            };

            Atom<bool> running = Atom(true);

            static void HandleStatusUpdate(object? sender, DeviceStatusEventArgs args)
            {
                if (args != null)
                {
                    var c = args;
                    Console.WriteLine($"{c.RemoteTimeStamp_ms}: {c.DeviceNetConfig.DeviceIP}:{c.DeviceNetConfig.DeviceCtrlPort} =>  R: {c.DeviceMeasurementConfig.Range} B:{c.DeviceMeasurementConfig.Bandwidth} S: {c.DeviceMeasurementConfig.Start}");
                }
            }
            _statusListener.StatusChangedEvent += HandleStatusUpdate;
            _statusListener.Start();

            return _statusListener.Running;
        }

        public void Stop() => _statusListener.Stop();
    }
}