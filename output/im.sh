#!/bin/bash
clear
echo "Import started ..."
echo "First, old database will be removed."
mongo lp --eval "db.dropDatabase()"
echo "Second, fresh data populates in the new database."
mongoimport --db lp --collection finance  --drop --file finance.json
mongoimport --db lp --collection health   --drop --file health.json
mongoimport --db lp --collection phone    --drop --file phone.json
mongoimport --db lp --collection social   --drop --file social.json
echo "Finished."
