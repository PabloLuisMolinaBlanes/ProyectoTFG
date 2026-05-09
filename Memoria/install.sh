CWD=$(pwd)
xelatex $CWD/main && biber $CWD/main && xelatex $CWD/main && xelatex $CWD/main
