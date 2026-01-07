/*
 * @lc app=leetcode id=146 lang=cpp
 *
 * [146] LRU Cache
 */

// @lc code=start
// @lc code=start
#include <unordered_map>

class LRUCache {
private:
    // 定义双向链表节点
    struct Node {
        int key, value;
        Node *prev, *next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    std::unordered_map<int, Node*> cache; // 哈希表：Key -> Node指针
    Node *head, *tail;                    // 伪头和伪尾节点

    // --- 内部辅助函数 (像操作显卡驱动里的 Page List 一样) ---

    // 1. 从链表中移除节点 (只是断开链接，不释放内存)
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 2. 将节点插入到头部 (表示最新使用)
    void addToHead(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    // 3. 移动节点到头部 (刷新热度)
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    // 4. 移除并返回尾部节点 (淘汰最久未用的)
    Node* removeTail() {
        Node* res = tail->prev;
        removeNode(res);
        return res;
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        // 初始化伪头和伪尾，构建空链表: head <-> tail
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1; // 没找到
        }
        // 找到了：先通过 Map 定位，然后把数据移到链表头（标记为最近使用）
        Node* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // 情况 1: Key 已存在 -> 更新 Value，刷新位置到头部
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            // 情况 2: Key 不存在 -> 创建新节点，放入 Map，插到头部
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToHead(newNode);

            // 检查是否超容 (Eviction)
            if (cache.size() > capacity) {
                Node* tailNode = removeTail(); // 淘汰链表尾部
                cache.erase(tailNode->key);    // 从 Map 中删除索引
                delete tailNode;               // 释放物理内存
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

