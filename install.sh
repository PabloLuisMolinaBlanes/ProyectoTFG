#!/bin/bash
CWD=$(pwd)
CLOUD="$CWD/Cloud/Integrated"
EMBEDDED="$CWD/Embedded/Integrated/FOSSPsychotechnicalExamination_embedded"
MEMORIA="$CWD/Memoria"
SYSTEMSOFTWARE="$CWD/SystemSoftware/Integrated"
WEB="$CWD/Web/Integrated"
COMPONENTS=($CLOUD $EMBEDDED $MEMORIA $SYSTEMSOFTWARE $WEB)
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
(cd $WEB; $WEB/install.sh)
(cd $CLOUD; $CLOUD/install.sh)
(cd $EMBEDDED; $EMBEDDED/install.sh)
(cd $SYSTEMSOFTWARE; $SYSTEMSOFTWARE/install.sh)
(cd $MEMORIA; $MEMORIA/install.sh)
echo "FOSS Physical Examination has been successfully built!"
