# -*- coding: utf-8 -*-
"""Untitled4.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1OBhGpaBQrqv3oVOmYPUqx9SfN47uGZEZ
"""

#!pip install pandas
#!pip install matplotlib
#!pip install seaborn
import pandas as pd
import matplotlib
import seaborn as sns

data=pd.read_csv(r'kc_house_data.csv')

data.head()

# exploratory data analysis
data.shape

pd.set_option('display.float_format', lambda x: '%.5f' % x)

data.describe()

data.info()

data.isnull().sum()

data.columns

X=data[['bedrooms', 'bathrooms', 'sqft_living',
       'sqft_lot', 'floors', 'waterfront', 'view', 'condition', 'grade',
       'sqft_above', 'sqft_basement',
        'sqft_living15', 'sqft_lot15']]

X

Y=data['price']

Y

from sklearn.model_selection import train_test_split

X_train, X_test , Y_train , Y_test = train_test_split(X,Y,test_size=0.25,random_state=101)

X_train

Y_train

X_test

Y_test

from sklearn.preprocessing import StandardScaler
std=StandardScaler()

X_train_std=std.fit_transform(X_train)
X_test_std=std.transform(X_test)

X_train

X_train_std

X_test_std

Y_train

Y_test

from sklearn.linear_model import LinearRegression
lr=LinearRegression()

lr.fit(X_train_std,Y_train)

Y_pred=lr.predict(X_test_std)

Y_pred

Y_test

from sklearn.metrics import mean_absolute_error,r2_score

mean_absolute_error(Y_test,Y_pred)

X_test

X_test.loc[7148]

r2_score(Y_test,Y_pred)

new_house=[[3,1,1520,5000,1,0,0,3,8,1000,1,2000,5000]]

new_house_std=std.transform(new_house)

new_house_std

int(lr.predict(new_house_std))

"""
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import RandomForestRegressor
reg = RandomForestRegressor()
reg.fit(X_train, Y_train)


print(regr.predict([[3,1,1520,5000,1,0,0,3,8,1000,1,2000,5000,5000,2200,1400,2000,1100,800,45,95,45,2000,2100,340,250,789,600,550,850,541,632,258,564,897,874,1400,1200,456,478,988,458,1477,45,622,2589,4100,588,4999,6587,4578,569,234,415,4522,3256,658,987,985,588,1244,120,3254,655,255,896,1247,569,4569,789,4567,567,4789,123,478,2000,1478,658,458,120,2365,458,963,2588,1456,569,1475,658,1256,3256,455,1455,655,2547,63,556,1244,325,3258,3654]]))
#Y_pred = reg.predict(X_train)
print(regr.predict([[]]))

"""

#random forest regressor
#from sklearn.ensemble import RandomForestRegressor
#reg = RandomForestRegressor()
#reg.fit(X_train, Y_train)

#Y_pred = reg.predict(X_train)

#print(Y_pred)

# predicting the prices via 

new_house=[[3,1,1520,5000,1,0,0,3,8,1000,1,2000,5000]]

new_house_std=std.transform(new_house)

new_house_std

from sklearn.ensemble import RandomForestRegressor
reg = RandomForestRegressor()
reg.fit(X_train_std,Y_train)

int(reg.predict(new_house_std))


