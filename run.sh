#!/bin/bash
CWD=$(pwd)
EMBEDDED="$CWD/Embedded/Integrated/FOSSPsychotechnicalExamination_embedded"
SYSTEMSOFTWARE="$CWD/SystemSoftware/Integrated"
WEB="$CWD/Web/Integrated"
for list in "${array[@]}"
do
    for item in $list
    do
	if [ ! -d $item ]; then
  		echo "folder $item does not exist. Error, cannot build."
  		exit
	fi
    done
done
(cd $EMBEDDED; $EMBEDDED/run.sh)
(cd $SYSTEMSOFTWARE; $SYSTEMSOFTWARE/run.sh)
(cd $WEB; $WEB/run.sh)