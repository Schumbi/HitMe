using HitMe.Console;

Console.WriteLine("Hello, World!");

DeviceController runner = new()
{
    Ipe = System.Net.IPEndPoint.Parse("10.8.1.228:10001"),
};

runner.Start();
Console.ReadKey();
runner.Stop();
Console.WriteLine($"Controller is running {runner.Running}");

Console.ReadKey();