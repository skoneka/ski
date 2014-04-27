project(wars)
include_directories(.)
link_libraries(ncurses)
add_executable(wars main.c map.c screens.c state.c util.c stats.c player.c)
