namespace HitMeTest
{
    using System.Threading.Tasks;

    using FakeItEasy;

    using FluentAssertions;

    using HitMe.Device;
    using HitMe.Types;

    using Microsoft.VisualStudio.TestTools.UnitTesting;

    [TestClass]
    public class DeviceTest
    {
        [TestMethod]
        public async Task ConfigureValidNet()
        {

            var device = A.Fake<IDevice>();

            DeviceNetConfig netConfig = new();

            _ = A.CallTo(() => device.ConfigureNet(netConfig))
                .Returns(
                Task.FromResult(new DeviceNetConfig
                { 
                    DeviceCtrlPort = netConfig.DeviceCtrlPort,
                    DeviceDataPort = netConfig.DeviceDataPort,
                    DeviceIP = netConfig.DeviceIP,
                }));


            DeviceNetConfig newNetConfig = await device.ConfigureNet(netConfig);


            _ = newNetConfig.Should().BeEquivalentTo(netConfig);

        }

        [TestMethod]
        public async Task ConfigureInValidNet()
        {

            var device = A.Fake<IDevice>();

            DeviceNetConfig netConfig = new();

            _ = A.CallTo(() => device.ConfigureNet(netConfig))
                .Returns(
                Task.FromResult(new DeviceNetConfig
                {
                    DeviceCtrlPort = netConfig.DeviceCtrlPort + 1,
                    DeviceDataPort = netConfig.DeviceDataPort + 1,
                    DeviceIP = System.Net.IPAddress.Any,
                }));


            DeviceNetConfig newNetConfig = await device.ConfigureNet(netConfig);
            _ = newNetConfig.Should().NotBeEquivalentTo(netConfig);
        }
    }
}