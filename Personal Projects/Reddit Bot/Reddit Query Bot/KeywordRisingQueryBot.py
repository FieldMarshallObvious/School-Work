import praw
import requests
import json
import csv
import time
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
firstRun = False


dt_string = ""

# Scheduler setup
s = sched.scheduler(time.time, time.sleep)

# setup csv
filename = "risingDataTab.csv"
header = ( "Ticker", "Num of Appearances", "upvotes", "Date", "Timestamp" )

# Functions

# Write CSV file
def writer( master, filename, newHeader ):
    with open ( filename, "a", newline="" ) as csvfile:
        temparr=[]
        index = 0
        print("First Run in method", firstRun)

        file = csv.writer(csvfile, quoting=csv.QUOTE_ALL, delimiter=',')
        if( firstRun == False ):
            file.writerow(newHeader)
            print("Write")

        for item in master:
            #print(temparr)
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
    for item in arr1:
        arrString += str(item) + ","
        arrString += str(arr2[index]) + ","
        arrString += str(arr3[index]) + ","
        arrString += str(arr4[index]) + " "
        index += 1

    index = 0
    word = ""
    for char in arrString:
        if( char != " " and char != "," ):
            word += char
        else:
            master[index] = word
            index += 1
            word = ""

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

    arrayCombiner( lOfTickers, numofTicks, upvotes, timestap, masterArray )
    writer( masterArray, "risingTab.csv", header )
    print(lOfTickers)
    print(numofTicks)
    print(upvotes)

    firstRun = True
    print("First Run: ", firstRun)


    s.enter(60, 1, mainSearch)


s.enter(0, 1, mainSearch)
s.run()
