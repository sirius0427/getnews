for id in `iconv -l`;do echo "$id:" && echo "\u5730\u65b9\u7ad9" |iconv -f $id -t utf-8 ;done
