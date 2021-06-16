using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace MainWebApplication.Models
{
    public class BleMacJsonConverter : JsonConverter<byte[]>
    {
        public override byte[] Read(
            ref Utf8JsonReader reader,
            Type typeToConvert,
            JsonSerializerOptions options) => reader
                .GetString()
                .Split(':')
                .Select(b => Convert.ToByte(b, 16))
                .ToArray();

        public override void Write(
            Utf8JsonWriter writer,
            byte[] blemac,
            JsonSerializerOptions options) => 
            writer.WriteStringValue(string.Join(":", 
                blemac.Select(b => b.ToString("X2"))));
    }
}
