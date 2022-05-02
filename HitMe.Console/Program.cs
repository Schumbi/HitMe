
using HitMe.Device;
using HitMe.Types;
using HitMe.Types.Device;

using LanguageExt;

using static HitMe.Device.DeviceStatusListener;
using static HitMe.Types.Device.DeviceConfig;
using static LanguageExt.Prelude;

Console.WriteLine("### HitMe Console ###");

DeviceStatusListener runner = new()
{
    Ipe = System.Net.IPEndPoint.Parse("10.8.1.228:10001"),
};

Atom<bool> running = Atom(true);


void HandleStatusUpdate(object? sender, DeviceStatusEventArgs args)
{
    if(args != null)
    {
        var c = args;
        Console.WriteLine($"{c.RemoteTimeStamp_ms}: {c.DeviceNetConfig.DeviceIP}:{c.DeviceNetConfig.DeviceCtrlPort} =>  R: {c.DeviceMeasurementConfig.Range} B:{c.DeviceMeasurementConfig.Bandwidth} S: {c.DeviceMeasurementConfig.Start}");
    }
}


runner.StatusChangedEvent += HandleStatusUpdate;

Console.ReadKey();
runner.Start();
Console.ReadKey();

var lastConf = runner.GetLastConfig();
lastConf.IfSome(c =>
{
    DeviceMeasurementConfig mC = new DeviceMeasurementConfig(
        HitMe.Types.Device.BMA020Range.BMA020_RANGE_4G,
        c.Measurement.Bandwidth,
        c.Measurement.Start
        );
    DeviceConfig nC = new(c.Net, mC);
    runner.Configure(nC);
});

Console.ReadKey();
runner.Stop();
running.Swap(f => false);

Console.WriteLine($"Controller is running {runner.Running}");
Console.WriteLine($"Any key -> exit!");

Console.ReadKey();