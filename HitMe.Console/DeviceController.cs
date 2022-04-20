namespace HitMe.Console
{
    using System;
    using System.Net;
    using System.Net.Sockets;
    using System.Text;
    using System.Threading.Tasks;


    internal class DeviceController
    {

        private const int _taskKillTimeout_ms = 2000;

        private const int _defaultCtrlPort = 10001; // HITME_CTRLPORT (in and out)

        /// <summary>
        ///  Field for the task.
        /// </summary>
        private Task _ctrlTask = Task.CompletedTask;

        private bool run = true;

        /// <summary>
        /// Port to user for control communication.
        /// </summary>
        public int CtrlPort { get; init; } = _defaultCtrlPort;

        /// <summary>
        /// Constructor.
        /// </summary>
        public DeviceController() { }

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
                           Console.WriteLine($"{ep.Address}:{ep.Port} {UTF8Encoding.UTF8.GetString(data)}");
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
