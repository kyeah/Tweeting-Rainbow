from apscheduler.schedulers.blocking import BlockingScheduler
from random import randint
import logging
import requests
import twitter

logging.basicConfig()

# Spark
spark_endpoint = 'https://api.spark.io/v1/devices/<SPARK_CORE_ID_HERE>/setTweet'
spark_token = '<SPARK_ACCESS_TOKEN_HERE>'

# Config
sched = BlockingScheduler()
tags = ['spooky', 'halloween', 'fml', 'creepy', 'wtf', 'dressing up', 'costume']
seen = []

@sched.scheduled_job('interval', minutes=1)
def timed_job():
    api = twitter.Api(consumer_key='<TWITTER_CONSUMER_KEY_HERE>',
                      consumer_secret='<TWITTER_CONSUMER_SECRET_HERE>',
                      access_token_key='<TWITTER_ATK_HERE>',
                      access_token_secret='<TWITTER_ATS_HERE>')
    
    tag = tags[randint(0,len(tags) - 1)]
    results = api.GetSearch(term=tag,
                            count=15,
                            lang='en',
                            include_entities=True)
    
    text_results = [result for result in results 
                    if not result.media and not result.urls and result.id not in seen]

    if text_results:
        result = text_results[randint(0, len(text_results) - 1)]
        tweet = result.text

        # Send in batches to avoid hard-coded Spark API payload limit
        total = 1 + (len(tweet) / 59)
        for i in xrange(total):
            msg = ('%s %s %s' % (i+1, total, tweet[59*i:59*(i+1)]));
            print msg
            requests.post(spark_endpoint, data={'access_token': spark_token,
                                                'args':msg})

        seen.append(result.id)
        print tweet
    
sched.start()
