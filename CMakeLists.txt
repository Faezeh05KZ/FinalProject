cmake_minimum_required(VERSION 3.10)
project (Game)

set (CMAKE_CXX_STANDARD 14)
add_executable (Game
 main.cc
 Archaeologist.cc
 Card.cc
 Dracula.cc
 GameManager.cc
 GameMap.cc
 GameUtils.cc 
 Hero.cc
 Invisibleman.cc
 Item.cc
 Mayor.cc
 Monster.cc
 MonsterCard.cc
 PerkCard.cc
 Player.cc
 TUI.cc
 Villager.cc)