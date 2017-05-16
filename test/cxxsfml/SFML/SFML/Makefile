C=g++ -g -Wall -Werror --std=c++11
E=.cpp
O=main.o
P=ProjectSunshine
SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
.PHONY : clean all
all:$P
$P :$O
	$C -o $P $O $(SFML)
$E.o :
	$C -c $< -o $@ $(SFML)
clean :
	rm $O $P
