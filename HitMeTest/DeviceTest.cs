namespace HitMeTest
{
    using System.Threading.Tasks;

    using FakeItEasy;

    using FluentAssertions;

    using HitMe.Device;
    using HitMe.Types;
    using HitMe.Types.Device;

    using Microsoft.VisualStudio.TestTools.UnitTesting;

    [TestClass]
    public class DeviceTest
    {
        [TestMethod]
        public async Task ConfigureValidNet()
        {

            var device = A.Fake<IDevice>();

            DeviceConfig netConfig = new(new(), DeviceMeasurementConfig.Default);

            _ = A.CallTo(() => device.Configure(netConfig))
                .Returns(
                Task.FromResult(new DeviceConfig
                ( 
                    new DeviceNetConfig()
                    {
                        DeviceCtrlPort = netConfig.Net.DeviceCtrlPort,
                        DeviceDataPort = netConfig.Net.DeviceDataPort,
                        DeviceIP = netConfig.Net.DeviceIP,
                    },
                    DeviceMeasurementConfig.Default

                )));


            var newConfig = await device.Configure(netConfig);
            var newNetConfig = newConfig.Net;

            _ = newNetConfig.Should().BeEquivalentTo(netConfig);

        }

        [TestMethod]
        public async Task ConfigureInValidNet()
        {

            var device = A.Fake<IDevice>();

            DeviceConfig netConfig = new(new(), DeviceMeasurementConfig.Default);

            _ = A.CallTo(() => device.Configure(netConfig))
                .Returns(
                Task.FromResult(new DeviceConfig
                (
                    new DeviceNetConfig() {
                    DeviceCtrlPort = netConfig.Net.DeviceCtrlPort + 1,
                    DeviceDataPort = netConfig.Net.DeviceDataPort + 1,
                    DeviceIP = System.Net.IPAddress.Any,
                    },
                    DeviceMeasurementConfig.Default
                )));


            DeviceConfig newConfig = await device.Configure(netConfig);
            _ = newConfig.Should().NotBeEquivalentTo(netConfig);
        }
    }
}