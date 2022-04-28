namespace HitMe.Device
{
    using System.Net;
    using System.Net.Sockets;
    using System.Text;

    using HitMe.Types;

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
        /// Port to user for control communication.
        /// </summary>
        public int CtrlPort { get; init; } = _defaultCtrlPort;

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
                                var jdata = JsonDeviceStatusMessage.FromJson(Encoding.UTF8.GetString(data));

                                Console.WriteLine($"{ep.Address}:{ep.Port} {jdata}");
                            }
                        }
                    }
                });
            }
        }

        /// <summary>
        /// Stops controll task.
        /// </summary>
        public void Stop()
        {
            if (_ctrlTask.Status == TaskStatus.Running)
            {
                run = false;
                if (!_ctrlTask.Wait(_taskKillTimeout_ms))
                {
                    _ctrlTask.Dispose();
                    _ctrlTask = Task.CompletedTask;
                }
            }
        }
    }
}
