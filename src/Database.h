#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

#include "Pallet.h"

#include <string>
#include <vector>
#include <mutex>

struct ChunkDB {
    bool exists;
    int id;
    int x;
    int y;
};

struct TileDB {
    int id;
    int chunk_id;
    int x;
    int y;
    Tile type;
};

struct ObjectDB {
    int id;
    int chunk_id;
    int x;
    int y;
    Tile type;
};

class Database {
    private:
        sqlite3* db;
        std::mutex db_mutex;

        void executeQuery(const std::string& query);

    public:
        Database() {}

        static Database& get() {
            static Database instance = Database();
            return instance;
        }

        bool load(std::string path = "resources/data.db");

        ChunkDB getChunk(int x, int y);

        int createChunk(int x, int y);
        
        std::string getIdentifierFromTile(Tile tile);

        Tile getTileFromIdentifier(std::string identifier);

        std::vector<TileDB> getTiles(int chunk_id);

        int createTile(int chunk_id, int x, int y, Tile type);

        std::vector<ObjectDB> getObjects(int chunk_id);

        int createObject(int chunk_id, int x, int y, Tile type);

        ~Database() {
            if (db) {
                sqlite3_close(db);
            }
        }
};

#endif // DATABASE_H
