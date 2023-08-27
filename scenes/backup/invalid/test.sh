
RED='\033[0;31m'
NC='\033[0m'
BLUE='\033[0;34m'

clear
echo "starting tests ..............................................................."

for file in "scenes/invalid"/*; do
  if [ -f "$file" ]; then
    echo "${RED} testing $file ${NC}"
	./miniRT "$file"
	echo "${BLUE} exit status is $? ${NC}"
  fi
done
