#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#define SIZE 20

typedef struct {
    int x, y;
    char dir; // '>', '<', '^', 'v'
} Guard;

char map[SIZE][SIZE + 1] = {
    "####################",
    "#O.....#...........#",
    "#......#..##.......#",
    "#..####.......#####",
    "#......#...........#",
    "#..>...#....#......#",
    "#......#....#......#",
    "#......#....#......#",
    "#..####....######..#",
    "#......#...........#",
    "#......#...........#",
    "#......#...........#",
    "#......#...........#",
    "#......#...........#",
    "#......#...........#",
    "#......#...........#",
    "#....v.#...........#",
    "#......#...........#",
    "#..............E...#",
    "####################"
};

Guard guards[] = {
    {5, 5, '>'},
    {5, 16, 'v'},
    {13, 2, '^'}
};
int guardCount = sizeof(guards) / sizeof(guards[0]);

int playerX = 1, playerY = 1;

void printMap();
bool isGuardSymbol(char c);
bool checkGuardsSeePlayer();
void placeGuardsOnMap();

int main() {
    placeGuardsOnMap();
    char move;

    while (1) {
        system("cls");
        printMap();

        if (checkGuardsSeePlayer()) {
            printf("\n💀 Gardiyan seni gördü! Oyun bitti!\n");
            break;
        }

        if (map[playerY][playerX] == 'E') {
            printf("\n🎉 Tebrikler! Kaçmayı başardın!\n");
            break;
        }

        printf("\nWASD ile hareket et (Q = çıkış): ");
        move = getch();

        if (move == 'q' || move == 'Q') {
            printf("\nOyundan çıktın.\n");
            break;
        }

        int newX = playerX, newY = playerY;
        if (move == 'w' || move == 'W') newY--;
        else if (move == 's' || move == 'S') newY++;
        else if (move == 'a' || move == 'A') newX--;
        else if (move == 'd' || move == 'D') newX++;

        if (map[newY][newX] == '#') continue; // duvar varsa geç

        // gardiyanın üstüne yürüme kontrolü
        if (isGuardSymbol(map[newY][newX])) {
            printf("\n💀 Gardiyanın üstüne yürüdün, yakalandın!\n");
            break;
        }

        // çıkış kontrolü
        if (map[newY][newX] == 'E') {
            printf("\n🎉 Çıkışa ulaştın — başarıyla kaçtın!\n");
            break;
        }

        // hareket
        if (map[playerY][playerX] != 'E') map[playerY][playerX] = '.';
        playerX = newX;
        playerY = newY;
        map[playerY][playerX] = 'O';
    }

    return 0;
}

void printMap() {
    for (int i = 0; i < SIZE; i++) printf("%s\n", map[i]);
}

void placeGuardsOnMap() {
    for (int i = 0; i < guardCount; i++) {
        map[guards[i].y][guards[i].x] = guards[i].dir;
    }
    map[playerY][playerX] = 'O';
}

bool isGuardSymbol(char c) {
    return (c == '>' || c == '<' || c == '^' || c == 'v');
}

// gardiyan oyuncuyu görüyor mu (duvar yoksa düz hat)
bool checkGuardsSeePlayer() {
    for (int i = 0; i < guardCount; i++) {
        Guard g = guards[i];
        int x = g.x, y = g.y;

        if (g.dir == '>') {
            for (int j = x + 1; j < SIZE; j++) {
                if (map[y][j] == '#') break;
                if (playerX == j && playerY == y) return true;
            }
        } else if (g.dir == '<') {
            for (int j = x - 1; j >= 0; j--) {
                if (map[y][j] == '#') break;
                if (playerX == j && playerY == y) return true;
            }
        } else if (g.dir == '^') {
            for (int i2 = y - 1; i2 >= 0; i2--) {
                if (map[i2][x] == '#') break;
                if (playerX == x && playerY == i2) return true;
            }
        } else if (g.dir == 'v') {
            for (int i2 = y + 1; i2 < SIZE; i2++) {
                if (map[i2][x] == '#') break;
                if (playerX == x && playerY == i2) return true;
            }
        }
    }
    return false;
}