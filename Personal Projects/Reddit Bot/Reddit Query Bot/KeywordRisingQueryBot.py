import praw
import requests
import json
import csv
import time

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

# setup csv
filename = "risingDataTab.csv"
header = ( "Ticker", "Num of Appearances", "upvotes", "Timestamp" )

# Functions

# Write CSV file
def writer( master, filename, newHeader ):
    with open ( filename, "w" ) as csvfile:
        temparr=[]
        word=""
        index = 0

        file = csv.writer(csvfile, quoting=csv.QUOTE_ALL)
        file.writerow(newHeader)

        for item in master:
            print(item)
            if( index <= 3 ):
                temparr += item
            else:
                file.writerow(item)
                print(temparr)
                index = 0
                word = ""
            
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

    print(arrString)

    index = 0
    word = ""
    for char in arrString:
        if( char != " " and char != "," ):
            word += char
        else:
            master[index] = word
            index += 1
            word = ""


    print(master)


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
                    print("FOUND")
                    # Find the equivalent tickers in the array 
                    for foundTicker in lOfTickers:
                        if(foundTicker == word):     
                            numofTicks[index] += 1
                            upvotes[index] += submission.score
                            found = True
                            break

                    # If the ticker has not been found yet append it
                    if(found == False):
                        lOfTickers.append(word)
                        numofTicks.append(1)
                        upvotes.append(submission.score)
                        for i in range(4):
                            masterArray.append(0)
                        break

                    index = index + 1
            # Reset word and index
            word = ""
time = upvotes
arrayCombiner( lOfTickers, numofTicks, upvotes, time, masterArray )
writer( masterArray, "risingTab.csv", header )
print(lOfTickers)
print(numofTicks)
print(upvotes)