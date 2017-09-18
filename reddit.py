#!/usr/bin/env python2.7

import re
import requests
import json
import os
import sys

# global set at default values

FIELD = 'title'
LIMIT = 10
SUBREDDIT = 'linux'
REGEX = ' ' 

# functions

def usage(status=0):
    print '''USage: reddit.py [ -f FIELD -s SUBREDDIT ] regex
    
    -f FIELD        Which field to search (default: title)
    -n LIMIT        Limit number of articles to report (default: 10)
    -s SUBREDDIT    Which subreddit to search (default: linux)'''
    sys.exit(status)

# command line

args = sys.argv[1:]
while len(args) and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-f':
        FIELD = args.pop(0)
    elif arg == '-n':
        LIMIT = int(args.pop(0))
        if (LIMIT <= 0):
            print 'Invalid number'
    elif arg == '-s':
        SUBREDDIT = args.pop(0)
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

if len(args) != 1:
    REGEX = '.*' # search for everything
else:
    REGEX = args[0]

# stop the 429 too many request error

headers = {'user-agent': 'reddit-{}'.format(os.environ['USER'])}
response = requests.get('https://www.reddit.com/r/linux/.json', headers=headers)

# getting json from page

link = 'https://www.reddit.com/r/{}/.json'.format(SUBREDDIT)
req = requests.get(link, headers=headers)
json = req.json()

# finding matches

data = []
for check in json['data']['children']:
    test = check['data']
    if FIELD in test:
        if re.search(REGEX, test[FIELD]):
            art = {} # dict for the article
            art['Title'] = test['title']
            art['Author'] = test['author']
            art['Link'] = test['url']
            data.append(art)
    else:
        print 'Invalid Field: ', FIELD
        break

# limit the amount of articles
artNum = LIMIT
for counter, art in enumerate(data):
    print '{}\tTitle:'.format(counter+1), art['Title']
    print '\t', 'Author:', art['Author']
    print '\t', 'Link:', art['Link'], '\n'
    artNum = artNum -1
    if artNum == 0:
        break
