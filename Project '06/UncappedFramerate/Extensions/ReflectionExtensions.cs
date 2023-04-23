using System.Reflection;

namespace UncappedFramerate.Extensions
{
    public static class ReflectionExtensions
    {
        public static T GetFieldValue<T>(this object obj, string name)
        {
            var field = obj.GetType().GetField
            (
                name,
                BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static
            );

            return (T)field?.GetValue(obj);
        }

        public static T SetFieldValue<T>(this object obj, string name, T value)
        {
            var field = obj.GetType().GetField
            (
                name,
                BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static
            );
            {
                field?.SetValue(obj, value);
            }

            return GetFieldValue<T>(obj, name);
        }

        public static T Invoke<T>(this object obj, string methodName, params object[] args)
        {
            var methodInfo = obj.GetType().GetMethod
            (
                methodName,
                BindingFlags.NonPublic | BindingFlags.Instance
            );

            if (methodInfo != null)
                return (T)methodInfo.Invoke(obj, args);

            return default;
        }
    }
}
