using System.Globalization;
using System.Net;
using System.Net.Http;

namespace RealTimeAndWeather.Networking
{
    public class Client
    {
        public static HttpClient HttpClient { get; private set; } = null;

        public static HttpClient Get()
        {
            if (HttpClient == null)
            {
                HttpClient = new HttpClient();
                {
                    HttpClient.DefaultRequestHeaders.TryAddWithoutValidation("User-Agent", "Mozilla/5.0 (compatible; RTAW)");
                }
            }

            return HttpClient;
        }

        public static bool IsAvailable(int timeout = 5000, string url = null)
        {
            // https://stackoverflow.com/a/2031831

            try
            {
                url ??= CultureInfo.InstalledUICulture switch
                {
                    // Iran
                    { Name: var n } when n.StartsWith("fa") =>
                        "http://www.aparat.com",

                    // China
                    { Name: var n } when n.StartsWith("zh") =>
                        "http://www.baidu.com",

                    _ =>
                        "http://www.gstatic.com/generate_204",
                };

                var request = (HttpWebRequest)WebRequest.Create(url);
                {
                    request.KeepAlive = false;
                    request.Timeout = timeout;
                }

                using (var response = (HttpWebResponse)request.GetResponse())
                    return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
