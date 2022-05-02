namespace HitMe.Device
{
    using System.Net;
    using System.Net.Sockets;
    using System.Text;

    using HitMe.Types;
    using HitMe.Types.Device;

    using LanguageExt;

    using static LanguageExt.Prelude;

    public class DeviceStatusListener
    {
        /// <summary>
        /// Default stop timeout for the task.
        /// </summary>
        private const int _taskKillTimeout_ms = 2000;

        /// <summary>
        /// Default hitme port for control messages.
        /// </summary>
        private const int _defaultCtrlPort = 10001; // HITME_CTRLPORT (in and out)

        /// <summary>
        ///  Field for the task.
        /// </summary>
        private Task _ctrlTask = Task.CompletedTask;

        /// <summary>
        /// Variable to stop the thread.
        /// </summary>
        private bool run = true;

        /// <summary>
        /// Is task running?
        /// </summary>
        public bool Running => _ctrlTask.Status == TaskStatus.Running;

        /// <summary>
        /// Device ip adress and port.
        /// </summary>
        public IPEndPoint Ipe { get; init; } = new IPEndPoint(IPAddress.None, _defaultCtrlPort);

        /// <summary>
        /// Start the control task.
        /// </summary>
        public void Start()
        {
            run = true;
            _last.Change += _last_Change;



            if (_ctrlTask.Status != TaskStatus.Running)
            {
                _ctrlTask = Task.Run(() =>
                {
                    using var udpClient = new UdpClient(Ipe.Port);
                    while (run)
                    {
                        IPEndPoint ep = Ipe;
                         byte[]? data = udpClient.Receive(ref ep);

                        if (Ipe.Equals(ep))
                        {
                            if (data != null)
                            {
                                var jdata = JsonDeviceStatusMessage.FromJson(Encoding.Latin1.GetString(data));

                                _ = _last.Swap(x => new DeviceConfig(new DeviceNetConfig()
                                { DeviceCtrlPort = Ipe.Port, DeviceIP = Ipe.Address }, new DeviceMeasurementConfig(jdata.Range, jdata.Bandwidth, jdata.Start)));
                            }
                        }
                    }
                });
            }
        }

        private void _last_Change(Option<DeviceConfig> value)
        {

            var c = value.Match(
                Some: config => config,
                None: () => DeviceConfig.Default);

            var args = new DeviceStatusEventArgs()
            {
                valid = value.IsSome,
                DeviceMeasurementConfig = c.Measurement,
                DeviceNetConfig = (DeviceNetConfig)c.Net.Clone(),
            };
            OnStatusChangedEvent(args);
        }

        /// <summary>
        /// Stops controll task.
        /// </summary>
        public void Stop()
        {
            if (_ctrlTask.Status == TaskStatus.Running)
            {
                run = false;
                _last.Change -= _last_Change;

                _ = _last.Swap(x => Option<DeviceConfig>.None);
                
                if (!_ctrlTask.Wait(_taskKillTimeout_ms))
                {
                    _ctrlTask.Dispose();
                    _ctrlTask = Task.CompletedTask;

                }
            }
        }


        public void Configure(DeviceConfig newConfig)
        {
            Stop();

            {
                using var udpClient = new UdpClient(Ipe.Port);

                JsonDeviceStatusMessage msg = new ()
                {
                    Type = Types.Device.MessageType.REQUEST_MSG,
                    Bandwidth = newConfig.Measurement.Bandwidth,
                    Range = newConfig.Measurement.Range,
                    Start = newConfig.Measurement.Start,
                };
                
                byte[] data = Encoding.Latin1.GetBytes(JsonDeviceStatusMessage.ToJson(msg));
                _ = udpClient.Send(data, data.Length, Ipe);
            }

            Start();
        }
        

        /// <summary>
        /// Last config state.
        /// </summary>
        readonly Atom<Option<DeviceConfig>> _last = Atom(Option<DeviceConfig>.None);

        /// <summary>
        /// Get last config.
        /// </summary>
        /// <returns>Last config.</returns>
        public Option<DeviceConfig> GetLastConfig() => _last.Value;

        
        /// <summary>
        /// Emitted on changes.
        /// </summary>
        public event EventHandler<DeviceStatusEventArgs> StatusChangedEvent;

        protected virtual void OnStatusChangedEvent(DeviceStatusEventArgs e) => StatusChangedEvent?.Invoke(this, e);

        /// <summary>
        /// Device configuration.
        /// </summary>
        /// <param name="Net">Network config.</param>
        /// <param name="Measurement">Measurement config.</param>
        public record DeviceConfig(DeviceNetConfig Net, DeviceMeasurementConfig Measurement)
        {
            public static DeviceConfig Default => new (DeviceNetConfig.Default, DeviceMeasurementConfig.Default);
        }
        
    }
}
