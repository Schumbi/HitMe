namespace HitMe.Types
{
    using System.Text.Json;
    using System.Text.Json.Serialization;

    using HitMe.Types.Device;

    /// <summary>
    /// Json type for status messages.
    /// </summary>
    /// <remarks>Todo: Set correct types.</remarks>
    [JsonSerializable(typeof(JsonDeviceStatusMessage))]
    public class JsonDeviceStatusMessage
    {
        [JsonPropertyName("type")]
        public MessageType Type { get; set; } = MessageType.PARSEERR;

        [JsonPropertyName("readable")]
        public bool Readable { get; set; } = false;

        [JsonPropertyName("range")]
        public BMA020Range Range { get; set; } = BMA020Range.BMA020_RANGE_2G;

        [JsonPropertyName("bandwidth")]
        public BMA020BANDWIDTH Bandwidth { get; set; } = BMA020BANDWIDTH.BMA020_BW_25HZ;

        [JsonPropertyName("millis")]
        public int TimeStamp_ms { get; set; } = 0;

        public static JsonDeviceStatusMessage FromJson(string jsonString)
        {
            JsonDeviceStatusMessage message = new ();
            try {
                message = JsonSerializer.Deserialize<JsonDeviceStatusMessage>(jsonString) ?? new JsonDeviceStatusMessage();
            }
            catch (JsonException e)
            {
                Console.WriteLine(e.Message);
            }

            return message;
        }

        public override string ToString() => JsonSerializer.Serialize(this);

    }
}
