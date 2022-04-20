namespace HitMe.Device
{
    using System;
    using System.Net;
    using System.Net.Sockets;
    using System.Text;
    using System.Threading.Tasks;

    internal class DeviceController
    {
        private const int ctrlPort = 10001; // HITME_CTRLPORT (in and out)
        

        private readonly IPAddress _ip;

        private bool _run = false;

        public DeviceController(IPAddress ip) => _ip = ip;

        public async Task StartController()
        {

            await Task.Run(() =>
            {
                using var udpClient = new UdpClient(ctrlPort);
                while (_run)
                {

                    IPEndPoint? ep = new(_ip, ctrlPort);
                    if (ep.Address == _ip)
                    {
                        byte[]? data = udpClient.Receive(ref ep);
                        Console.WriteLine($"{ep.Address}:{ep.Port} {UTF8Encoding.UTF8.GetString(data)}");
                    }
                }
            });
        }

        /// <summary>
        /// Is contoller running?
        /// </summary>
        public bool Running => _run;
    }
}
