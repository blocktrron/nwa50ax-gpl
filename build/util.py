import os
import logging
import yaml
import glob
import shutil
import subprocess
import shlex
import argparse
import re
import sys

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''

def run_command_with_logging(command):
    args = shlex.split(command)
    p = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    '''
    with p.stdout:
        while True:
            output = p.stdout.readline()
            if len(output) == 0 and p.poll() is not None:
                break
            if output:
                logging.info(output.decode('utf-8','ignore').strip())
    '''
    with p.stdout as outfd:
        for output in outfd:
            logging.info(output.decode('utf-8','ignore').strip())

    return p.poll()

def init_logger(logfile):
    logging.basicConfig(level=logging.DEBUG,
        format='%(asctime)s %(name)-12s %(levelname)-8s %(message)s',
        datefmt='%m-%d %H:%M',
        filename='{0}'.format(logfile),
        filemode='w')
 
    logger = logging.getLogger()
    logger.setLevel(logging.DEBUG)

    ch = logging.StreamHandler()
    ch.setLevel(logging.DEBUG)

    formatter = logging.Formatter('%(message)s')

    ch.setFormatter(formatter)
    logger.addHandler(ch)
