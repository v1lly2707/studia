#?/bin/bash
grep "OK DOWNLOAD" cdlinux.ftp.log | cut -d'"' -f 2,4 |
sort -u | sed "1,\$s#.*/##" | grep "\.iso" | sort | uniq -c