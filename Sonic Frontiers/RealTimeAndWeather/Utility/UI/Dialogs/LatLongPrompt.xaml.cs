using ModernWpf.Controls;

namespace RealTimeAndWeather.UI
{
    public partial class LatLongPrompt
    {
        public float Latitude { get; set; } = 0.0f;

        public float Longitude { get; set; } = 0.0f;

        public LatLongPrompt()
        {
            InitializeComponent();
        }

        private void ContentDialog_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            Latitude  = (float)LatitudeField.Value;
            Longitude = (float)LongitudeField.Value;
        }

        private void ContentDialog_SecondaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
        {
            args.GetDeferral().Complete();
        }
    }
}
