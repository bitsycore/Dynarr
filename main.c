#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dynarr/dynarr.h"
#include "dynarr/chainarr.h"
#include "dynarr/blockarr.h"

typedef struct {
    int level;
    int experience;
    bool isAlive;
    bool isGodMode;
} Player;

void printPlayer(const Player player) {
    printf("Player: level=%d, experience=%d, isAlive=%d, isGodMode=%d\n",
           player.level, player.experience, player.isAlive, player.isGodMode);
}

DYNARR_DEFINE_NAME(Player, PlayerDynArray)
BLOCKARR_DEFINE_NAME(Player, PlayerBlockArray)
CHAINARR_DEFINE_NAME(Player, PlayerChainArray)

DYNARR_DEFINE(int)
CHAINARR_DEFINE(int)
BLOCKARR_DEFINE(int)

int main() {
    srand(time(NULL));

    // Create and populate the first dynamic array
    printf("Creating and populating the first dynamic array:\n");
    const PTR_PlayerDynArray dynArray1 = new_PlayerDynArray(10);
    for (int i = 0; i < 15; ++i) {
        const Player player = { i, rand() % 1000, rand() % 2, rand() % 2 };
        append_PlayerDynArray(dynArray1, player);
    }

    // Print the contents of the first array
    for (size_t i = 0; i < size_PlayerDynArray(dynArray1); ++i) {
        printPlayer(get_PlayerDynArray(dynArray1, i));
    }

    // Create and populate the second dynamic array
    printf("\nCreating and populating the second dynamic array:\n");
    const PTR_PlayerDynArray dynArray2 = new_PlayerDynArray(5);
    for (int i = 15; i < 20; ++i) {
        const Player player = { i, rand() % 1000, rand() % 2, rand() % 2 };
        append_PlayerDynArray(dynArray2, player);
    }

    // Print the contents of the second array
    for (size_t i = 0; i < size_PlayerDynArray(dynArray2); ++i) {
        printPlayer(get_PlayerDynArray(dynArray2, i));
    }

    // Concatenate the two arrays
    printf("\nConcatenating the two arrays:\n");
    concat_PlayerDynArray(dynArray1, dynArray2);
    for (size_t i = 0; i < size_PlayerDynArray(dynArray1); ++i) {
        printPlayer(get_PlayerDynArray(dynArray1, i));
    }

    // Resize the array
    printf("\nResizing the array to 25 elements:\n");
    resize_PlayerDynArray(dynArray1, 25);
    printf("New capacity: %zu\n", capacity_PlayerDynArray(dynArray1));

    // Insert a new player at index 10
    printf("\nInserting a new player at index 10:\n");
    const Player newPlayer = { 100, 9999, 1, 1 };
    insert_PlayerDynArray(dynArray1, 10, newPlayer);
    printPlayer(get_PlayerDynArray(dynArray1, 10));

    // Remove the player at index 5
    printf("\nRemoving the player at index 5:\n");
    remove_PlayerDynArray(dynArray1, 5);
    printf("New size: %zu\n", size_PlayerDynArray(dynArray1));

    // Find a player with level 100
    printf("\nFinding the player with level 100:\n");
    const Player searchPlayer = { 100, 0, 0, 0 }; // We only care about the level for this search
    insert_PlayerDynArray(dynArray1, 10, searchPlayer);
    const int foundIndex = find_PlayerDynArray(dynArray1, searchPlayer);
    if (foundIndex != -1) {
        printf("Found at index: %d\n", foundIndex);
        printPlayer(get_PlayerDynArray(dynArray1, foundIndex));
    } else {
        printf("Player not found.\n");
    }

    // Clean up
    delete_PlayerDynArray(dynArray1);
    delete_PlayerDynArray(dynArray2);

    // Test PlayerDynArray
    const PTR_PlayerDynArray dynArray = new_PlayerDynArray(10);
    for (int i = 0; i < 20; ++i) {
        const Player player = { i, rand(), rand()%2, rand()%2 };
        append_PlayerDynArray(dynArray, player);
    }
    for (size_t i = 0; i < size_PlayerDynArray(dynArray); ++i) {
        const Player player = get_PlayerDynArray(dynArray, i);
        printf("PlayerDynArray: level=%d, experience=%d, isAlive=%d, isGodMod=%d\n", player.level, player.experience, player.isAlive, player.isGodMode);
    }
    delete_PlayerDynArray(dynArray);

    // Test PlayerBlockArray"
    PlayerBlockArray* blockArray = new_PlayerBlockArray(10);
    for (int i = 0; i < 20; ++i) {
        const Player player = { i, rand(), rand()%2, rand()%2 };
        append_PlayerBlockArray(blockArray, player);
    }
    for (size_t i = 0; i < size_PlayerBlockArray(blockArray); ++i) {
        const Player player = get_PlayerBlockArray(blockArray, i);
        printf("PlayerBlockArray: level=%d, experience=%d, isAlive=%d, isGodMod=%d\n", player.level, player.experience, player.isAlive, player.isGodMode);
    }
    delete_PlayerBlockArray(blockArray);

    // Test PlayerChainArray
    PlayerChainArray* chainArray = new_PlayerChainArray();
    for (int i = 0; i < 20; ++i) {
        const Player player = { i, rand(), rand()%2, rand()%2 };
        append_PlayerChainArray(chainArray, player);
    }
    for (size_t i = 0; i < size_PlayerChainArray(chainArray); ++i) {
        const Player player = get_PlayerChainArray(chainArray, i);
        printf("PlayerChainArray: level=%d, experience=%d, isAlive=%d, isGodMod=%d\n", player.level, player.experience, player.isAlive, player.isGodMode);
    }
    delete_PlayerChainArray(chainArray);

    // Test int arrays
    dynarr_int* dynarr_int = new_dynarr_int(10);
    for (int i = 0; i < 20; ++i) {
        append_dynarr_int(dynarr_int, i);
    }
    for (size_t i = 0; i < size_dynarr_int(dynarr_int); ++i) {
        const int value = get_dynarr_int(dynarr_int, i);
        printf("dynarr_int: %d\n", value);
    }
    delete_dynarr_int(dynarr_int);

    blockarr_int* blockarr_int = new_blockarr_int(10);
    for (int i = 0; i < 20; ++i) {
        append_blockarr_int(blockarr_int, i);
    }
    for (size_t i = 0; i < size_blockarr_int(blockarr_int); ++i) {
        const int value = get_blockarr_int(blockarr_int, i);
        printf("blockarr_int: %d\n", value);
    }
    clear_blockarr_int(blockarr_int);
    delete_blockarr_int(blockarr_int);

    chainarr_int* chainarr_int = new_chainarr_int();
    for (int i = 0; i < 20; ++i) {
        append_chainarr_int(chainarr_int, i);
    }
    for (size_t i = 0; i < size_chainarr_int(chainarr_int); ++i) {
        const int value = get_chainarr_int(chainarr_int, i);
        printf("chainarr_int: %d\n", value);
    }
    free_chainarr_int(chainarr_int);
    delete_chainarr_int(chainarr_int);

    return 0;
}