using Newtonsoft.Json;
using System.Collections.Generic;

namespace RealTimeAndWeather.Networking.API.OpenMeteo
{
    public class Geocoding
    {
        [JsonProperty("results")]
        public List<City> Cities { get; set; } = new List<City>();

        [JsonProperty("generationtime_ms")]
        public float TimeElapsed { get; set; }

        public static Geocoding Load(string json) => JsonConvert.DeserializeObject<Geocoding>(json);
    }
}
