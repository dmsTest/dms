#!/bin/bash
mysql -hlocalhost -uroot -p123456 -P3306 -e "use dms; select * from data" > export.xls
