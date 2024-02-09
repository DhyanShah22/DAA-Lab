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

// Function prototypes
void insertRecord(struct CityDatabase *db, char name[], int x, int y);
void deleteRecordByName(struct CityDatabase *db, char name[]);
void deleteRecordByCoordinate(struct CityDatabase *db, int x, int y);
struct City* searchRecordByName(struct CityDatabase *db, char name[]);
struct City* searchRecordByCoordinate(struct CityDatabase *db, int x, int y);
void printRecordsWithinDistance(struct CityDatabase *db, int x, int y, double distance);

// Function to insert a record
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

// Function to delete a record by name
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

// Function to delete a record by coordinate
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

// Function to search a record by name
struct City* searchRecordByName(struct CityDatabase *db, char name[]) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->cities[i].name, name) == 0) {
            return &(db->cities[i]);
        }
    }
    return NULL;
}

// Function to search a record by coordinate using distance formula
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

// Function to print all records within a given distance of a specified point
void printRecordsWithinDistance(struct CityDatabase *db, int x, int y, double distance) {
    for (int i = 0; i < db->count; i++) {
        double dist = sqrt(pow(db->cities[i].x - x, 2) + pow(db->cities[i].y - y, 2));
        if (dist <= distance) {
            printf("City: %s, Coordinates: (%d, %d)\n", db->cities[i].name, db->cities[i].x, db->cities[i].y);
        }
    }
}

int main() {
    printf("Anusi Patel \n22BCP250 \n");
    struct CityDatabase database;
    database.count = 0;

    // Inserting records
    insertRecord(&database, "New York", 10, 20);
    insertRecord(&database, "Los Angeles", 30, 40);

    // Searching a record by name
    struct City* cityByName = searchRecordByName(&database, "New York");
    if (cityByName != NULL) {
        printf("City found by name: %s, Coordinates: (%d, %d)\n", cityByName->name, cityByName->x, cityByName->y);
    } else {
        printf("City not found by name.\n");
    }

    // Searching a record by coordinate
    struct City* cityByCoord = searchRecordByCoordinate(&database, 30, 40);
    if (cityByCoord != NULL) {
        printf("City found by coordinate: %s, Coordinates: (%d, %d)\n", cityByCoord->name, cityByCoord->x, cityByCoord->y);
    } else {
        printf("City not found by coordinate.\n");
    }

    // Deleting a record by name
    deleteRecordByName(&database, "New York");

    // Deleting a record by coordinate
    deleteRecordByCoordinate(&database, 30, 40);
    insertRecord(&database, "New York", 10, 20);
    insertRecord(&database, "Los Angeles", 30, 40);

    // Printing records within a given distance of a specified point
    printf("Records within distance of (5, 10):\n");
    printRecordsWithinDistance(&database, 5, 10, 15);

    return 0;
}
