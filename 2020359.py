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
    

