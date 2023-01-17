using ModernWpf.Controls;
using System.Threading.Tasks;

namespace RealTimeAndWeather.Helpers
{
    internal class DialogHelper
    {
        public static async Task<ContentDialogResult> ShowEmbedded(string text, string caption, string primaryButtonText = "OK", string secondaryButtonText = "")
        {
            return await new ContentDialog()
            {
                Title               = caption,
                Content             = text,
                PrimaryButtonText   = primaryButtonText,
                SecondaryButtonText = secondaryButtonText,
            }
            .ShowAsync();
        }
    }
}
