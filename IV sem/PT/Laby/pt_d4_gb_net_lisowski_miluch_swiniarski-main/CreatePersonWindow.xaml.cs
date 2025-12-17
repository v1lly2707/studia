using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Logika interakcji dla klasy CreatePersonWindow.xaml
    /// </summary>
    public partial class CreatePersonWindow : Window
    {
        public Czlowiek NewPerson { get; private set; }

        public CreatePersonWindow(Czlowiek parent)
        {
            InitializeComponent();
        }

        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            if (int.TryParse(HeightTextBox.Text, out int height) && int.TryParse(WeightTextBox.Text, out int weight))
            {
                NewPerson = new Czlowiek
                {
                    imie = NameTextBox.Text,
                    wzrost = height,
                    waga = weight
                };
                DialogResult = true;
                
                Close();
            }
            else
            {
                MessageBox.Show("Podano nieprawidłowe dane.", "Błąd", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void TextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (sender is TextBox textBox)
            {
                if (textBox.Text == "Imię" || textBox.Text == "Wzrost" || textBox.Text == "Waga")
                {
                    textBox.Text = string.Empty;
                    textBox.Foreground = Brushes.Black;
                }
            }
        }

        private void TextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            if (sender is TextBox textBox)
            {
                if (string.IsNullOrWhiteSpace(textBox.Text))
                {
                    if (textBox == NameTextBox)
                        textBox.Text = "Imię";
                    else if (textBox == HeightTextBox)
                        textBox.Text = "Wzrost";
                    else if (textBox == WeightTextBox)
                        textBox.Text = "Waga";

                    textBox.Foreground = Brushes.Gray;
                }
            }
        }
    }
}
