#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);				        \
		}							\
	} while (0)

#define MAX_STRING_SIZE 64

typedef struct dll_node_t dll_node_t;
struct dll_node_t
{
    void* data; /* Pentru ca datele stocate sa poata avea orice tip, folosim un
                   pointer la void. */
    dll_node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t
{
    dll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};  

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
	/* TODO */
	doubly_linked_list_t* list = (doubly_linked_list_t*)malloc(sizeof(doubly_linked_list_t));
    list->data_size = data_size;
    list->head = NULL;
    list->size = 0;

    return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere?
 * Atentie: n>=0 (nu trebuie tratat cazul in care n este negativ).
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	/* TODO */
    if (n >= list->data_size)
        n = list->data_size - 1;
    
    dll_node_t* it = list->head;
    for(int i = 0 ; i < n ; ++i) {
        it = it->next;
    }

    return it;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei.
 * Atentie: n>=0 (nu trebuie tratat cazul in care n este negativ).
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* new_data)
{
	/* TODO */

    dll_node_t* newnode = (dll_node_t *)malloc(sizeof(dll_node_t));
    newnode->data = malloc(list->data_size);
    memcpy(newnode->data, new_data, list->data_size);

    if (n >= list->size)
        n = list->size;

    if (list->size == 0) {
        newnode->next = newnode;
        newnode->prev = newnode;
        list->head = newnode;
        list->size ++;
        return;
    }

    dll_node_t* it = list->head;
    for(int i = 0; i < n ; ++i ) {
        it = it->next;
    }

    dll_node_t* bef = it->prev;

    bef->next = newnode;
    newnode->prev = bef;
    newnode->next = it;
    it->prev = newnode;

    if (n == 0)
        list->head = newnode;

    list->size ++;

}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Este responsabilitatea apelantului sa elibereze memoria
 * acestui nod.
 * Atentie: n>=0 (nu trebuie tratat cazul in care n este negativ).
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	/* TODO */
    if (list->size == 0) {
        return NULL;
    }

    if (n >= list->size)
        n = list->size - 1;

    dll_node_t* it = list->head;
    for(int i = 0; i < n ; ++i ) {
        it = it->next;
    }

    dll_node_t* bef = it->prev;
    dll_node_t* jump = it->next;
    dll_node_t* ret = it;

    bef->next = jump;
    jump->prev = bef;

    if (n == 0)
        list->head = jump;

    list->size --;

    return ret;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
	/* TODO */

    dll_node_t* it = list->head;
    int  i = 0;
    do {
        ++i;
        it = it->next;
    } while (it != list->head);
    return i;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
	/* TODO */
    dll_node_t* it = (*pp_list)->head;
    for(int i = 0; i < ((*pp_list)->size); ++i) {
        dll_node_t* f = it;
        it = it->next;
        free(f->data);
        free(f);
    }
    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
	/* TODO */
    dll_node_t* it = list->head;
    // printf("Size: %d | ", list->size);
    for(int i = 0; i < list->size ; ++i ) {
        printf("%d ", *((int*)it->data));

        it = it->next;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la ULTIMUL nod din
 * lista si in ordine inversa.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
	/* TODO */
    /* TODO */
    dll_node_t* it = list->head->prev;
    for(int i = 0; i < list->size ; ++i ) {
        printf("%s ", ((char*)it->data));
        it = it->prev;

    }
    printf("\n");
}
/*
 * Procedura primeste doua liste simplu inlantuite sortate si intoarce o
 * lista simplu inlantuita sortata care contine toate elementele celor doua
 * liste.
 */
doubly_linked_list_t*
merge_sorted_lists(doubly_linked_list_t* list1, doubly_linked_list_t* list2)
{
    /* TODO */
    dll_node_t* h1 = list1->head;
    dll_node_t* h2 = list2->head;
    dll_node_t* head1 = h1;
    dll_node_t* head2 = h2;

    doubly_linked_list_t* c = dll_create(sizeof(int));

    int sw1 = 1, sw2 = 1;
    int c1 = 0, c2 = 0;
    while(sw1 * sw2 != 0) {
        if (*(int*)(h1->data) < *(int*)(h2->data)) {
            dll_add_nth_node(c, c->size + 4, h1->data);
            h1 = h1->next;
            c1++;

        } else {
            dll_add_nth_node(c, c->size + 4, h2->data);
            h2 = h2->next;
            c2 ++;
        }

        if (c1 == list1->size)
            sw1 = 0;
        if (c2 == list2->size)
            sw2 = 0;
    }

    if (sw1 == 0) {
        h1 = h2;
        head1 = head2;
        c1 = c2;
        list1 = list2;
    }

    if (sw2 != 0) {
        while(c1 < list2->size) {        
            dll_add_nth_node(c, c->size + 4, h2->data);
            c1++;
            h2 = h2->next;
        }
    }

    
    
    
    return c;
}

int main()
{
    doubly_linked_list_t *list1, *list2, *mergedlist;
    long size1, size2, curr_nr;

    list1 = dll_create(sizeof(int));
    list2 = dll_create(sizeof(int));

    scanf("%ld", &size1);

    for (int i = 0; i < size1; ++i) {
        scanf("%ld", &curr_nr);
        dll_add_nth_node(list1, size1, &curr_nr);
    }

    scanf("%ld", &size2);

    for (int i = 0; i < size2; ++i) {
        scanf("%ld", &curr_nr);
        dll_add_nth_node(list2, size2, &curr_nr);
    }

    mergedlist = merge_sorted_lists(list1, list2);
    dll_print_int_list(mergedlist);

    dll_free(&mergedlist);
    dll_free(&list1);
    dll_free(&list2);

    return 0;
}