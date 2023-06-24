import matplotlib.pyplot as plt
import numpy as np
import io
from matplotlib import colors
from matplotlib.ticker import PercentFormatter
import matplotlib.pyplot as plt
 
# define filename as a constant
DATA_FILE= 'OnlySizeC.txt'
 
def readDataFromFile():  
    # create empty lists
    sizes = []
  
   # open file for reading
    with io.open(DATA_FILE, encoding='utf-8') as f:
   # with open(DATA_FILE, 'r') as f:
        f.readline()
        for line in f.readlines():
            if((line[:-1]).isdigit()):
                sizes.append(int(line[:-1]))
    return sizes

#function for countig files in specific range
def countInRange(sizes,min,max):
    count=0
    for i in sizes:
        if(i>=min and i<=max):
            count=count+1
    return count

#function to show persent of files in range
def PersentInRange(sizes,min,max):
    num = countInRange(sizes,min,max)
    print ('Number of files in range', min, ' - ',max, ' bytes: ', num)
    persent = num*100/len(sizes)
    print ('Which is ', persent ,'% of files')
#MAIN PROGRAM
sizes = readDataFromFile()

#BUILDING SCATTER
fig, ax = plt.subplots()
step = 10
n = int(20000/step)
X = [step*i for i in range(n)]
Y = [0 for i in range(n)]
for i in sizes:
    if (i<step*n):
        Y[int(i/step)] = Y[int(i/step)]+1
    
ax.scatter(X,Y, color = 'green', s=1 )
ax.set_title('Scatter view')
ax.set_xlabel('File sizes')
ax.set_ylabel('File count')
#plt.yticks(range(0,1201,100))
plt.xticks(range(0, 20001, 2000))
#plt.xticks(range(0, 50000, 10000))

# Show plot
plt.show()
