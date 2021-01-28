import praw
import requests
import json
from nltk.corpus import words

# Get reddit bot and subreddit
reddit = praw.Reddit('bot2')

subreddit = reddit.subreddit("wallstreetbets")

# Get all stock tickers from FinHub
r = requests.get('https://finnhub.io/api/v1/stock/symbol?exchange=US&token=c06u89f48v6rt4njqhr0')
rJson = json.loads(r.text)
lOfTickers = []
numofTicks = []

# Get a list of all english words
word_list = words.words()


# Search through all the submissions in the rising tab
for submission in subreddit.rising(limit=24):
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
                    # Make sure word is not an english word
                    length = len(words)
                    for wordItem in length:
                        EngWord = words[wordItem]
                        if( EngWord == word ):
                            continue
                        else:
                            found = False
                            print("FOUND")
                            # Find the equivalent tickers in the array 
                            for foundTicker in lOfTickers:
                                index = index + 1
                                if(foundTicker == word):   
                                    numofTicks[index] += 1
                                    print(numofTicks[index])
                                    found = True

                                # If the ticker has not been found yet append it
                                if(found == False):
                                    lOfTickers.append(word)
                                    numofTicks.append(1)
                                    print(lOfTickers)

            # Reset word
            word = ""