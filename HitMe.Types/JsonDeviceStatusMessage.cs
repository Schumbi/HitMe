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
        public MessageType Type { get; set; }

        [JsonPropertyName("readable")]
        public bool Readable { get; set; }

        [JsonPropertyName("range")]
        public BMA020Range Range { get; set; }

        [JsonPropertyName("bandwidth")]
        public BMA020BANDWIDTH Bandwidth { get; set; }

        [JsonPropertyName("millis")]
        public int TimeStamp_ms { get; set; }

        public static JsonDeviceStatusMessage FromJson(string jsonString)
        {
            JsonDeviceStatusMessage message = new JsonDeviceStatusMessage();
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
