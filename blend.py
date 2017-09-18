#!/usr/bin/env python2.7

import atexit
import os
os.environ['PATH'] = '~ccl/software/external/imagemagick/bin:' + os.environ['PATH']
import re
import shutil
import sys
import tempfile

import requests

# Global variables

REVERSE     = False
DELAY       = 20
STEPSIZE    = 5

# Functions

def usage(status=0):
    print '''Usage: {} [ -r -d DELAY -s STEPSIZE ] netid1 netid2 target
    -r          Blend forward and backward
    -d DELAY    GIF delay between frames (default: {})
    -s STEPSIZE Blending percentage increment (default: {})'''.format(
        os.path.basename(sys.argv[0]), DELAY, STEPSIZE
    )
    sys.exit(status)

def remove_workspace():
    shutil.rmtree(workspace)
    print 'Cleaning up workspace: ', workspace, '\n'

def search_portrait(netid):
    req = requests.get('https://engineering.nd.edu/profiles/' + str(netid))
    if (req.text[0]):
        result = re.findall('<img src="(.*@@images.*?)"', req.text)
        print 'Searching portrait for ', netid, '... ', result[0], '\n'
        return result[0]
    else:
        print 'Invalid netid'
        sys.exit(1)   
    
def download_file(url, path):
    image = requests.get(url, stream = True)
    with open(path, 'wb') as fs:
        fs.write(image.content)
    return path

def run_command(command):
    if (os.system(command) != 0):
        sys.exit(1)

# Parse command line options

args = sys.argv[1:]

while len(args) and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-r':
        REVERSE = True
    elif arg == '-d':
        DELAY = int(args.pop(0))
    elif arg == '-s':
        STEPSIZE = int(args.pop(0))
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

# added to make sure for a valid STEPSIZE
if STEPSIZE > 100 or STEPSIZE < 0:
    print "Error, the step size must be between 0 and 100"
    usage(1)

if len(args) != 3:
    usage(1)
if len(args) == 0:
    ars.append('-')

netid1 = args[0]
netid2 = args[1]
target = args[2]

## Main execution

# Create workspace
workspace = tempfile.mkdtemp()
print 'Using workspace: ', workspace, '\n'

# Register cleanup
atexit.register(remove_workspace)

# Extract portrait URLs
url1 = search_portrait(netid1);
url2 = search_portrait(netid2);

# Download portraits
path1 = os.path.join(workspace, netid1+".jpeg")
path2 = os.path.join(workspace, netid2+".jpeg")
pic1 = download_file(url1,path1)
pic2 = download_file(url2,path2)

# Generate blended composite images
filesL = []
counter = 000
while counter < 101:
    out = os.path.join(workspace, '{:03d}-{}_{}.jpeg'.format(counter,netid1, netid2))
    run_command('composite -blend {:03d} {} {} {}'.format(counter,pic1,pic2, out))
    filesL.append(out)
    counter = counter + STEPSIZE


# Generate final animation

together = " ".join(filesL)
togetherReverse = together + " ".join(reversed(filesL))
if (REVERSE == True):
    run_command('convert -loop 0 -delay {} {} {}'.format(DELAY,togetherReverse, target))
else:
    run_command('convert -loop 0 -delay {} {} {}'.format(DELAY,together,target))
