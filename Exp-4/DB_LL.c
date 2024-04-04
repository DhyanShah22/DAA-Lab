#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

struct City {
    char name[100];
    int x;
    int y;
    struct City* next;
};

struct CityDatabase {
    struct City* head;
};

void initializeDatabase(struct CityDatabase *db);
void insertRecord(struct CityDatabase *db, char name[], int x, int y);
void deleteRecordByName(struct CityDatabase *db, char name[]);
void deleteRecordByCoordinate(struct CityDatabase *db, int x, int y);
struct City* searchRecordByName(struct CityDatabase *db, char name[]);
struct City* searchRecordByCoordinate(struct CityDatabase *db, int x, int y);
void printRecordsWithinDistance(struct CityDatabase *db, int x, int y, double distance);
void freeDatabase(struct CityDatabase *db);

int main() {
    printf("Dhyan Shah \n22BCP269 \n");
    struct CityDatabase database;
    initializeDatabase(&database);

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
    insertRecord(&database, "Chicago", 35, 60);
    insertRecord(&database, "Houston", 70, 10);
    insertRecord(&database, "Phoenix", 30, 20);

    printf("\nRecords within distance of (10, 10):\n");
    printRecordsWithinDistance(&database, 10, 10, 30);

    freeDatabase(&database);

    return 0;
}

void initializeDatabase(struct CityDatabase *db) {
    db->head = NULL;
}

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

struct City* searchRecordByCoordinate(struct CityDatabase *db, int x, int y) {
    struct City* current = db->head;
    double minDistance = INT_MAX; 
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
