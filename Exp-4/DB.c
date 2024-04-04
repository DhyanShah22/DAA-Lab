#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CITIES 100

struct City {
    char name[100];
    int x;
    int y;
};

struct CityDatabase {
    struct City cities[MAX_CITIES];
    int count;
};

void insertRecord(struct CityDatabase *db, char name[], int x, int y);
void deleteRecordByName(struct CityDatabase *db, char name[]);
void deleteRecordByCoordinate(struct CityDatabase *db, int x, int y);
struct City* searchRecordByName(struct CityDatabase *db, char name[]);
struct City* searchRecordByCoordinate(struct CityDatabase *db, int x, int y);
void printRecordsWithinDistance(struct CityDatabase *db, int x, int y, double distance);

void insertRecord(struct CityDatabase *db, char name[], int x, int y) {
    if (db->count < MAX_CITIES) {
        strcpy(db->cities[db->count].name, name);
        db->cities[db->count].x = x;
        db->cities[db->count].y = y;
        db->count++;
    } else {
        printf("Database is full. Cannot insert more records.\n");
    }
}

void deleteRecordByName(struct CityDatabase *db, char name[]) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->cities[i].name, name) == 0) {
            for (int j = i; j < db->count - 1; j++) {
                db->cities[j] = db->cities[j + 1];
            }
            db->count--;
            break;
        }
    }
}

void deleteRecordByCoordinate(struct CityDatabase *db, int x, int y) {
    for (int i = 0; i < db->count; i++) {
        if (db->cities[i].x == x && db->cities[i].y == y) {
            for (int j = i; j < db->count - 1; j++) {
                db->cities[j] = db->cities[j + 1];
            }
            db->count--;
            break;
        }
    }
}

struct City* searchRecordByName(struct CityDatabase *db, char name[]) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->cities[i].name, name) == 0) {
            return &(db->cities[i]);
        }
    }
    return NULL;
}

struct City* searchRecordByCoordinate(struct CityDatabase *db, int x, int y) {
    double minDistance = __INT_MAX__;
    struct City *nearestCity = NULL;
    
    for (int i = 0; i < db->count; i++) {
        double dist = sqrt(pow(x - db->cities[i].x, 2) + pow(y - db->cities[i].y, 2));
        if (dist < minDistance) {
            minDistance = dist;
            nearestCity = &(db->cities[i]);
        }
    }
    return nearestCity;
}

void printRecordsWithinDistance(struct CityDatabase *db, int x, int y, double distance) {
    for (int i = 0; i < db->count; i++) {
        double dist = sqrt(pow(db->cities[i].x - x, 2) + pow(db->cities[i].y - y, 2));
        if (dist <= distance) {
            printf("City: %s, Coordinates: (%d, %d)\n", db->cities[i].name, db->cities[i].x, db->cities[i].y);
        }
    }
}

int main() {
    printf("Dhyan Shah \n22BCP269 \n");
    struct CityDatabase database;
    database.count = 0;

    insertRecord(&database, "New York", 10, 20);
    insertRecord(&database, "Los Angeles", 30, 40);

    struct City* cityByName = searchRecordByName(&database, "New York");
    if (cityByName != NULL) {
        printf("City found by name: %s, Coordinates: (%d, %d)\n", cityByName->name, cityByName->x, cityByName->y);
    } else {
        printf("City not found by name.\n");
    }

    struct City* cityByCoord = searchRecordByCoordinate(&database, 30, 40);
    if (cityByCoord != NULL) {
        printf("City found by coordinate: %s, Coordinates: (%d, %d)\n", cityByCoord->name, cityByCoord->x, cityByCoord->y);
    } else {
        printf("City not found by coordinate.\n");
    }

    deleteRecordByName(&database, "New York");

    deleteRecordByCoordinate(&database, 30, 40);
    insertRecord(&database, "New York", 10, 20);
    insertRecord(&database, "Los Angeles", 30, 40);

    printf("Records within distance of (5, 10):\n");
    printRecordsWithinDistance(&database, 5, 10, 15);

    return 0;
}
