#!/bin/bash

touch tempfile.sh
echo "#!/bin/bash" > tempfile.sh
chmod +x tempfile.sh
grep -lR "//function" src/ | sed 's/src\/\(.*\)\.c/headers\/\1\.h/g' | xargs touch
find headers/ -type f | xargs sed -i '/.*\/\/function/d'
grep -R "//function" src/ | sed 's/src\/\(.*\)\.c/headers\/\1\.h/g' | awk -F: -v q=\" '{printf "echo %s%s%s >> %s\n", q,$2,q,$1}' >> tempfile.sh
./tempfile.sh
rm tempfile.sh
find headers/ -type f | xargs sed -i 's/\(.*)\) *{/\1;/g'
