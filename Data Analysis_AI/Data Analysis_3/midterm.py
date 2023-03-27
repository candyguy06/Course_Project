#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 31 10:25:04 2020

@author: cycu
"""
#%%==設定工作目錄
import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt
import seaborn as sns
sns.set(style="darkgrid")
import os
wkDir = "C:/Users/candy/Desktop/pj1/";   os.chdir(wkDir)
#%%

#%%==載入資料
#import numpy as np   
#import pandas as pd
items=pd.read_csv('items.csv')
shops=pd.read_csv('shops.csv')
item_cats=pd.read_csv('item_categories.csv')
sales=pd.read_csv('sales_train.csv')
test=pd.read_csv('test.csv')
print(items)
# items
#                                               item_name  ...  item_category_id
#0              ! ВО ВЛАСТИ НАВАЖДЕНИЯ (ПЛАСТ.)         D  ...                40
#1      !ABBYY FineReader 12 Professional Edition Full...  ...                76
#2          ***В ЛУЧАХ СЛАВЫ   (UNV)                    D  ...                40
#3        ***ГОЛУБАЯ ВОЛНА  (Univ)                      D  ...                40
#4            ***КОРОБКА (СТЕКЛО)                       D  ...                40
#                                                ...  ...               ...
#22165             Ядерный титбит 2 [PC, Цифровая версия]  ...                31
#22166    Язык запросов 1С:Предприятия  [Цифровая версия]  ...                54
#22167  Язык запросов 1С:Предприятия 8 (+CD). Хрустале...  ...                49
#22168                                Яйцо для Little Inu  ...                62
#22169                      Яйцо дракона (Игра престолов)  ...                69
#[22170 rows x 3 columns]
print(shops)
# shop
#                                          shop_name  shop_id
#0                     !Якутск Орджоникидзе, 56 фран        0
#1                     !Якутск ТЦ "Центральный" фран        1
#2                                  Адыгея ТЦ "Мега"        2
#3                    Балашиха ТРК "Октябрь-Киномир"        3
#                               ...                       ...
#57                          Якутск Орджоникидзе, 56       57
#58                          Якутск ТЦ "Центральный"       58
#59                           Ярославль ТЦ "Альтаир"       59
print(item_cats)
# cats
#           item_category_name  item_category_id
#0     PC - Гарнитуры/Наушники                 0
#1            Аксессуары - PS2                 1
#2            Аксессуары - PS3                 2
#3            Аксессуары - PS4                 3
#4            Аксессуары - PSP                 4
#..                        ...               ...
#79                  Служебные                79
#80         Служебные - Билеты                80
#81    Чистые носители (шпиль)                81
#82  Чистые носители (штучные)                82
#83           Элементы питания                83
#[84 rows x 2 columns]
print(sales)
# train 
#          date  date_block_num  shop_id  item_id  item_price  item_cnt_day
#0        02.01.2013               0       59    22154      999.00           1.0
#1        03.01.2013               0       25     2552      899.00           1.0
#2        05.01.2013               0       25     2552      899.00          -1.0
#3        06.01.2013               0       25     2554     1709.05           1.0
#4        15.01.2013               0       25     2555     1099.00           1.0
#            ...             ...      ...      ...         ...           ...
#2935844  10.10.2015              33       25     7409      299.00           1.0
#2935845  09.10.2015              33       25     7460      299.00           1.0
#2935846  14.10.2015              33       25     7459      349.00           1.0
#2935847  22.10.2015              33       25     7440      299.00           1.0
#2935848  03.10.2015              33       25     7460      299.00           1.0
#[2935849 rows x 6 columns]
print(test)
# test
#            ID  shop_id  item_id
#0            0        5     5037
#1            1        5     5320
#2            2        5     5233
#3            3        5     5232
#4            4        5     5268
#       ...      ...      ...
#214195  214195       45    18454
#214196  214196       45    16188
#214197  214197       45    15757
#214198  214198       45    19648
#214199  214199       45      969
#[214200 rows x 3 columns]

#%%
item_cats.head(5)
items.head(5)
shops.head(5)
sales.head(5)
test.head(5)


#%%==數據探索
from datetime import datetime
sales['year'] = pd.to_datetime(sales['date']).dt.strftime('%Y')
sales['month'] = sales.date.apply(lambda x: datetime.strptime(x,'%d.%m.%Y').strftime('%m')) #another way for same thing

sales.head(2)
#         date  date_block_num  shop_id  ...  item_cnt_day  year  month
#0  02.01.2013               0       59  ...           1.0  2013     01
#1  03.01.2013               0       25  ...           1.0  2013     01

# item_cnt_day
grouped = pd.DataFrame(sales.groupby(['year','month'])['item_cnt_day'].sum().reset_index())
sns.pointplot(x='month', y='item_cnt_day', hue='year', data=grouped)

# item_Price
grouped_price = pd.DataFrame(sales.groupby(['year','month'])['item_price'].mean().reset_index())
sns.pointplot(x='month', y='item_price', hue='year', data=grouped_price)

# total sales - time(mounth)
ts=sales.groupby(["date_block_num"])["item_cnt_day"].sum()
ts.astype('float')
plt.figure(figsize=(16,8))
plt.title('Total Sales of the whole time period')
plt.xlabel('Time')
plt.ylabel('Sales')
plt.plot(ts);

# cnt_day & price
sns.jointplot(x="item_cnt_day", y="item_price", data=sales, height=8)
plt.show()

# cnt_day value
sales.item_cnt_day.hist(bins=100)
sales.item_cnt_day.describe()
#count    2.935849e+06
#mean     1.242641e+00
#std      2.618834e+00
#min     -2.200000e+01
#25%      1.000000e+00
#50%      1.000000e+00
#75%      1.000000e+00
#max      2.169000e+03
#Name: item_cnt_day, dtype: float64
#%%

#%%==資料轉換1 remove outliers
print('Data set size before remove item price 0 cleaning:', sales.shape)
sales = sales.query('item_price > 0')
print('Data set size after remove item price 0 cleaning:', sales.shape)
#Data set size before remove item price 0 cleaning: (2935849, 8)
#Data set size after remove item price 0 cleaning: (2935848, 8)

print('Data set size before filter valid:', sales.shape)
# Only shops that exist in test set.
sales = sales[sales['shop_id'].isin(test['shop_id'].unique())]
# Only items that exist in test set.
sales = sales[sales['item_id'].isin(test['item_id'].unique())]
print('Data set size after filter valid:', sales.shape)
#Data set size before filter valid: (2935848, 8)
#Data set size after filter valid: (1224439, 8)

print('Data set size before remove outliers:', sales.shape)
sales = sales.query('item_cnt_day >= 0 and item_cnt_day <= 125 and item_price < 75000')
print('Data set size after remove outliers:', sales.shape)
#Data set size before remove outliers: (1224439, 8)
#Data set size after remove outliers: (1221451, 8)

#After cleaning plot
sns.jointplot(x="item_cnt_day", y="item_price", data=sales, height=8)
plt.show()

cleaned = pd.DataFrame(sales.groupby(['year','month'])['item_cnt_day'].sum().reset_index())
sns.pointplot(x='month', y='item_cnt_day', hue='year', data=cleaned)
#%%

#%%==資料轉換ㄉ2 transform
# Aggregate to monthly level the sales
monthly_sales=sales.groupby(["date_block_num","shop_id","item_id"])[
    "date_block_num","date","item_price","item_cnt_day"].agg({"date_block_num":'mean',"date":["min",'max'],"item_price":"mean","item_cnt_day":"sum"})

monthly_sales.head(5)
# monthly_sales
#                               date_block_num  ... item_cnt_day
#                                         mean  ...          sum
#date_block_num shop_id item_id                 ...             
#0              2       33                   0  ...          1.0
#                       482                  0  ...          1.0
#                       491                  0  ...          1.0
#                       839                  0  ...          1.0
#                       1007                 0  ...          3.0
#[5 rows x 5 columns]


sales_data_flat = monthly_sales.item_cnt_day.apply(list).reset_index()
#Keep only the test data of valid
sales_data_flat = pd.merge(test,sales_data_flat,on = ['item_id','shop_id'],how = 'left')
#fill na with 0
sales_data_flat.fillna(0,inplace = True)
sales_data_flat.drop(['shop_id','item_id'],inplace = True, axis = 1)
sales_data_flat.head(5)
#   ID  date_block_num  sum
#0   0            20.0  1.0
#1   0            22.0  1.0
#2   0            23.0  2.0
#3   0            24.0  2.0
#4   0            28.0  1.0

#We will create pivot table.
# Rows = each shop+item code
# Columns will be out time sequence
pivoted_sales = sales_data_flat.pivot_table(index='ID', columns='date_block_num',fill_value = 0,aggfunc='sum' )
pivoted_sales.head(5)
#                sum                           ...                              
#date_block_num 0.0  1.0  2.0  3.0  4.0  5.0   ... 28.0 29.0 30.0 31.0 32.0 33.0
#ID                                            ...                              
#0                 0    0    0    0    0    0  ...    1    1    1    3    1    0
#1                 0    0    0    0    0    0  ...    0    0    0    0    0    0
#2                 0    0    0    0    0    0  ...    3    2    0    1    3    1
#3                 0    0    0    0    0    0  ...    0    0    0    1    0    0
#4                 0    0    0    0    0    0  ...    0    0    0    0    0    0
#[5 rows x 34 columns]


#%%
for col in pivoted_sales.columns: 
    print(col) 
pivoted_sales()
#%%==modeling
# X we will keep all columns execpt the last one 
X_train = np.expand_dims(pivoted_sales.values[:,:-1],axis = 2)
# the last column is our prediction
y_train = pivoted_sales.values[:,-1:]

# for test we keep all the columns execpt the first one
X_test = np.expand_dims(pivoted_sales.values[:,1:],axis = 2)

# lets have a look on the shape 
print(X_train.shape,y_train.shape,X_test.shape)
# (214200, 33, 1) (214200, 1) (214200, 33, 1)

from keras.models import Sequential
from keras.layers import LSTM,Dense,Dropout
from keras.models import load_model, Model
# our defining sales model 
sales_model = Sequential()
sales_model.add(LSTM(units = 64,input_shape = (33,1)))
#sales_model.add(LSTM(units = 64,activation='relu'))
sales_model.add(Dropout(0.5))
sales_model.add(Dense(1))

sales_model.compile(loss = 'mse',optimizer = 'adam', metrics = ['mean_squared_error'])
sales_model.summary()


#%%
'''
temp = train.iloc[:,2:6]
tempx = train.iloc[:,2:5]
X = tempx.values
tempy = train.iloc[:,5:6]
y = tempy.values
print(y)
'''
'''
temp
         shop_id  item_id  item_price  item_cnt_day
0             59    22154      999.00           1.0
1             25     2552      899.00           1.0
2             25     2552      899.00           0.0
3             25     2554     1709.05           1.0
4             25     2555     1099.00           1.0
         ...      ...         ...           ...
2935840       25     7409      299.00           1.0
2935841       25     7460      299.00           1.0
2935842       25     7459      349.00           1.0
2935843       25     7440      299.00           1.0
2935844       25     7460      299.00           1.0

[2935845 rows x 4 columns]
X
array([[   59., 22154.,   999.],
       [   25.,  2552.,   899.],
       [   25.,  2552.,   899.],
       ...,
       [   25.,  7459.,   349.],
       [   25.,  7440.,   299.],
       [   25.,  7460.,   299.]])
y
[[1.]
 [1.]
 [0.]
 ...
 [1.]
 [1.]
 [1.]]
'''
'''


indices = np.random.permutation(len(X))
piece = int(len(indices) / 5)
print(piece)
# 587169

print(len(indices[:-piece]))
print(indices[:-piece])   
x = indices[:-piece]
type(x)
#2348680
#[2808114 2745981 2334457 ... 2361947 1659042  845813]

print(len(indices[-piece:]))   #-- test data number = 10
print(indices[-piece:])   #-- test data number = 10
#587169
#[1978621 1143289  784769 ... 2075302 1612600  643075]
'''



#%%