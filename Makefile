CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k 
MAIN = main.o
SUPER = entity.o enemy.o player.o subject.o observer.o tile.o grid.o textdisplay.o treasure.o potion.o game.o
RACES = races/human.o races/elf.o races/dwarf.o races/orc.o
ENEMIES = enemies/goblin.o enemies/dragon.o enemies/merchant.o enemies/phoenix.o enemies/troll.o enemies/vampire.o enemies/werewolf.o
TILES = tiles/doorway.o tiles/floortile.o tiles/passage.o tiles/staircase.o tiles/verticalwall.o tiles/void.o tiles/horizontalwall.o
POTIONS = potions/bapotion.o potions/bdpotion.o potions/phpotion.o potions/rhpotion.o potions/wapotion.o potions/wdpotion.o
TREASURE = treasure/barriersuit.o treasure/biggold.o treasure/dragonhoard.o treasure/merchanthoard.o treasure/smallgold.o
OBJECTS = ${MAIN} ${SUPER} ${RACES} ${ENEMIES} ${TILES} ${POTIONS} ${TREASURE}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} -g ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}