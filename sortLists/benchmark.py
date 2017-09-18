#!/usr/bin/env python2.7

import os
import subprocess

print '| NITEMS   | SORT     | TIME     | SPACE    |'
print '| -------- | -------- | -------- | -------- |'

num = 1
while (num <= 10000000):
    proc1 = subprocess.Popen(['shuf', '-i1-{}'.format(num), '-n {}'.format(num)], stdout=subprocess.PIPE)
    proc2 = subprocess.Popen(['./measure', './lsort', '-n'], stdin=proc1.stdout, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    proc1.stdout.close()
    out, mErr = proc2.communicate()
    proc1 = subprocess.Popen(['shuf', '-i1-{}'.format(num), '-n {}'.format(num)], stdout=subprocess.PIPE)
    proc2 = subprocess.Popen(['./measure', './lsort', '-n', '-q'], stdin=proc1.stdout, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    proc1.stdout.close()
    out, qErr = proc2.communicate()
    msort = list()
    qsort = list()
    msort.append(mErr.split('\t')[0].split(' ')[0])
    msort.append(mErr.split('\t')[1].split(' ')[0])
    qsort.append(qErr.split('\t')[0].split(' ')[0])
    qsort.append(qErr.split('\t')[1].split(' ')[0])
    print '| {:<8} | Merge    | {:<8} | {:<8} |'.format(num, msort[0], msort[1])
    print '| {:<8} | Quick    | {:<8} | {:<8} |'.format(num, qsort[0], qsort[1])
    num = num * 10
