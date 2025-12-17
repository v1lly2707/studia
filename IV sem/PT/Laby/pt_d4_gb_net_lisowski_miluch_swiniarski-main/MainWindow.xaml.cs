using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Xml.Serialization;
using System.Collections.ObjectModel;
using System.Reflection;
using System.Xml.XPath;
using System.Xml;
using System.Xml.Linq;


namespace WpfApp1
{
    /// <summary>
    /// Logika interakcji dla klasy MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private SortingObservableCollection<Czlowiek> czlowiekList { get; set; }

        public ICommand DodajCommand { get; }
        public ICommand UsunCommand { get; }

        public MainWindow()
        {
            InitializeComponent();
            czlowiekList = new SortingObservableCollection<Czlowiek>();
            ModelDataGrid.ItemsSource = czlowiekList;
        }

        private void Version_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Wersja aplikacji: 1.0.0", "Informacje o wersji", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void GenerateData_Click(object sender, RoutedEventArgs e)
        {
            List<Czlowiek> randomCzlowiekList = Czlowiek.createRandomList(3, 2, 50);

            for (int i = 0; i < randomCzlowiekList.Count; i++)
            {
                ObjectTreeView.Items.Add(CreateTreeViewItem(randomCzlowiekList[i]));
                czlowiekList.Add(randomCzlowiekList[i]);
            }

        }

        private TreeViewItem CreateTreeViewItem(Czlowiek person)
        {
            var item = new TreeViewItem { Header = person.imie, Tag = person };
            foreach (var child in person.Dzieci)
            {
                item.Items.Add(CreateTreeViewItem(child));
            }
            return item;
        }

        private void ObjectTreeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            if (ObjectTreeView.SelectedItem is TreeViewItem selectedItem && selectedItem.Tag is Czlowiek person)
            {
                ObjectDetailsTextBlock.Text = person.wypisz();
            }
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void Create_Click(object sender, RoutedEventArgs e)
        {
            var createWindow = new CreatePersonWindow(null);
            if (createWindow.ShowDialog() == true)
            {
                Czlowiek newPerson = createWindow.NewPerson;

                if (ObjectTreeView.SelectedItem is TreeViewItem selectedItem && selectedItem.Tag is Czlowiek parent)
                {
                    parent.Dzieci.Add(newPerson);

                    selectedItem.Items.Add(CreateTreeViewItem(newPerson));
                }
                else
                {
                    ObjectTreeView.Items.Add(CreateTreeViewItem(newPerson));
                }
            }
        }

        private void Delete_Click(object sender, RoutedEventArgs e)
        {
            if (ObjectTreeView.SelectedItem is TreeViewItem selectedItem && selectedItem.Tag is Czlowiek person)
            {
                if (selectedItem.Parent is TreeViewItem parentItem && parentItem.Tag is Czlowiek parent)
                {
                    parent.Dzieci.Remove(person);
                    parentItem.Items.Remove(selectedItem);
                }
                else
                {
                    ObjectTreeView.Items.Remove(selectedItem);
                }
            }
        }

