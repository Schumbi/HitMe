namespace HitMe.Types
{
    using HitMe.Types.Device;

    /// <summary>
    /// Configuration of device measurement.
    /// </summary>
    /// <param name="Range">Range to use.</param>
    /// <param name="Bandwidth">Bandwidth to use.</param>
    public record DeviceMeasurementConfig(BMA020Range Range, BMA020Bandwidth Bandwidth, bool Start)
    {
        public static DeviceMeasurementConfig Default => new (BMA020Range.BMA020_RANGE_8G, BMA020Bandwidth.BMA020_BW_25HZ, false);
    }
}
