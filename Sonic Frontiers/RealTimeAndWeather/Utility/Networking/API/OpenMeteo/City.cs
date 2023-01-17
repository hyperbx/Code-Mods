using Newtonsoft.Json;
using System.Linq;
using System.Text;

namespace RealTimeAndWeather.Networking.API.OpenMeteo
{
    public class City
    {
        [JsonProperty("id")]
        public int ID { get; set; }

        [JsonProperty("name")]
        public string Name { get; set; }

        [JsonProperty("latitude")]
        public float Latitude { get; set; }

        [JsonProperty("longitude")]
        public float Longitude { get; set; }

        [JsonProperty("elevation")]
        public float Elevation { get; set; }

        [JsonProperty("feature_code")]
        public string FeatureCode { get; set; }

        [JsonProperty("country_code")]
        public string CountryCode { get; set; }

        [JsonProperty("admin1_id")]
        public int AdminId1 { get; set; }

        [JsonProperty("admin2_id")]
        public int AdminId2 { get; set; }

        [JsonProperty("admin3_id")]
        public int AdminId3 { get; set; }

        [JsonProperty("admin4_id")]
        public int AdminId4 { get; set; }

        [JsonProperty("timezone")]
        public string TimeZone { get; set; }

        [JsonProperty("population")]
        public int Population { get; set; }

        [JsonProperty("country_id")]
        public int CountryID { get; set; }

        [JsonProperty("country")]
        public string Country { get; set; }

        [JsonProperty("admin1")]
        public string Admin1 { get; set; }

        [JsonProperty("admin2")]
        public string Admin2 { get; set; }

        [JsonProperty("admin3")]
        public string Admin3 { get; set; }

        [JsonProperty("admin4")]
        public string Admin4 { get; set; }

        [JsonIgnore]
        public string Admins
        {
            get => string.Join(", ", new[] { Admin1, Admin2, Admin3, Admin4 }.Where(x => !string.IsNullOrEmpty(x)));
        }
    }
}
