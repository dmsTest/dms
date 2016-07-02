#!/bin/bash
cp wtmpx.bak wtmpx
rm -rf *wtmpx.2016*
cat /dev/null > logins.dat
