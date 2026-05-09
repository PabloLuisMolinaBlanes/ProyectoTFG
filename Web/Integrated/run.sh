CWD=$(pwd)

if [ ! -f "$CWD/build/first_examination.txt" ]; then
	cat ../../SystemSoftware/Integrated/bin/first_test.txt > $CWD/build/first_examination.txt
fi

if [ ! -f "$CWD/build/second_examination.txt" ]; then
	head -n 1 ../../SystemSoftware/Integrated/bin/second_test_1.txt > $CWD/build/second_examination.txt && cat ../../SystemSoftware/Integrated/bin/second_test_2.txt >> $CWD/build/second_examination.txt
fi
npm run dev
