// #include "game.h"

// Game::Game()
// {
//     screen = {600, 600};
//     genv::gout.open(screen.x(), screen.y());
//     genv::gout << genv::font("LiberationSans-Regular.ttf", 20);
//     genv::gin.timer(1000 / 64);
// }

// Game::~Game()
// {
//     //dtor
// }

// void Game::run()
// {
//     while (genv::gin >> ev && ev.keycode != genv::key_escape)
//     {
//         screen.clear();

//         if (ev.type == genv::ev_mouse && ev.button != genv::btn_wheelup && ev.button != genv::btn_wheelup)
//         {
//             cursor = {ev.pos_x, ev.pos_y};
//         }

//         bool focus = true;
//        /* for (auto &w : ws)
//         {
//             w->handle(ev, cursor, focus);
//             w->draw();
//         }*/

//         genv::gout << genv::refresh;
//     }
// }
