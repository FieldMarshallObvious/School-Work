import praw
import requests
import json
import csv
import time
import os.path
import sched,time
from datetime import datetime

# Get reddit bot and subreddit
reddit = praw.Reddit('bot2')

subreddit = reddit.subreddit("wallstreetbets")

# Get all stock tickers from FinHub
r = requests.get('https://finnhub.io/api/v1/stock/symbol?exchange=US&token=c06u89f48v6rt4njqhr0')
rJson = json.loads(r.text)
lOfTickers = []
numofTicks = []

# Other data
upvotes = []
timestap = []
masterArray = []
print("assigned")

dt_string = ""

# Scheduler setup
s = sched.scheduler(time.time, time.sleep)

# setup csv
filename = "risingDataTab.csv"
header = ( "Ticker", "Num of Appearances", "upvotes", "Date", "Timestamp" )

# Functions

# Write all data to CSV file
def writer( master, filename, newHeader ):
    printHeader = False

    # If the file doesn't exist then print headers
    if not os.path.isfile(filename):
            printHeader = True
    
    with open ( filename, "a+", newline="" ) as csvfile:
        temparr=[]
        index = 0

        file = csv.writer(csvfile, quoting=csv.QUOTE_ALL, delimiter=',')
        
        # If there is not file print headers
        if(printHeader == True):
            print("Printing Header")
            file.writerow(newHeader)


        # Print each item in the master array
        # to the csv file
        for item in master:
            if( index <= 3):
                temparr.append(str(item))

            else:
                temparr.append(str(item))
                file.writerow(temparr)
                index = -1
                temparr = []
            
            index += 1

    csvfile.close()

# Combines all arrays into one string
def arrayCombiner( arr1, arr2, arr3, arr4, master ):
    index = 0
    arrString = ""

    # Create a master string of all data
    for item in arr1:
        arrString += str(item) + ","
        arrString += str(arr2[index]) + ","
        arrString += str(arr3[index]) + ","
        arrString += str(arr4[index]) + " "
        index += 1

    # reset data
    index = 0
    word = ""

    # Create an array of individual items
    for char in arrString:
        if( char != " " and char != "," ):
            word += char
        else:
            master[index] = word
            index += 1
            word = ""

# Main function
def mainSearch():

    # Search through all the submissions in the rising tab
    for submission in subreddit.rising(limit=71):
        Title = str(submission.title)
        word = ""
        for char in Title:
            index = 0

            # Build words out of the submission string
            if(char != " " and char != "," and char != "." and char != "!" and char != "?"):
                word = word + char

            # If the char is not part of the word check it against tickers
            if(char == " " or char == "," or char == "." or char == "!" or char == "?" ):

                for ticker in rJson:
                    if(word == ticker["displaySymbol"]):
                        found = False

                        # Get date time
                        now = datetime.now()
                        dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

                        # Find the equivalent tickers in the array 
                        for foundTicker in lOfTickers:
                            if(foundTicker == word):     
                                numofTicks[index] += 1
                                upvotes[index] += submission.score
                                timestap[index] = dt_string
                                found = True
                                break

                        # If the ticker has not been found yet append it
                        if(found == False):
                            lOfTickers.append(word)
                            numofTicks.append(1)
                            upvotes.append(submission.score)
                            timestap.append(dt_string)
                            for i in range(5):
                                masterArray.append(0)
                            break
                        


                        index = index + 1
                # Reset word and index
                word = ""

    # Get data ready to be written
    # then write
    arrayCombiner( lOfTickers, numofTicks, upvotes, timestap, masterArray )
    writer( masterArray, "risingTab.csv", header )

    # print arrays
    print(lOfTickers)
    print(numofTicks)
    print(upvotes)


    # Repeat script every 60 seconds
    s.enter(60, 1, mainSearch)

# Start schedule
s.enter(0, 1, mainSearch)
s.run()
