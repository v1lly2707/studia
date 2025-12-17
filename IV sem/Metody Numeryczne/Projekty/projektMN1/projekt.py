import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


DATA_FILE = 'eurpln_d.csv'
STOCK_NAME = 'EUR'
CURRENCY = 'PLN'
PLOT_TITLE = 'EUR to PLN exchange rate'

def load_data(data_file):
    data = pd.read_csv(data_file, delimiter=',')
    data.rename(columns={'Data': 'Date', 'Zamkniecie': 'Close'}, inplace=True)
    data.Date = pd.to_datetime(data['Date'])
    data = data.sort_values('Date')
    return data

data = load_data(DATA_FILE)

# 1 wykres
plt.figure().set_figwidth(15)
plt.plot(data['Date'], data['Close'], label=STOCK_NAME)
plt.xlabel('Date')
plt.ylabel('Close price')
plt.title(PLOT_TITLE)
plt.legend()
plt.savefig('plot1.png')
plt.show()


#liczenie EMA
def EMA(data: np.ndarray, N: int):
    alpha = 2 / (N + 1)
    factors = (1 - alpha) ** np.arange(N + 1)
    factors = factors[::-1]
    result = np.nan * np.zeros_like(data)
    for i in range(N, len(data)):
        result[i] = np.sum(data[i-N:i+1] * factors) / factors.sum()
    return result

macd = EMA(data['Close'].to_numpy(), 12) - EMA(data['Close'].to_numpy(), 26)
signal = EMA(macd, 9)

data.insert(0, 'MACD', macd, allow_duplicates=True)
data.insert(1, 'Signal', signal, allow_duplicates=True)

data = data.dropna()

data = data[-1000:]

# wykres ceny z okresu
plt.figure().set_figwidth(15)
plt.plot(data['Date'], data['Close'], label=STOCK_NAME)
plt.xlabel('Date')
plt.ylabel(f'Price [{CURRENCY}]')
plt.title(f'{PLOT_TITLE} from {data.iloc[-999]["Date"].date()} to {data.iloc[-1]["Date"].date()}')
plt.legend()
plt.savefig('plot2.png')
plt.show()

# wykres macd i signal
plt.figure().set_figwidth(15)
plt.plot(data['Date'], data['MACD'], label='MACD')
plt.plot(data['Date'], data['Signal'], label='Signal')

buy = np.argwhere(np.diff(np.sign(data['MACD'] - data['Signal'])) > 0).flatten() + 1
sell = np.argwhere(np.diff(np.sign(data['MACD'] - data['Signal'])) < 0).flatten() + 1

buy_rows = data.iloc[buy]
sell_rows = data.iloc[sell]

plt.plot(buy_rows['Date'], buy_rows['MACD'], 'g^', label='Buy signal')
plt.plot(sell_rows['Date'], sell_rows['MACD'], 'rv', label='Sell signal')
plt.xlabel('Date')
plt.title('MACD and Signal')
plt.legend()
plt.savefig('macd_signal.png')
plt.show()

# wykres ceny z transakcjami
plt.figure().set_figwidth(15)
plt.plot(data['Date'], data['Close'], label=STOCK_NAME)
plt.plot(buy_rows['Date'], buy_rows['Close'], 'g^', label='Buy signal')
plt.plot(sell_rows['Date'], sell_rows['Close'], 'rv', label='Sell signal')
plt.xlabel('Date')
plt.ylabel(f'Price [{CURRENCY}]')
plt.title(f'{PLOT_TITLE} from {data.iloc[-999]["Date"].date()} to {data.iloc[-1]["Date"].date()}')
plt.legend()
plt.savefig('plot3.png')
plt.show()

# 1 okres
interesting_date = (data['Date'] >= '2020-05-13') & (data['Date'] <= '2020-12-31')
interesting_part = data[interesting_date]
interesting_buy = buy_rows.loc[interesting_date]
interesting_sell = sell_rows.loc[interesting_date]

plt.figure().set_figwidth(12)
plt.plot(interesting_part['Date'], interesting_part['Close'], label=STOCK_NAME)
plt.plot(interesting_buy['Date'], interesting_buy['Close'], 'g^', label='Buy signal')
plt.plot(interesting_sell['Date'], interesting_sell['Close'], 'rv', label='Sell signal')

for i, row in interesting_buy.iterrows():
    plt.annotate(f'{row["Close"]:.2f}', xy=(row["Date"], row["Close"]), fontsize=12, ha='right', va='bottom')

for i, row in interesting_sell.iterrows():
    plt.annotate(f'{row["Close"]:.2f}', xy=(row["Date"], row["Close"]), fontsize=12, ha='left', va='bottom')

plt.xlabel('Date')
plt.ylabel(f'Price [{CURRENCY}]')
plt.title(f'{PLOT_TITLE} from {interesting_part.iloc[0]["Date"].date()} to {interesting_part.iloc[-1]["Date"].date()}')
plt.legend()
plt.savefig('plot4.png')
plt.show()

# 2 okres
interesting_date = (data['Date'] >= '2023-04-06') & (data['Date'] <= '2023-06-30')
interesting_part = data[interesting_date]
interesting_buy = buy_rows.loc[interesting_date]
interesting_sell = sell_rows.loc[interesting_date]

plt.figure().set_figwidth(10)
plt.plot(interesting_part['Date'], interesting_part['Close'], label=STOCK_NAME)
plt.plot(interesting_buy['Date'], interesting_buy['Close'], 'g^', label='Buy signal')
plt.plot(interesting_sell['Date'], interesting_sell['Close'], 'rv', label='Sell signal')

