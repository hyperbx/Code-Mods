using IniParser;
using IniParser.Model;
using ModernWpf.Controls;
using RealTimeAndWeather.Helpers;
using RealTimeAndWeather.Networking;
using RealTimeAndWeather.Networking.API.OpenMeteo;
using System;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Windows.Threading;

namespace RealTimeAndWeather.UI
{
    public partial class MainWindow : Window
    {
        DispatcherTimer SearchTimer;

        public MainWindow()
        {
            InitializeComponent();

            // Hide close button for DLL mod.
            if (App.IsRunningFromDLL)
                TitleBar.SetButtonStyle(this, (Style)FindResource("NoButtonTitleBarStyle"));
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);

            SearchBox.Focus();
        }

        private void SearchBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (SearchTimer == null)
            {
                SearchTimer = new();
                {
                    SearchTimer.Interval = TimeSpan.FromMilliseconds(500);

                    SearchTimer.Tick += (s, e) =>
                    {
                        CityList.ItemsSource = OpenMeteo.GetCitiesByName(SearchBox.Text);

                        SearchTimer?.Stop();
                    };
                }
            }
            else
            {
                SearchTimer?.Stop();
            }

            SearchTimer?.Start();
        }

        private async void Finalise(float latitude, float longitude)
        {
            string ini = Path.Combine(Environment.CurrentDirectory, "RealTimeAndWeather.ini");

            if (!File.Exists(ini))
                File.WriteAllText(ini, Properties.Resources.DefaultConfig);

            var parser = new FileIniDataParser();
            {
                IniData data = parser.ReadFile(ini);
                {
                    if (bool.Parse(data["Location"]["isFirstTimeSetup"]) && App.IsRunningFromDLL)
                    {
                        await DialogHelper.ShowEmbedded
                        (
                            "If you need to change your location, you can re-open this program from the mod directory.",
                            "Location saved!",
                            "OK"
                        );
                    }

                    data["Location"]["isFirstTimeSetup"] = "False";
                    data["Location"]["latitude"]         = $"{latitude}";
                    data["Location"]["longitude"]        = $"{longitude}";
                }

                parser.WriteFile(ini, data);
            }

            App.Current.Shutdown();
        }

        private async void Button_ManualInput_Click(object sender, RoutedEventArgs e)
        {
            var latLongPrompt = new LatLongPrompt();
            var result = await latLongPrompt.ShowAsync();

            if (result != ContentDialogResult.Primary)
                return;

            float latitude  = latLongPrompt.Latitude;
            float longitude = latLongPrompt.Longitude;

            if (latitude == 0.0f && longitude == 0.0f)
                await DialogHelper.ShowEmbedded("Welcome to Null Island.", "0°N, 0°E", "OK");

            // TODO: 3rd arg.
            Finalise(latitude, longitude);
        }

        private async void Button_OK_Click(object sender, RoutedEventArgs e)
        {
            if (!Client.IsAvailable())
            {
                await DialogHelper.ShowEmbedded("Unable to establish a connection to Open-Meteo.", "Network error", "OK");

                return;
            }

            if (CityList.SelectedItem == null)
            {
                await DialogHelper.ShowEmbedded("Please select a location.", "Invalid", "OK");

                return;
            }

            Finalise((CityList.SelectedItem as City).Latitude, (CityList.SelectedItem as City).Longitude);
        }

        private void Hyperlink_OpenMeteo_RequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            Process.Start(e.Uri.ToString());
        }
    }
}
