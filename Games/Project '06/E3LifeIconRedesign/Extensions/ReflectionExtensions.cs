using System.Reflection;

namespace UncappedFramerate.Extensions
{
    public static class ReflectionExtensions
    {
        public static T GetFieldValue<T>(this object in_obj, string in_name)
        {
            var field = in_obj.GetType().GetField
            (
                in_name,
                BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static
            );

            return (T)field?.GetValue(in_obj);
        }

        public static T SetFieldValue<T>(this object in_obj, string in_name, T in_value)
        {
            var field = in_obj.GetType().GetField
            (
                in_name,
                BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static
            );

            field?.SetValue(in_obj, in_value);

            return GetFieldValue<T>(in_obj, in_name);
        }

        public static T Invoke<T>(this object in_obj, string in_methodName, params object[] in_args)
        {
            var methodInfo = in_obj.GetType().GetMethod
            (
                in_methodName,
                BindingFlags.NonPublic | BindingFlags.Instance
            );

            if (methodInfo != null)
                return (T)methodInfo.Invoke(in_obj, in_args);

            return default;
        }
    }
}
