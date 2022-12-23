all:
	cd MakeFolder && cmake . && make && sudo ./main.exe && cd ..