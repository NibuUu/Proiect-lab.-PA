#include <stdio.h>   // Include biblioteca standard de intrare/ieșire
#include <stdlib.h>  // Include biblioteca standard pentru alocarea memoriei și alte funcții utile

// Structura pentru a pastra informatiile despre un angajat
typedef struct {
    int totalPages;  // Totalul de pagini pe care le are un angajat
    int *books;      // Pointer către array-ul de pagini alocat angajatului
    int bookCount;   // Numarul de carti alocate angajatului
} Employee;

// Functie de comparatie pentru sortarea cartilor in ordine descrescatoare
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);  // Compararea a doua valori intregi in ordine descrescatoare
}

// Functie pentru a adauga o carte unui angajat
void addBook(Employee *employee, int pages) {
    employee->totalPages += pages;           // Adauga numarul de pagini la totalul de pagini al angajatului
    employee->books[employee->bookCount++] = pages;  // Adauga cartea in array-ul de carti si incrementeaza contorul de carti
}

// Functie pentru a gasi angajatul cu cele mai putine pagini
int findEmployeeWithLeastPages(Employee employees[], int n) {
    int minIndex = 0;  // Initial indexul minim este 0
    for (int i = 1; i < n; i++) {  // Itereaza prin toti angajatii
        if (employees[i].totalPages < employees[minIndex].totalPages) {  // Daca gasim un angajat cu mai putine pagini
            minIndex = i;  // Actualizam indexul minim
        }
    }
    return minIndex;  // Returnam indexul angajatului cu cele mai putine pagini
}

int main() {
    int numBooks, numEmployees = 3;  // Declararea numarului de carti si a numarului de angajati (3)

    // Citirea numarului de carti
    printf("Introduceti numarul de carti: ");
    scanf("%d", &numBooks);  // Citim numarul de carti de la tastatura

    // Alocarea memoriei pentru array-ul de carti
    int *books = (int *)malloc(numBooks * sizeof(int));  // Alocam memorie pentru array-ul de carti

    // Citirea paginilor cartilor
    printf("Introduceti numarul de pagini pentru fiecare carte:\n");
    for (int i = 0; i < numBooks; i++) {  // Iteram prin fiecare carte
        printf("Cartea %d: ", i + 1);
        scanf("%d", &books[i]);  // Citim numarul de pagini pentru fiecare carte
    }

    // Sortam cartile in ordine descrescatoare
    qsort(books, numBooks, sizeof(int), compare);  // Sortam array-ul de carti folosind functia qsort

    // Initializam angajatii
    Employee employees[numEmployees];  // Declararea array-ului de angajati
    for (int i = 0; i < numEmployees; i++) {  // Iteram prin fiecare angajat
        employees[i].totalPages = 0;  // Initializam totalul de pagini la 0
        employees[i].bookCount = 0;  // Initializam contorul de carti la 0
        employees[i].books = (int *)malloc(numBooks * sizeof(int));  // Alocam memorie pentru array-ul de carti al angajatului
    }

    // Distribuim cartile utilizand o abordare greedy
    for (int i = 0; i < numBooks; i++) {  // Iteram prin fiecare carte
        int minIndex = findEmployeeWithLeastPages(employees, numEmployees);  // Gasim angajatul cu cele mai putine pagini
        addBook(&employees[minIndex], books[i]);  // Adaugam cartea la angajatul respectiv
    }

    // Afisam rezultatele
    for (int i = 0; i < numEmployees; i++) {  // Iteram prin fiecare angajat
        printf("Angajatul %d are %d pagini: ", i + 1, employees[i].totalPages);  // Afisam totalul de pagini al angajatului
        for (int j = 0; j < employees[i].bookCount; j++) {  // Iteram prin fiecare carte a angajatului
            printf("%d ", employees[i].books[j]);  // Afisam numarul de pagini al fiecarei carti
        }
        printf("\n");  // Linie noua pentru urmatorul angajat
        free(employees[i].books);  // Eliberam memoria pentru array-ul de carti al angajatului
    }

    // Eliberarea memoriei pentru array-ul de carti
    free(books);  // Eliberam memoria alocata pentru array-ul de carti

    return 0;  // Terminam programul
}
