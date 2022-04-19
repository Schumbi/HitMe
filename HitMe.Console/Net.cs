namespace HitMe.Console
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Net;
    using System.Net.NetworkInformation;
    using System.Net.Sockets;
    using System.Text;
    using System.Threading.Tasks;



    internal class Net
    {
        private const int ctrlPort = 10001; // HITME_CTRLPORT (in and out)
        private const int dataPort = 10000; // HITME_DATAPORT (in only)

        private UdpClient _udpCtrl = new(ctrlPort);
        private UdpClient _udpData = new();


        private bool run = true;


        public Net()
        {
        }


        public async Task RunCtrlUpdate()
        {
            await Task.Run(() =>
            {
                while (run)
                {
                    IPEndPoint? ep = new (IPAddress.Parse("10.8.1.2"), ctrlPort);
                    byte[]? data = _udpCtrl.Receive(ref ep);
                    Console.WriteLine($"{ep.Address}:{ep.Port} {UTF8Encoding.UTF8.GetString(data)}");
                }
            });
        }
    }
}
