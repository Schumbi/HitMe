namespace HitMe.Device.Extensions
{
    using System;
    using System.Threading.Tasks;

    internal static class TimerExtensions
    {

        public static async Task<bool> WaitFor<T, R>(this T obj, Func<T, R> func, R Should, TimeSpan period, int times)
            where T : IEquatable<T> where R : IEquatable<R>
        {
            if (obj == null) throw new ArgumentNullException(nameof(obj));

            if (func == null) throw new ArgumentNullException(nameof(func));

            if (period == TimeSpan.Zero) throw new ArgumentOutOfRangeException(nameof(period));

            if (times == 0) throw new ArgumentOutOfRangeException(nameof(times));

            return await Task.Run(() =>
            {
                bool succeeded = false;
                int count = 0;

                do
                {
                    R erg = func(obj);
                    succeeded = erg.Equals(Should);

                    if (!succeeded)
                    {
                        Thread.Sleep(period);
                    }
                    count++;

                } while (!succeeded && count < times);
                return succeeded;
            });

        }

    }
}
