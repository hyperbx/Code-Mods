using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using System.Security;

namespace OriginsSaveEditor.Bridge
{
    public class Proxy : MarshalByRefObject
    {
        public void Run()
        {
            Main.PostInit();
        }
    }

    public class Main
    {
        private static AppDomain _childDomain;

        [DllExport(CallingConvention.Cdecl)]
        public static void Init()
        {
            try
            {
                Type proxyType = typeof(Proxy);

                PermissionSet permissionSet = new PermissionSet(PermissionState.Unrestricted);
                {
                    permissionSet.AddPermission(new SecurityPermission(SecurityPermissionFlag.AllFlags));
                }

                AppDomainSetup appDomainSetup = new AppDomainSetup()
                {
                    ApplicationBase = Path.GetDirectoryName(proxyType.Assembly.Location)
                };

                _childDomain = AppDomain.CreateDomain("Origins Save Editor", null, appDomainSetup, permissionSet);

                dynamic initProxy = _childDomain.CreateInstanceFrom(proxyType.Assembly.Location, proxyType.FullName).Unwrap();
                {
                    initProxy.Run();
                }
            }
            catch
            {
                PostInit();
            }
        }

        public static void PostInit()
        {
            Console.WriteLine("Bridged!");
        }
    }
}
