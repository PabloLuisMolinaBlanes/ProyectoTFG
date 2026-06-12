CWD=$(pwd)

mkdir -p $CWD/build

tail -n 1 ../../SystemSoftware/Integrated/bin/first_test.txt > $CWD/build/first_examination.txt
tail -n 1 ../../SystemSoftware/Integrated/bin/second_test_1.txt > $CWD/build/second_examination.txt && tail -n 1 ../../SystemSoftware/Integrated/bin/second_test_2.txt >> $CWD/build/second_examination.txt

if [ ! -f "$CWD/build/.env" ]; then
	echo "HOST_NAME=\"example.com\"" > $CWD/build/.env
fi

if [ ! -f "$CWD/build/hospital_credentials.txt" ]; then
	echo "EXAMPLE\nEXAMPLE"" > $CWD/build/hospital_credentials.txt
fi

npm run dev
