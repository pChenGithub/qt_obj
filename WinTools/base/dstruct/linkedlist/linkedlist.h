#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <pthread.h>
#define LKLIST_ERR_CHECKPARAM   1   // 参数错误
#define LKLIST_ERR_CALLOCFAIL   2   // 执行calloc失败
#define LKLIST_ERR_INIT_MUTEXLOCK   3   // 初始化锁失败
#define LKLIST_ERR_LOCK   4   // 加锁锁失败

typedef struct _node{
    struct _node* pre;
    struct _node* next;
} LINK_NODE;

typedef struct {
    LINK_NODE node;
    int nodecount;      // 链表节点数量,不包括head
    pthread_mutex_t lock_linked;
} LINK_HEAD;

// 静态申请一个链表头
#define INIT_LINKEDLIST(head) \
    LINK_HEAD head = { \
        {&head, &head}, \
        0, \
    } \

// 创建一个链表头
int init_linkedlist(LINK_HEAD** head);
// 释放链表头
int free_linkedlist(LINK_HEAD* head);
// 插入一项
// index表示在哪个地方插入,
// index=0表示在head后面插入,1表示在第一个node后插入,-1表示在倒数第一个node插入
int insert_lknode(LINK_HEAD* head, LINK_NODE* node, int index);
// 前插/后插
int insert_head(LINK_HEAD* head, LINK_NODE* node);
int insert_tail(LINK_HEAD* head, LINK_NODE* node);
// 删除一项
// 1表示在第一个node,-1表示倒数第一个node
int remove_lknode(LINK_HEAD* head, int index, LINK_NODE** node);
// 遍历
typedef int (*hand_node)(LINK_NODE* node);
int foreach_lklist(LINK_HEAD* head, hand_node hand);
// head:链表头指针,node:节点指针
#define FOREACH_LKLIST(head, _mnode) \
    for (_mnode=head->node.next;_mnode!=(&head->node);_mnode=_mnode->next)
// 结构体操作
// 计算域在结构体中的地址偏移
#define OFFSETOF(type, member) ((size_t)&((type*)0)->member)
// 根据node地址获取结构体地址
// ptr:node指针,type:实体结构体类型,member:node在结构体的域名称
#define CONTAINER_OF(ptr, type, member) \
({ \
    (type*)((char*)ptr-OFFSETOF(type, member)); \
})
// 清空链表
int clear_lklist(LINK_HEAD* head, hand_node hand);
#define CLEAR_LKLIST(head, type, member) ({ \
    LINK_NODE* _mnode = NULL; \
    for (_mnode=(head)->node.next;_mnode!=(&((head)->node));) { \
        type* _mdata = CONTAINER_OF(_mnode, type, member); \
        _mnode = _mnode->next; \
        free(_mdata); \
    } \
    (head)->nodecount = 0; \
    (head)->node.pre = (LINK_NODE*)head; \
    (head)->node.next = (LINK_NODE*)head; \
    })

#ifdef __cplusplus
}
#endif
#endif

