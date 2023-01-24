using RealTimeAndWeather.Networking;
using RealTimeAndWeather.Networking.API.OpenMeteo;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace RealTimeAndWeather
{
    public class OpenMeteo
    {
        public static List<City> GetCitiesByName(string name)
        {
            if (!Client.IsAvailable())
            {
                var error = new List<City>();
                {
                    error.Add
                    (
                        new City
                        {
                            Name   = "Network error",
                            Admin1 = "Unable to establish a connection to Open-Meteo."
                        }
                    );
                }

                return error;
            }

            string json = Client.Get().GetStringAsync($"https://geocoding-api.open-meteo.com/v1/search?name={HttpUtility.UrlEncode(name)}&count=100").Result;

            return Geocoding.Load(json).Cities
                .GroupBy(x => x.Admins)
                .Select(x => x.First())
                .OrderBy(x => x.CountryCode)
                .ThenBy(x => x.Name)
                .ThenBy(x => x.Admins)
                .ToList();
        }
    }
}
