#include "Database.h"

#include <iostream>

void Database::executeQuery(const std::string& query) {
    std::lock_guard<std::mutex> lock(db_mutex);

    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

bool Database::load(std::string path) {
    int result = sqlite3_open(path.c_str(), &db);

    if (result != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string createChunksTable = R"(
        CREATE TABLE IF NOT EXISTS chunks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            x INTEGER NOT NULL,
            y INTEGER NOT NULL,
            UNIQUE (x, y)
        );
    )";

    std::string createTilesTable = R"(
        CREATE TABLE IF NOT EXISTS tiles (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            chunk_id INTEGER NOT NULL,
            x INTEGER NOT NULL,
            y INTEGER NOT NULL,
            type TEXT NOT NULL,
            UNIQUE (chunk_id, x, y),
            FOREIGN KEY (chunk_id) REFERENCES chunks (id) ON DELETE CASCADE
        );
    )";

    std::string createObjectssTable = R"(
        CREATE TABLE IF NOT EXISTS objects (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            chunk_id INTEGER NOT NULL,
            x INTEGER NOT NULL,
            y INTEGER NOT NULL,
            type TEXT NOT NULL,
            UNIQUE (chunk_id, x, y),
            FOREIGN KEY (chunk_id) REFERENCES chunks (id) ON DELETE CASCADE
        );
    )";

    executeQuery(createChunksTable);
    executeQuery(createTilesTable);
    executeQuery(createObjectssTable);

    return true;
}

ChunkDB Database::getChunk(int x, int y) {
    std::lock_guard<std::mutex> lock(db_mutex);

    const char* query = "SELECT id, x, y FROM chunks WHERE x = ? AND y = ?;";
    sqlite3_stmt* stmt;

    ChunkDB chunk = {
        false,
        -1,
        0,
        0
    };

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    }

    if (
        sqlite3_bind_int(stmt, 1, x) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 2, y) != SQLITE_OK
    ) {
        std::cerr << "Failed to bind parameters: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        chunk.exists = true;
        chunk.id = sqlite3_column_int(stmt, 0);
        chunk.x = sqlite3_column_int(stmt, 1);
        chunk.y = sqlite3_column_int(stmt, 2);
    } else {
        std::cerr << "Chunk not found for coordinates (" << x << ", " << y << ")" << std::endl;
    }

    sqlite3_finalize(stmt);

    return chunk;
}

int Database::createChunk(int x, int y) {
    std::lock_guard<std::mutex> lock(db_mutex);

    const char* query = "INSERT INTO chunks (x, y) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    if (
        sqlite3_bind_int(stmt, 1, x) != SQLITE_OK || 
        sqlite3_bind_int(stmt, 2, y) != SQLITE_OK
    ) {
        std::cerr << "Failed to bind parameters: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int chunkID = static_cast<int>(sqlite3_last_insert_rowid(db));
    sqlite3_finalize(stmt);

    return chunkID;
}

std::string Database::getIdentifierFromTile(Tile tile) {
    switch (tile) {
        case NONE:
        case GRASS:
            return "grass";
        case DIRT:
            return "dirt";
        case WATER:
            return "water";
        case GARDEN:
            return "garden";
        case ROAD:
            return "road";
        case FENCE:
            return "fence";
        case CHEST:
            return "chest";
        case CAMPFIRE:
            return "campfire";
        case PLAYER:
            return "player";
        case NPC_1:
            return "npc_1";
    }
}

Tile Database::getTileFromIdentifier(std::string identifier) {
    static const std::map<std::string, Tile> mapping = {
        { "grass", GRASS },
        { "dirt", DIRT },
        { "water", WATER },
        { "garden", GARDEN },
        { "road", ROAD },
        { "fence", FENCE },
        { "chest", CHEST },
        { "campfire", CAMPFIRE },
        { "player", PLAYER },
        { "npc_1", NPC_1 },
    };

    auto it = mapping.find(identifier);

    if (it != mapping.end()) {
        return it->second;
    } else {
        return GRASS;
    }
}

std::vector<TileDB> Database::getTiles(int chunk_id) {
    std::lock_guard<std::mutex> lock(db_mutex);

    const char* query = "SELECT id, chunk_id, x, y, type FROM tiles WHERE chunk_id = ?;";
    sqlite3_stmt* stmt;

    std::vector<TileDB> tiles;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return tiles;
    }

    if (sqlite3_bind_int(stmt, 1, chunk_id) != SQLITE_OK) {
        std::cerr << "Failed to bind chunk_id: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return tiles;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        TileDB tile;
        tile.id = sqlite3_column_int(stmt, 0);
        tile.chunk_id = sqlite3_column_int(stmt, 1);
        tile.x = sqlite3_column_int(stmt, 2);
        tile.y = sqlite3_column_int(stmt, 3);
        tile.type = getTileFromIdentifier(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));

        tiles.push_back(tile);
    }

    return tiles;

}

int Database::createTile(int chunk_id, int x, int y, Tile type) {
    std::lock_guard<std::mutex> lock(db_mutex);

    const char* query = "INSERT OR REPLACE INTO tiles (chunk_id, x, y, type) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    std::string identifier = getIdentifierFromTile(type);

    if (
        sqlite3_bind_int(stmt, 1, chunk_id) != SQLITE_OK || 
        sqlite3_bind_int(stmt, 2, x) != SQLITE_OK || 
        sqlite3_bind_int(stmt, 3, y) != SQLITE_OK || 
        sqlite3_bind_text(stmt, 4, identifier.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK
    ) {
        std::cerr << "Failed to bind parameters: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int tileID = static_cast<int>(sqlite3_last_insert_rowid(db));
    sqlite3_finalize(stmt);

    return tileID;
}

std::vector<ObjectDB> Database::getObjects(int chunk_id) {
    std::lock_guard<std::mutex> lock(db_mutex);

    const char* query = "SELECT id, chunk_id, x, y, type FROM objects WHERE chunk_id = ?;";
    sqlite3_stmt* stmt;

    std::vector<ObjectDB> objects;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return objects;
    }

    if (sqlite3_bind_int(stmt, 1, chunk_id) != SQLITE_OK) {
        std::cerr << "Failed to bind chunk_id: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return objects;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        ObjectDB object;

        object.id = sqlite3_column_int(stmt, 0);
        object.chunk_id = sqlite3_column_int(stmt, 1);
        object.x = sqlite3_column_int(stmt, 2);
        object.y = sqlite3_column_int(stmt, 3);
        object.type = getTileFromIdentifier(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));

        objects.push_back(object);
    }

    return objects;

}

int Database::createObject(int chunk_id, int x, int y, Tile type) {
    std::lock_guard<std::mutex> lock(db_mutex);

    const char* query = "INSERT OR REPLACE INTO objects (chunk_id, x, y, type) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    std::string identifier = getIdentifierFromTile(type);

    if (
        sqlite3_bind_int(stmt, 1, chunk_id) != SQLITE_OK || 
        sqlite3_bind_int(stmt, 2, x) != SQLITE_OK || 
        sqlite3_bind_int(stmt, 3, y) != SQLITE_OK || 
        sqlite3_bind_text(stmt, 4, identifier.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK
    ) {
        std::cerr << "Failed to bind parameters: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int objectID = static_cast<int>(sqlite3_last_insert_rowid(db));
    sqlite3_finalize(stmt);

    return objectID;
}
