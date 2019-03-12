#ifndef NULL
#define NULL 0
#endif

const int MAX_FIELD_SIZE = 19;
const int MAX_RECORD_SIZE = 50000;
const int MAX_ALLOCATOR_SIZE = MAX_RECORD_SIZE * 1.5;
const int MAX_HASH_TABLE_SIZE = 10007;

typedef enum {
	START,
	NAME = START,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO,
	MAX
} FIELD;

typedef struct {
	int count;
	char str[20];
} RESULT;

namespace str {
	void copy(char *dest, const char *src) {
		while (*src) {
			*dest = *src;
			src++; dest++;
		}
		*dest = 0;
	}
	bool is_same(const char *str1, const char *str2) {
		while (*str1 && *str2 && *str1 == *str2) {
			str1++; str2++;
		}
		return (*str1 == 0 && *str2 == 0);
	}
}

template <typename T>
struct Allocator {
	T mempool_[MAX_ALLOCATOR_SIZE];
	int index_;

	void init() {
		index_ = 0;
	}
	T* alloc() {
		T* ret = &mempool_[index_++];
		ret->init();
		return ret;
	}
};

template <typename T>
struct Node {
	T *data_;
	Node<T> *next_, *prev_;

	void init() {
		data_ = NULL;
		next_ = prev_ = NULL;
	}
};

template <typename T>
struct List {
	Node<T> *head_;

	void init() {
		head_ = NULL;
	}
	void push(Node<T> *node) {
		if (head_) head_->prev_ = node;
		node->prev_ = NULL;
		node->next_ = head_;
		head_ = node;
	}
	void remove(Node<T> *node) {
		if (node == head_) head_ = node->next_;
		if (node->prev_) node->prev_->next_ = node->next_;
		if (node->next_) node->next_->prev_ = node->prev_;
	}
};

template <typename T>
struct Hash {
	typedef unsigned long key_t;
	typedef List<T> HashList;

	Allocator< Node<T> > nodeAllocator_;
	HashList chain_[MAX_HASH_TABLE_SIZE];

	static key_t hash(const char *str) {
		unsigned long hash = 5381;
		int c;
		while (c = *str++) {
			hash = (((hash << 5) + hash) + c) % MAX_HASH_TABLE_SIZE;
		}
		return hash % MAX_HASH_TABLE_SIZE;
	}
	void init() {
		nodeAllocator_.init();
		for (register int i = 0; i < MAX_HASH_TABLE_SIZE; i++) {
			chain_[i].init();
		}
	}
	Node<T>* insert(key_t key, T *data) {
		Node<T>* node = nodeAllocator_.alloc();
		node->data_ = data;
		chain_[key].push(node);
		return node;
	}
	void insert(key_t key, Node<T> *node) {
		chain_[key].push(node);
	}
	void remove(key_t key, Node<T> *node) {
		chain_[key].remove(node);
	}
};

struct Record {
	char field_[FIELD::MAX][MAX_FIELD_SIZE + 1];
	Hash<Record>::key_t keys_[FIELD::MAX];
	Node<Record> *link_[FIELD::MAX];

	bool is_same(FIELD field, const char *val) {
		return str::is_same(field_[field], val);
	}
	void set(const char* name, const char* number, const char* birthday, const char* email, const char* memo) {
		str::copy(field_[FIELD::NAME], name);
		str::copy(field_[FIELD::NUMBER], number);
		str::copy(field_[FIELD::BIRTHDAY], birthday);
		str::copy(field_[FIELD::EMAIL], email);
		str::copy(field_[FIELD::MEMO], memo);
	}
};

struct DB {
	typedef void(*op)(DB* table, Record* record, void *userdata);

	struct ChangeContext {
		ChangeContext(FIELD field, char *changestr) : changedCount(0), changeField(field), changeStr(changestr) {}
		int changedCount;
		FIELD changeField;
		char *changeStr;
	};
	struct SearchContext {
		SearchContext(RESULT* result, FIELD field) : result(result), retField(field) { result->count = 0; }
		RESULT* result;
		FIELD retField;
	};

	Record table_[MAX_RECORD_SIZE];
	Hash<Record> hashes_[FIELD::MAX];
	int index_;

	static void removeOp(DB* table, Record* record, void *userdata) {
		(*(int*)userdata)++;
		for (register int field = FIELD::START; field < FIELD::MAX; field++) {
			Hash<Record>::key_t key = record->keys_[field];
			Node<Record>* cur = record->link_[field];
			table->hashes_[field].remove(key, cur);
		}
	}
	static void changeOp(DB* table, Record* record, void *userdata) {
		ChangeContext *ctx = (ChangeContext*)userdata;

		ctx->changedCount++;

		Hash<Record>::key_t oldKey = record->keys_[ctx->changeField];
		Hash<Record>::key_t changeKey = Hash<Record>::hash(ctx->changeStr);
		record->keys_[ctx->changeField] = changeKey;
		str::copy(record->field_[ctx->changeField], ctx->changeStr);

		Node<Record>* cur = record->link_[ctx->changeField];
		table->hashes_[ctx->changeField].remove(oldKey, cur);
		table->hashes_[ctx->changeField].insert(changeKey, cur);
	}
	static void searchOp(DB* table, Record* record, void *userdata) {
		SearchContext* ctx = (SearchContext*)userdata;
		ctx->result->count++;
		if (ctx->result->count == 1) // if count is over 1 then don't copy string
			str::copy(ctx->result->str, record->field_[ctx->retField]);
	}

	void init() {
		index_ = 0;
		for (register int field = 0; field < FIELD::MAX; field++) {
			hashes_[field].init();
		}
	}
	void retrieve(FIELD field, const char* str, op iter, void *userdata) {
		Hash<Record>::key_t key = Hash<Record>::hash(str);
		Node<Record>* node = hashes_[field].chain_[key].head_;
		while (node) {
			Record *record = node->data_;
			node = node->next_;
			if (record->is_same(field, str) == false) continue;
			iter(this, record, userdata);
		}
	}
	void add(const char* name, const char* number, const char* birthday, const char* email, const char* memo) {
		Record* record = &table_[index_++];
		record->set(name, number, birthday, email, memo);

		for (register int field = 0; field < FIELD::MAX; field++) {
			Hash<Record>::key_t key = Hash<Record>::hash(record->field_[field]);
			record->keys_[field] = key;
			record->link_[field] = hashes_[field].insert(key, record);
		}
	}
	int remove(FIELD field, const char* str) {
		int deletedCount = 0;
		retrieve(field, str, removeOp, &deletedCount);
		return deletedCount;
	}
	int change(FIELD field, char* str, FIELD changefield, char* changestr) {
		ChangeContext ctx(changefield, changestr);
		retrieve(field, str, changeOp, &ctx);
		return ctx.changedCount;
	}
	void search(FIELD field, char* str, FIELD ret_field, RESULT *result) {
		SearchContext ctx(result, ret_field);
		retrieve(field, str, searchOp, &ctx);
	}
} TABLE;

void InitDB() {
	TABLE.init();
}
void Add(char* name, char* number, char* birthday, char* email, char* memo) {
	TABLE.add(name, number, birthday, email, memo);
}
int Delete(FIELD field, char* str) {
	return TABLE.remove(field, str);
}
int Change(FIELD field, char* str, FIELD changefield, char* changestr) {
	return TABLE.change(field, str, changefield, changestr);
}
RESULT Search(FIELD field, char* str, FIELD ret_field) {
	RESULT result;
	TABLE.search(field, str, ret_field, &result);
	return result;
}