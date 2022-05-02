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
        public BMA020Bandwidth Bandwidth { get; set; } = BMA020Bandwidth.BMA020_BW_25HZ;

        [JsonPropertyName("millis")]
        public int TimeStamp_ms { get; set; } = 0;

        [JsonPropertyName("start")]
        public bool Start { get; set; } = false;

        public static JsonDeviceStatusMessage FromJson(string jsonString)
        {
            JsonDeviceStatusMessage message = new ();
            try 
            {
                message = JsonSerializer.Deserialize<JsonDeviceStatusMessage>(jsonString) ?? new JsonDeviceStatusMessage();
            }
            catch (JsonException e)
            {
                Console.WriteLine(e.Message);
            }

            return message;
        }

        public static string ToJson(JsonDeviceStatusMessage msg)
        {
            try
            {
                return JsonSerializer.Serialize<JsonDeviceStatusMessage>(msg);
            }
            catch (JsonException e)
            {
                Console.WriteLine(e.Message);
            }
            return string.Empty;
        }

        public override string ToString() => JsonSerializer.Serialize(this);

    }
}
