# here i am just implementing the random forest without the certain goal
#or you can say that not using the random forest for the house predicting price
#in order to get the basic idea of the algorithm



from csv import reader #To read csv file without using read_csv of pandas

# Load a CSV File
def load_the_csv(filename, header):
    #using the file name as i was using the random csv file for it
    # Initialize the dataset as list
    data_set = list()
    #open the data set from the file.
    with open(filename, 'r') as file:
        
        csv = reader(file)
        
        #Append each row
        for row in csv:
            if not row or not header:
                header = 1
                continue
            
            data_set.append(row)
    
    return data_set 
#converting the string coloum if present in the csv file to float
def string_col_to_float(dsetination, col):
    
    for row in dsetination:
        row[col] = float(row[col].strip())

#trying to implement the random forest from scratch and performed the basic 
#operarion that are needed for the project.