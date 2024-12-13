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
        /**
         * Database constructor
         */
        Database() {}

        /**
         * Retrives the database object
         *
         * @returns a static database instance
         */
        static Database& get() {
            static Database instance = Database();
            return instance;
        }

        /**
         * Loads sqlite database
         *
         * @param path the path to the database
         * @returns true iff database is successfully loaded
         */
        bool load(std::string path = "resources/data.db");

        /**
         * Retrives the chunk at a given position from sqlite database
         *
         * @param x the x-coordinate of the chunk
         * @param y the y-coordinate of the chunk
         * @returns details about the chunk from database
         */
        ChunkDB getChunk(int x, int y);

        /**
         * Created a chunk at the given position in the sqlite database
         *
         * @param x the x-coordinate of the chunk
         * @param y the y-coordinate of the chunk
         * @returns the chunk's id
         */
        int createChunk(int x, int y);
        
        /**
         * Retrives a string to uniquely identify a tile
         *
         * @param tile the tile to encode
         * @returns the string identifier of the tile
         */
        std::string getIdentifierFromTile(Tile tile);

        /**
         * Retrives the tile from the string identifier
         *
         * @param identifier the string identifier of the tile
         * @returns the encoded tile
         */
        Tile getTileFromIdentifier(std::string identifier);

        /**
         * Retrives the vector of tiles for a given chunk
         *
         * @param chunk_id the chunk's id
         * @returns a vector of tile data
         */
        std::vector<TileDB> getTiles(int chunk_id);

        /**
         * Creates/updates a tile at a given position of a given chunk
         *
         * @param chunk_id the chunk's id
         * @param x the tile's x coordinate relative to the chunk
         * @param y the tile's y coordinate relative to the chunk
         * @param type the tile type
         * @returns the id of the tile
         */
        int createTile(int chunk_id, int x, int y, Tile type);

        /**
         * Retrives the vector of objects for a given chunk
         *
         * @param chunk_id the chunk's id
         * @returns a vector of object data
         */
        std::vector<ObjectDB> getObjects(int chunk_id);

        /**
         * Creates/updates an object at a given position of a given chunk
         *
         * @param chunk_id the chunk's id
         * @param x the tile's x coordinate relative to the chunk
         * @param y the tile's y coordinate relative to the chunk
         * @param type the object's type
         * @returns the id of the object
         */
        int createObject(int chunk_id, int x, int y, Tile type);

        /**
         * Deconstructor for Database
         *
         * Closes the database
         */
        ~Database() {
            if (db) {
                sqlite3_close(db);
            }
        }
};

#endif // DATABASE_H
