#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct City {
    char name[100];
    int x;
    int y;
    struct City* next;
};

struct CityDatabase {
    struct City* head;
};

// Function prototypes
void initializeDatabase(struct CityDatabase *db);
void insertRecord(struct CityDatabase *db, char name[], int x, int y);
void deleteRecordByName(struct CityDatabase *db, char name[]);
void deleteRecordByCoordinate(struct CityDatabase *db, int x, int y);
struct City* searchRecordByName(struct CityDatabase *db, char name[]);
struct City* searchRecordByCoordinate(struct CityDatabase *db, int x, int y);
void printRecordsWithinDistance(struct CityDatabase *db, int x, int y, double distance);
void freeDatabase(struct CityDatabase *db);

int main() {
    printf("Anusi Patel \n22BCP250 \n");
    struct CityDatabase database;
    initializeDatabase(&database);

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
    insertRecord(&database, "Chicago", 35, 60);
    insertRecord(&database, "Houston", 70, 10);
    insertRecord(&database, "Phoenix", 30, 20);

    // Printing records within a given distance of a specified point
    printf("\nRecords within distance of (10, 10):\n");
    printRecordsWithinDistance(&database, 10, 10, 30);

    // Free memory
    freeDatabase(&database);

    return 0;
}

// Function to initialize the database
void initializeDatabase(struct CityDatabase *db) {
    db->head = NULL;
}

// Function to insert a record
void insertRecord(struct CityDatabase *db, char name[], int x, int y) {
    struct City* newCity = (struct City*)malloc(sizeof(struct City));
    if (newCity == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(newCity->name, name);
    newCity->x = x;
    newCity->y = y;
    newCity->next = db->head;
    db->head = newCity;
}

// Function to delete a record by name
void deleteRecordByName(struct CityDatabase *db, char name[]) {
    struct City* current = db->head;
    struct City* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                db->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to delete a record by coordinate
void deleteRecordByCoordinate(struct CityDatabase *db, int x, int y) {
    struct City* current = db->head;
    struct City* prev = NULL;

    while (current != NULL) {
        if (current->x == x && current->y == y) {
            if (prev == NULL) {
                db->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to search a record by name
struct City* searchRecordByName(struct CityDatabase *db, char name[]) {
    struct City* current = db->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to search a record by coordinate using distance formula
struct City* searchRecordByCoordinate(struct CityDatabase *db, int x, int y) {
    struct City* current = db->head;
    double minDistance = __INT_MAX__;
    struct City* nearestCity = NULL;

    while (current != NULL) {
        double dist = sqrt(pow(x - current->x, 2) + pow(y - current->y, 2));
        if (dist < minDistance) {
            minDistance = dist;
            nearestCity = current;
        }
        current = current->next;
    }
    return nearestCity;
}

// Function to print all records within a given distance of a specified point
void printRecordsWithinDistance(struct CityDatabase *db, int x, int y, double distance) {
    struct City* current = db->head;
    while (current != NULL) {
        double dist = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
        if (dist <= distance) {
            printf("City: %s, Coordinates: (%d, %d)\n", current->name, current->x, current->y);
        }
        current = current->next;
    }
}

// Function to free memory allocated for the database
void freeDatabase(struct CityDatabase *db) {
    struct City* current = db->head;
    struct City* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    db->head = NULL;
}
