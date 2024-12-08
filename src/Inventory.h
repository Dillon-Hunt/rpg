#ifndef INVENTORY_H
#define INVENTORY_H

#include "utils/config.h"
#include "NoCopy.h"
#include "Pallet.h"

struct Slot {
    int quantity;
    Tile item;
    const Texture2D* texture;  // Reference, must be handled correctly during moves

    Slot() : quantity(0), item(NONE), texture(Pallet::get().getTexture(EMPTY_TEXTURE)) {}

    Slot(int quantity, Tile item, const Texture2D* texture)
        : quantity(quantity), item(item), texture(texture) {}
};

class Inventory : public NoCopy {
    private:
        int selected;
        Slot slots[HOTBAR_SIZE];

    public:
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

        bool clickHandler(const Vector2& position);

        void update();

        void draw() const;

        ~Inventory() {}
};

#endif // INVENTORY_H
