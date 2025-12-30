/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "itest.h"
#include "itest_log.h"

/*
-------------double list test-----------------
*/
struct list_head {
    struct list_head *next, *prev;
};

#define offsetof(TYPE, MEMBER)  ((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({              \
    void *__mptr = (void *)(ptr);                   \
    ((type *)(__mptr - offsetof(type, member))); })


#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

#define list_next_entry(pos, member) \
    list_entry((pos)->member.next, typeof(*(pos)), member)

/**
* list_for_each_entry   -   iterate over list of given type
* @pos: the type * to use as a loop cursor.
* @head:    the head for your list.
* @member:  the name of the list_head within the struct.
*/
#define list_for_each_entry(pos, head, member)              \
    for (pos = list_first_entry(head, typeof(*pos), member);    \
         &pos->member != (head);                    \
         pos = list_next_entry(pos, member))


#define list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)


/*
-------OK-------
/ # chmod 777 sample_future
/ # ./sample_future  AX_SMAPLE_LIST_001
begin to test 'AX_SMAPLE_LIST_001'
found  testcase 'AX_SMAPLE_LIST_001'
number = 3
number = 2
-----------ret is 'Pass' cost time = 0 ms (0 s)
*/
typedef struct _foo {
    int data;
    struct list_head link;
} foo_T;



static void ITEST_USER_LIB_LIST_001(void)
{
    //foo_T main_list;
    //main_list.data = 1;


    LIST_HEAD(foo_head);
    //INIT_LIST_HEAD(& (foo_head));

    foo_T f1;
    f1.data = 2;
    //INIT_LIST_HEAD(& f1.link);
    list_add(&(f1.link), &(foo_head));

    foo_T f2;
    f2.data = 3;
    //INIT_LIST_HEAD(& f2.link);
    list_add(&(f2.link), &(foo_head));

    foo_T *pos;

    list_for_each_entry(pos, &(foo_head), link) {
        printf("number = %d \n", pos->data);
    }

    uassert_true(1);

    return;
}

ITEST_TC_EXPORT(ITEST_USER_LIB_LIST_001, "ITEST_USER_LIB_LIST_001", RT_NULL, RT_NULL, 10, ITEST_TC_EXCE_AUTO);


/*
-------OK-------

typedef struct _foo{
    int data;
    struct list_head link;
}foo_T;


int AX_SMAPLE_LIST_001(char **failReason)
{
    int ret=0;
    foo_T main_list;
    main_list.data = 1;
    INIT_LIST_HEAD(& (main_list.link));

    foo_T f1;
    f1.data = 2;
    //INIT_LIST_HEAD(& f1.link);
    list_add(&(f1.link), &(main_list.link));

    foo_T f2;
    f2.data = 3;
    //INIT_LIST_HEAD(& f2.link);
    list_add(&(f2.link), &(main_list.link));

    foo_T *pos;

    list_for_each_entry(pos, &(main_list.link), link) {
        printf("number = %d \n", pos->data);
    }

    return ret;
}
*/

/*
-------OK-------
struct person
{
    int age;
    char name[20];
    struct list_head list;
};

int AX_SMAPLE_LIST_001(char **failReason)
{
    int ret=0;

    struct person *boy;
    struct person person_head;
    struct person *pperson;

    int i;
    // 初始化双链表的表头
    INIT_LIST_HEAD(&person_head.list);
    // 添加节点
    for (i=0; i<5; i++)
    {
        pperson = (struct person*)malloc(sizeof(struct person));
        pperson->age = (i+1)*20;
        sprintf(pperson->name, "%d", i+1);
        // 将节点链接到链表的末尾
        // 如果想把节点链接到链表的表头后面，则使用 list_add
        //list_add_tail(&(pperson->list), &(person_head.list));
        list_add(&(pperson->list), &(person_head.list));
    }

    // 遍历链表
    printf("==== 2st iterator d-link ====\n");
    list_for_each_entry(boy, &(person_head.list), list ){
        printf("------name:%-2s, age:%d\n", boy->name, boy->age);
    }

    return ret;
}
*/

/*
-------OK-------
struct person
{
    int age;
    char name[20];
    struct list_head list;
};

int AX_SMAPLE_LIST_001(char **failReason)
{
    int ret=0;

    struct person *boy;
    struct person person_head;
    struct person *pperson;

    int i;
    // 初始化双链表的表头
    INIT_LIST_HEAD(&person_head.list);
    // 添加节点
    for (i=0; i<5; i++)
    {
        pperson = (struct person*)malloc(sizeof(struct person));
        pperson->age = (i+1)*10;
        sprintf(pperson->name, "%d", i+1);
        // 将节点链接到链表的末尾
        // 如果想把节点链接到链表的表头后面，则使用 list_add
        //list_add_tail(&(pperson->list), &(person_head.list));
        list_add(&(pperson->list), &(person_head.list));
    }

    // 遍历链表
    printf("==== 2st iterator d-link ====\n");
    list_for_each_entry(boy, &(person_head.list), list ){
        printf("------name:%-2s, age:%d\n", boy->name, boy->age);
    }

    return ret;
}
*/

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int age;
    char name[20];
    struct list_head list;
};

int AX_SMAPLE_LIST_001(char **failReason)
{
    int ret = 0;

    struct person *pperson;
    struct person *boy;
    struct person person_head;
    struct list_head *pos, *next;
    int i;
    // 初始化双链表的表头
    INIT_LIST_HEAD(&person_head.list);
    // 添加节点
    for (i = 0; i < 5; i++) {
        pperson = (struct person *)malloc(sizeof(struct person));
        pperson->age = (i + 1) * 10;
        sprintf(pperson->name, "%d", i + 1);
        // 将节点链接到链表的末尾
        // 如果想把节点链接到链表的表头后面，则使用 list_add
        //list_add_tail(&(pperson->list), &(person_head.list));
        list_add(&(pperson->list), &(person_head.list));
    }

    // 遍历链表
    printf("==== 1st iterator d-link ====\n");
    list_for_each(pos, &person_head.list) {
        pperson = list_entry(pos, struct person, list);
        printf("name:%-2s, age:%d\n", pperson->name, pperson->age);
    }

    // 遍历链表
    printf("==== 2st iterator d-link ====\n");
    list_for_each_entry(boy, &(person_head.list), list) {
        printf("------name:%-2s, age:%d\n", boy->name, boy->age);
    }

#if 0
    // 删除节点age为20的节点
    printf("==== delete node(age:20) ====\n");
    list_for_each_safe(pos, next, &person_head.list) {
        pperson = list_entry(pos, struct person, list);
        if (pperson->age == 20) {
            list_del_init(pos);
            free(pperson);
        }
    }

    // 再次遍历链表
    printf("==== 2nd iterator d-link ====\n");
    list_for_each(pos, &person_head.list) {
        pperson = list_entry(pos, struct person, list);
        printf("name:%-2s, age:%d\n", pperson->name, pperson->age);
    }

    // 释放资源
    list_for_each_safe(pos, next, &person_head.list) {
        pperson = list_entry(pos, struct person, list);
        list_del_init(pos);
        free(pperson);
    }

#endif
    return ret;
}

#endif

