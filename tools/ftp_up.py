#!/usr/bin/env python3

import sys
import os
import ftplib
from termcolor import cprint

ftp_host = '192.168.178.79'
ftp_port = 5000
ftp_usr = 'bent'
ftp_pwd = 'nsmbusux'
ftp_exefs = '/atmosphere/titles/0100EA80032EA000/exefs/'
ftp_exefs_patches = '/atmosphere/exefs_patches/nsmbudx/'


def fatal(msg):
    cprint(msg, 'red')
    sys.exit(1)

def main(argc, argv):

    if argc != 4:
        fatal('Usage: %s <config file> <nso> <ips>' % argv[0])

    cfg_path = argv[1]
    nso_path = argv[2]
    ips_path = argv[3]

    # Parse cfg
    dict = { }
    try:
        f = open(cfg_path, "r")

        for line in f:
            line = line.replace('\t', ' ')
            line = line.replace('\r', '')
            line = line.replace('\n', '')
            
            try:
                idx = line.index(':')
                key = line[:idx]
                value = line[idx+1:].strip()
                dict[key] = value
            except:
                continue

    except:
        fatal('Parsing %s failed' % cfg_path)

    
    required_keys = ['host', 'port', 'host_exefs', 'host_exefs_patches']
    for k in required_keys:
        if not k in dict:
            fatal('Required key \"%s\" not present in %s' % (k, cfg_path))



    try:
        ftp_session = ftplib.FTP(timeout = 3)
        ftp_session.connect(dict['host'], int(dict['port'], 0))
    except ValueError:
        fatal('Connecting failed: Invalid port')
    except Exception as e:
        fatal('Connecting failed: %s' % str(e))

    try:
        ftp_session.login(dict.get('user', ''), dict.get('pwd', ''))
    except Exception as e:
        fatal('Login failed: %s' % str(e))

    try:
        host_exefs = dict['host_exefs']
        host_exefs_patches = dict['host_exefs_patches']

        nso_file = open(nso_path,'rb')
        ftp_session.cwd(host_exefs)
        ftp_session.storbinary('STOR %s' % os.path.basename(nso_path), nso_file)
        cprint('%s uploaded to %s' % (nso_path, host_exefs), 'green')

        ips_file = open(ips_path,'rb')
        ftp_session.cwd(host_exefs_patches)
        ftp_session.storbinary('STOR %s' % os.path.basename(ips_path), ips_file)
        cprint('%s uploaded to %s' % (ips_path, host_exefs_patches), 'green')

        ftp_session.quit()

    except Exception as e:
        cprint('Uploading files failed: %s' % str(e), 'red')
        sys.exit(1)


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
