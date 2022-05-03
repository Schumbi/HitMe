namespace HitMeTest
{
    using System.Threading.Tasks;

    using FakeItEasy;

    using FluentAssertions;

    using HitMe.Device;
    using HitMe.Types;
    using HitMe.Types.Device;

    using LanguageExt;

    using Microsoft.VisualStudio.TestTools.UnitTesting;

    using static HitMe.Types.Device.DeviceConfig;

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
                Task.FromResult(Option<DeviceConfig>.Some(new DeviceConfig
                ( 
                    new DeviceNetConfig()
                    {
                        DeviceCtrlPort = netConfig.Net.DeviceCtrlPort,
                        DeviceDataPort = netConfig.Net.DeviceDataPort,
                        DeviceIP = netConfig.Net.DeviceIP,
                    },
                    DeviceMeasurementConfig.Default

                ))));


            var newConfig = await device.Configure(netConfig);
            _ = newConfig.Match(
                Some: some => _ = some.Should().BeEquivalentTo(netConfig),
                None: () => Assert.Fail("Should be some!"));

        }

        [TestMethod]
        public async Task ConfigureInValidNet()
        {

            var device = A.Fake<IDevice>();

            DeviceConfig netConfig = new(new(), DeviceMeasurementConfig.Default);

            _ = A.CallTo(() => device.Configure(netConfig))
                .Returns(
                Task.FromResult(Option<DeviceConfig>.Some(new DeviceConfig
                (
                    new DeviceNetConfig() {
                    DeviceCtrlPort = netConfig.Net.DeviceCtrlPort + 1,
                    DeviceDataPort = netConfig.Net.DeviceDataPort + 1,
                    DeviceIP = System.Net.IPAddress.Any,
                    },
                    DeviceMeasurementConfig.Default
                ))));


            var newConfig = await device.Configure(netConfig);
            _ = newConfig.Match(
                Some: c => c.Should().NotBeEquivalentTo(netConfig),
                None: () => Assert.Fail("Should be some!"));
        }
    }
}