        private List<dynamic> zapytanie1Result()
        {
            return czlowiekList
                .Where(c =>
                    c.Samochod != null &&
                    c.Samochod.ID % 2 == 1)
                .Select(c => new
                {
                    SUM_OF = (c.Samochod?.liczbaDrzwi ?? 0) + (c.Samochod?.PojemnoscSilnika ?? 0.0),
                    UPPERCASE = (c.Samochod?.marka ?? string.Empty).ToUpper()
                })
                .Cast<dynamic>()
                .ToList();
        }
        private void Zapytanie_1(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Zapytanie 1", czlowiekList.Count.ToString(), MessageBoxButton.OK, MessageBoxImage.Information);

            var result = zapytanie1Result();

            if (result.Count == 0)
            {
                MessageBox.Show("No matching people found.", "Query Result", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            var sb = new StringBuilder();
            foreach (var item in result)
            {
                sb.AppendLine($"SUM_OF: {item.SUM_OF}, UPPERCASE: {item.UPPERCASE}");
            }

            MessageBox.Show(sb.ToString(), "Query Result", MessageBoxButton.OK, MessageBoxImage.Information);
        }
        private void Zapytanie_2(object sender, RoutedEventArgs e)
        {
            try
            {
                var result = zapytanie1Result() ?? new List<dynamic>();

                if (result.Count == 0)
                {
                    MessageBox.Show("No matching people found.", "Query Result", MessageBoxButton.OK, MessageBoxImage.Information);
                    return;
                }

                var avg = result
                            .Select(x =>
                            {
                                double val;
                                return double.TryParse(x.SUM_OF?.ToString(), out val) ? val : 0.0;
                            })
                            .DefaultIfEmpty(0.0)
                            .Average();

                MessageBox.Show($"Average SUM_OF: {avg:F2}", "Query Result", MessageBoxButton.OK, MessageBoxImage.Information);

            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error: {ex.Message}", "Crash Info", MessageBoxButton.OK, MessageBoxImage.Error);
            }

        }


        private void Serialize_Click(object sender, RoutedEventArgs e)
        {
            string sciezka = "czlowiek.xml";
            SeriazlizeCzlowiek(sciezka, czlowiekList.ToList());
            MessageBox.Show("Zapisano do pliku XML.", "Informacja", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void Deserialize_Click(object sender, RoutedEventArgs e)
        {
            string sciezka = "czlowiek.xml";
            czlowiekList = DeserializeCzlowiek(sciezka);
            ObjectTreeView.Items.Clear();
            foreach (var czlowiek in czlowiekList)
            {
                ObjectTreeView.Items.Add(CreateTreeViewItem(czlowiek));
            }
            MessageBox.Show("Wczytano z pliku XML.", "Informacja", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void SeriazlizeCzlowiek(string sciezka, List<Czlowiek> lista)
        {
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Czlowiek>));
                using (FileStream fs = new FileStream(sciezka, FileMode.Create))
                {
                    serializer.Serialize(fs, lista);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Błąd serializacji: " + ex.Message, "Błąd", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private SortingObservableCollection<Czlowiek> DeserializeCzlowiek(string sciezka)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(SortingObservableCollection<Czlowiek>));
            using (FileStream fs = new FileStream(sciezka, FileMode.Open))
            {
                var list = (SortingObservableCollection<Czlowiek>)serializer.Deserialize(fs);
                AssignNewIdsRecursive(list);
                return list;
            }
        }

        private void AssignNewIdsRecursive(IEnumerable<Czlowiek> lista)
        {
            foreach (var czlowiek in lista)
            {
                czlowiek.ID = (int)DateTimeOffset.UtcNow.ToUnixTimeSeconds();

                if (czlowiek.Dzieci != null && czlowiek.Dzieci.Count > 0)
                {
                    AssignNewIdsRecursive(czlowiek.Dzieci);
                }
            }
        }

        private void Create_Data_Click(object sender, RoutedEventArgs e)
        {
            var createWindow = new CreatePersonWindow(null);
            if (createWindow.ShowDialog() == true)
            {
                Czlowiek newPerson = createWindow.NewPerson;
                czlowiekList.Add(newPerson);
            }
        }

        private void Delete_Data_Click(object sender, RoutedEventArgs e)
        {
            if (ModelDataGrid.SelectedItem is Czlowiek selectedPerson)
            {
                czlowiekList.Remove(selectedPerson);
            }
            else
            {
                MessageBox.Show("Wybierz osobę do usunięcia.", "Informacja", MessageBoxButton.OK, MessageBoxImage.Information);
            }
        }


        private void Sort_Click(object sender, RoutedEventArgs e)
        {
            czlowiekList.Sort("wzrost");
        }

        private void PropertyComboBox_DropDownOpened(object sender, EventArgs e)
        {
            PropertyComboBox.Items.Clear();

            var properties = typeof(Czlowiek)
                .GetProperties(BindingFlags.Public | BindingFlags.Instance)
                .Where(p => p.PropertyType == typeof(string) || p.PropertyType == typeof(int));

            foreach (var prop in properties)
            {
                PropertyComboBox.Items.Add(prop.Name);
            }

            if (PropertyComboBox.Items.Count > 0)
                PropertyComboBox.SelectedIndex = 0;
        }

        private void ResetButton_Click(object sender, RoutedEventArgs e)
        {
            ModelDataGrid.ItemsSource = czlowiekList;
            SearchTextBox.Text = string.Empty;
            PropertyComboBox.SelectedItem = null;
        }

        private void SearchButton_Click(object sender, RoutedEventArgs e)
        {
            if (PropertyComboBox.SelectedItem is string selectedProp && !string.IsNullOrWhiteSpace(SearchTextBox.Text))
            {
                string searchText = SearchTextBox.Text.ToLower();
                var filtered = czlowiekList.Where(c =>
                {
                    var prop = c.GetType().GetProperty(selectedProp);
                    if (prop == null) return false;

                    var value = prop.GetValue(c);
                    if (value == null) return false;

                    if (prop.PropertyType == typeof(string))
                    {
                        return value.ToString().ToLower().Contains(searchText);
                    }
                    else if (prop.PropertyType == typeof(int))
                    {
                        return int.TryParse(searchText, out int num) && (int)value == num;
                    }

                    return false;
                }).ToList();

                var sb = new StringBuilder();
                foreach (var person in filtered)
                {
                    sb.AppendLine(person.wypisz());
                }

                ObjectDetailsTextBlock.Text = sb.Length > 0 ? sb.ToString() : "Brak wyników wyszukiwania.";
            }
        }

        private void SearchTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                SearchButton_Click(sender, e);
            }
        }

        private void XPath_Click(object sender, RoutedEventArgs e)
        {
            string inputPath = "czlowiek.xml";
            string outputPath = "wynik.xml";

            XmlDocument doc = new XmlDocument();
            doc.Load(inputPath);

            XPathNavigator nav = doc.CreateNavigator();

            string xpathQuery = "//wzrost";
            XPathNodeIterator nodes = nav.Select(xpathQuery);

            XmlDocument outputDoc = new XmlDocument();
            XmlElement root = outputDoc.CreateElement("wyniki");
            outputDoc.AppendChild(root);

            while (nodes.MoveNext())
            {
                string wartosc = nodes.Current.Value;

                XmlElement titleElement = outputDoc.CreateElement("wzrost");
                titleElement.InnerText = wartosc;

                root.AppendChild(titleElement);
            }

            // Zapisz do pliku
            outputDoc.Save(outputPath);

            MessageBox.Show("Zapisano wyniki do pliku XML.", "Informacja", MessageBoxButton.OK, MessageBoxImage.Information);

        }

        private void XHTML_Click(object sender, RoutedEventArgs e)
        {
            XNamespace ns = "http://www.w3.org/1999/xhtml";

            IEnumerable<(Czlowiek osoba, string parentName)> Flatten(List<Czlowiek> list, string parent)
            {
                foreach (var osoba in list)
                {
                    yield return (osoba, parent);
                    if (osoba.Dzieci != null && osoba.Dzieci.Count > 0)
                    {
                        foreach (var child in Flatten(osoba.Dzieci, osoba.imie))
                            yield return child;
                    }
                }
            }

            var rows = Flatten(czlowiekList.ToList(), null)
            .Select(tuple =>
                new XElement(ns + "tr",
                    new XElement(ns + "td", tuple.osoba.imie),
                    new XElement(ns + "td", tuple.osoba.wzrost),
                    new XElement(ns + "td", tuple.osoba.waga),
                    new XElement(ns + "td", tuple.parentName ?? "")
                )
            );

            var dokument = new XDocument(
                new XElement(ns + "html",
                    new XElement(ns + "head",
                        new XElement(ns + "title", "Lista osób")
                    ),
                    new XElement(ns + "body",
                        new XElement(ns + "table",
                            new XAttribute("border", "1"),
                            new XElement(ns + "tr",
                                new XElement(ns + "th", "Imię"),
                                new XElement(ns + "th", "Wzrost"),
                                new XElement(ns + "th", "Waga"),
                                new XElement(ns + "th", "Rodzic")
                            ),
                            rows
                        )
                    )
                )
            );

            dokument.Save("czlowiek.xhtml");
            MessageBox.Show("Zapisano dane do czlowiek.xhtml", "Informacja", MessageBoxButton.OK, MessageBoxImage.Information);
        }



    }
}
