#!/usr/bin/env python2.7

import os
import subprocess

print '|{:^12}|{:^12}|{:^12}|{:^12}|'.format("NITEMS", "ALPHA", "TIME", "SPACE")
print '|------------|------------|------------|------------|'
alpha = {0.5, 0.75, 0.9, 1.0, 2.0, 4.0, 8.0, 16.0}
items = [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000]

for item in items:
    for a in alpha:
        proc1 = subprocess.Popen('shuf -i1-100000000 -n {}'.format(item), shell=True, stdout=subprocess.PIPE)
        proc2 = subprocess.Popen('./measure ./freq -l {}'.format(a), shell=True, stdin=proc1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, err = proc2.communicate()
        answer = list()
        answer.append(err.split('\t')[0].split(' ')[0])
        answer.append(err.split('\t')[1].split(' ')[0])
        print '|{:>12}|{:>12}|{:>12}|{:>12}|'.format(item, a, answer[0], answer[1])
