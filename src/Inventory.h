#ifndef INVENTORY_H
#define INVENTORY_H

#include "utils/config.h"
#include "NoCopy.h"
#include "Pallet.h"

/**
 * Structure for an inventory slot
 */
struct Slot {
    int quantity;
    Tile item;
    const Texture2D* texture;  // Reference, must be handled correctly during moves

    Slot() : quantity(0), item(NONE), texture(Pallet::get().getTexture(EMPTY_TEXTURE)) {}

    Slot(int quantity, Tile item, const Texture2D* texture)
        : quantity(quantity), item(item), texture(texture) {}
};

/**
 * Stores the inventory of the player
 */
class Inventory : public NoCopy {
    private:
        int selected;
        Slot slots[HOTBAR_SIZE];

    public:
        /**
         * Constructs a new inventory
         */
        Inventory() : selected(0) {
            slots[0] = Slot(
                4,
                FENCE,
                Pallet::get().getTexture(FENCE_TEXTURE)
            );

            slots[1] = Slot(
                2,
                CHEST,
                Pallet::get().getTexture(CHEST_TEXTURE)
            );
        }

        /**
         * Handles clicks
         *
         * @param position of the click
         * @returns true iff the click was on the inventory
         */
        bool clickHandler(const Vector2& position);

        /**
         * Checks for inventory changes
         */
        void update();

        /**
         * Draws the inventory / hotbar
         */
        void draw() const;

        /**
         * Deconstructs inventory instance
         */
        ~Inventory() {}
};

#endif // INVENTORY_H
