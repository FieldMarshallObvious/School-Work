import praw
from get_all_tickers import get_tickers as gt

# Get reddit bot and subreddit
reddit = praw.Reddit('bot2')

subreddit = reddit.subreddit("wallstreetbets")

# Get all stock tickers from Yahoo Finance
lOfTickers = gt.get_tickers()
numofTicks = []

for submission in subreddit.rising(limit=24):
    Title = str(submission.title)
    word = ""
    for char in Title:
        index = 0
        if(char != " " and char != "," and char != "." and char != "!" and char != "?"):
            word = word + char
            print(word)
        if(char == " " or char == "," or char == "." or char == "!" or char == "?" ):
            print("CHECKING WORD")
            for ticker in lOfTickers:
                index = index + 1
                if(word == lOfTickers):
                    print(word)
                    if(numofTicks[index] == None):
                        numofTicks.append(1)
                    else:
                        numofTicks[index] = numofTicks[index] + 1

            word = ""