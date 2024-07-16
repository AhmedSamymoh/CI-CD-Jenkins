#include <stdio.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int grade;
} Student;

typedef struct {
    double average;
    int highest;
    int lowest;
    int passingCount;
} GradeStats;

GradeStats calculateGradeStats(Student students[], int count) {
    
    GradeStats stats;


    if (count == 0) {
        stats.average = 0.0;
        stats.highest = -1;
        stats.lowest = -1;
        stats.passingCount = 0;
        return stats;
    }

    int total = 0;
    stats.highest = students[0].grade;
    stats.lowest = students[0].grade;
    stats.passingCount = 0;

    for (int i = 0; i < count; i++) {
        total += students[i].grade;
        if (students[i].grade > stats.highest) {
            stats.highest = students[i].grade;
        }
        if (students[i].grade < stats.lowest) {
            stats.lowest = students[i].grade;
        }
        if (students[i].grade >= 50) {
            stats.passingCount++;
        }
    }

    stats.average = (double)total / count;
    return stats;
}