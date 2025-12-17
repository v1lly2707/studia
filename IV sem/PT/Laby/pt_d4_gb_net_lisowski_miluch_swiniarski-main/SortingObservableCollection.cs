using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    public class SortingObservableCollection<T> : ObservableCollection<T>
    {
        public void Sort(string propertyName)
        {
            var property = typeof(T).GetProperty(propertyName);

            if (property == null)
                throw new ArgumentException($"Brak właściwości {propertyName}");

            if (typeof(IComparable).IsAssignableFrom(property.PropertyType))
            {
                var sorted = this.OrderBy(x => property.GetValue(x), Comparer<object>.Create((a, b) =>
                {
                    return ((IComparable)a).CompareTo(b);
                })).ToList();
                this.Clear();
                foreach (var item in sorted)
                {
                    this.Add(item);
                }
            }
            else
            {
                throw new InvalidOperationException("Elementy kolekcji nie implementują interfejsu IComparable.");
            }
        }

        public T Find(string propertyName, object value)
        {
            var property = typeof(T).GetProperty(propertyName);

            return this.First(x => object.Equals(property.GetValue(x), value));
        }

    }
}
