using System.Windows;

namespace RealTimeAndWeather.UI
{
    public partial class App : Application
    {
        public static bool IsRunningFromDLL { get; set; } = false;

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            if (e.Args.Length > 0)
            {
                if (e.Args[0] == "-DLL")
                    IsRunningFromDLL = true;
            }
        }
    }
}
