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
        /// Device ip adress.
        /// </summary>
        private readonly IPEndPoint _ipe;

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
        /// <param name="ipe">IP info to use.</param>
        public DeviceController(IPEndPoint ipe) => _ipe = ipe;

        /// <summary>
        /// Is task running?
        /// </summary>
        public bool Running => _ctrlTask.Status == TaskStatus.Running;

        /// <summary>
        /// Start the control task.
        /// </summary>
        public void Start()
        {
            _ctrlTask = Task.Run(() =>
           {
               using var udpClient = new UdpClient(_ipe.Port);
               while (run)
               {
                   IPEndPoint ep = _ipe;
                   byte[]? data = udpClient.Receive(ref ep);
                   if (_ipe.Equals(ep))
                   {
                       Console.WriteLine($"{ep.Address}:{ep.Port} {UTF8Encoding.UTF8.GetString(data)}");
                   }
               }
           });
        }

        /// <summary>
        /// Stops controll task.
        /// </summary>
        public void Stop()
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
