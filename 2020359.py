#import Libraries 

import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt 
import seaborn as sns 
from scipy import stats 
import warnings 

#Loading the train and test dataseys and importing in a dataframe 
train = pd. read_csv('train (1).csv') 
test = pd.read_csv('test.csv') 
print('Datasets read successfully..')


# Missing Value Handling

def HandlingMissingValue(df):
   
    #for Object columns fill using 'None'
    #for Numerical columns fill using median
    
    num_cols = [cname for cname in df.columns if df[cname].dtype in ['int64', 'float64']]
    cat_cols = [cname for cname in df.columns if df[cname].dtype == 'object']
    values = {}
    
    for a in cat_cols:
        values[a] = 'None'
        
    for a in num_cols:
        values[a] = df[a].median()
        
    df.fillna(value = values , inplace = True)
    

