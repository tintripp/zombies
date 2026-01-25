#include "game.h"

int main(void) {
    Game g = {0};
    game_init(&g);
    game_loop(&g);

    return 0;
}