for i, row in interesting_buy.iterrows():
    plt.annotate(f'{row["Close"]:.2f}', xy=(row["Date"], row["Close"]), fontsize=12, ha='right', va='bottom')

for i, row in interesting_sell.iterrows():
    plt.annotate(f'{row["Close"]:.2f}', xy=(row["Date"], row["Close"]), fontsize=12, ha='right', va='bottom')

plt.xlabel('Date')
plt.ylabel(f'Price [{CURRENCY}]')
plt.title(f'{PLOT_TITLE} from {interesting_part.iloc[0]["Date"].date()} to {interesting_part.iloc[-1]["Date"].date()}')
plt.legend()
plt.savefig('plot5.png')
plt.show()

# symulacja transakcji
def trading_simulation(data: pd.DataFrame, initial_money: float, initial_stocks: int):
    money = initial_money
    stocks = initial_stocks
    portfolio_value = [money + stocks * data.iloc[0]['Close']]  
    successful_trades = 0
    unsuccessful_trades = 0
    
    for i in range(1, len(data)):
        if data.iloc[i]['MACD'] > data.iloc[i]['Signal'] and money > 0:  #kupno
            stocks_bought = money // data.iloc[i]['Close']
            money -= stocks_bought * data.iloc[i]['Close']
            stocks += stocks_bought

        elif data.iloc[i]['MACD'] < data.iloc[i]['Signal'] and stocks > 0:  #sprzedaz
            sell_value = stocks * data.iloc[i]['Close']
            profit = sell_value - (stocks * data.iloc[i-1]['Close'])
            if profit > 0:
                successful_trades += 1
            else:
                unsuccessful_trades += 1
            money += sell_value
            stocks = 0

        portfolio_value.append(money + stocks * data.iloc[i]['Close'])  
    
    final_money = money + stocks * data.iloc[-1]['Close']
    return final_money, portfolio_value, successful_trades, unsuccessful_trades

initial_money = 1000  
initial_stocks = 0    
final_money, portfolio_values, successful_trades, unsuccessful_trades = trading_simulation(data, initial_money, initial_stocks)


if len(portfolio_values) < len(data):
    portfolio_values.append(portfolio_values[-1])  

data['Portfolio Value'] = portfolio_values

#wykres wartosci portfolio
plt.figure(figsize=(15, 5))
plt.plot(data['Date'], data['Portfolio Value'], label='Portfolio Value')
plt.xlabel('Date')
plt.ylabel(f'Value [{CURRENCY}]')
plt.title('Portfolio Value Over Time')
plt.legend()
plt.savefig('portfolio_value.png')
plt.show()

#statystyki
print(f"Final capital: {final_money:.2f} {CURRENCY}")
print(f"Successful trades: {successful_trades}")
print(f"Unsuccessful trades: {unsuccessful_trades}")
success_rate = (successful_trades / (successful_trades + unsuccessful_trades)) * 100 if (successful_trades + unsuccessful_trades) > 0 else 0
print(f"Success rate: {success_rate:.2f}%")


data = data.dropna()


interesting_date_2020 = (data['Date'] >= '2020-05-13') & (data['Date'] <= '2020-12-31')
interesting_data_2020 = data[interesting_date_2020]


interesting_date_2023 = (data['Date'] >= '2023-04-06') & (data['Date'] <= '2023-06-30')
interesting_data_2023 = data[interesting_date_2023]

# macd i signal dla 1 okresu
plt.figure().set_figwidth(15)
plt.plot(interesting_data_2020['Date'], interesting_data_2020['MACD'], label='MACD')
plt.plot(interesting_data_2020['Date'], interesting_data_2020['Signal'], label='Signal')

buy_2020 = np.argwhere(np.diff(np.sign(interesting_data_2020['MACD'] - interesting_data_2020['Signal'])) > 0).flatten() + 1
sell_2020 = np.argwhere(np.diff(np.sign(interesting_data_2020['MACD'] - interesting_data_2020['Signal'])) < 0).flatten() + 1

buy_rows_2020 = interesting_data_2020.iloc[buy_2020]
sell_rows_2020 = interesting_data_2020.iloc[sell_2020]

plt.plot(buy_rows_2020['Date'], buy_rows_2020['MACD'], 'g^', label='Buy signal')
plt.plot(sell_rows_2020['Date'], sell_rows_2020['MACD'], 'rv', label='Sell signal')
plt.xlabel('Date')
plt.title('MACD and Signal - 2020')
plt.legend()
plt.savefig('macd_signal2020.png')
plt.show()

# macd i signal dla 2 okresu
plt.figure().set_figwidth(15)
plt.plot(interesting_data_2023['Date'], interesting_data_2023['MACD'], label='MACD')
plt.plot(interesting_data_2023['Date'], interesting_data_2023['Signal'], label='Signal')

buy_2023 = np.argwhere(np.diff(np.sign(interesting_data_2023['MACD'] - interesting_data_2023['Signal'])) > 0).flatten() + 1
sell_2023 = np.argwhere(np.diff(np.sign(interesting_data_2023['MACD'] - interesting_data_2023['Signal'])) < 0).flatten() + 1

buy_rows_2023 = interesting_data_2023.iloc[buy_2023]
sell_rows_2023 = interesting_data_2023.iloc[sell_2023]

plt.plot(buy_rows_2023['Date'], buy_rows_2023['MACD'], 'g^', label='Buy signal')
plt.plot(sell_rows_2023['Date'], sell_rows_2023['MACD'], 'rv', label='Sell signal')
plt.xlabel('Date')
plt.title('MACD and Signal - 2023')
plt.legend()
plt.savefig('macd_signal2023.png')
plt.show()