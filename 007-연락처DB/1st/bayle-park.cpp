typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO,
	MAX
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;

#ifndef NULL
#define NULL 0
#endif

const int MAX_FIELD_SIZE = 19;
const int MAX_RECORD_SIZE = 50000;
const int MAX_ALLOCATOR_RECORD_SIZE = MAX_RECORD_SIZE * 1.5;
const int MAX_HASH_TABLE_SIZE = 100007;

namespace str {
	void copy(char *dest, const char *src) {
		while (*src) {
			*dest = *src;
			src++;
			dest++;
		}
		*dest = 0;
	}
	bool is_same(const char *str1, const char *str2) {
		while (*str1 && *str2 && *str1 == *str2) {
			str1++;
			str2++;
		}
		if (*str1 == 0 && *str2 == 0) return true;
		else return false;
	}
	int len(const char *str) {
		int len = 0;
		while (*(str++)) {
			len++;
		}
		return len;
	}
}

template <typename T>
struct Allocator {
	T* mempool_;
	int index_;
	void init() {
		index_ = 0;
	}
	T* alloc() {
		T* ret = &mempool_[index_++];
		ret->init();
		return ret;
	}
	Allocator(int maxsize) {
		mempool_ = new T[maxsize];
	}
	~Allocator() {
		delete[] mempool_;
	}
};

template <typename T>
struct Hash {
	struct Node {
		T *data_;
		Node *next_, *prev_;
		void init() {
			data_ = NULL;
			next_ = prev_ = NULL;
		}
	};

	Allocator<Node> allocator_;
	Node* tables_[MAX_HASH_TABLE_SIZE];

	typedef unsigned long key_t;

	Hash() : allocator_(MAX_ALLOCATOR_RECORD_SIZE) { }

	static key_t hash(const char *str) {
		unsigned long hash = 5381;
		int c;
		while (c = *str++) {
			hash = (((hash << 5) + hash) + c) % MAX_HASH_TABLE_SIZE;
		}
		return hash % MAX_HASH_TABLE_SIZE;
	}

	void init() {
		allocator_.init();
		for (register int i = 0; i < MAX_HASH_TABLE_SIZE; i++) tables_[i] = NULL;
	}

	Node* insert(const char *keyval, T *data) {
		Node* node = allocator_.alloc();
		node->data_ = data;
		key_t key = hash(keyval);
		if (tables_[key]) tables_[key]->prev_ = node;
		node->prev_ = NULL;
		node->next_ = tables_[key];
		tables_[key] = node;
		return node;
	}
};

struct Record {
	char field_[FIELD::MAX][MAX_FIELD_SIZE + 1];
	Hash<Record>::Node *link_[FIELD::MAX];
	bool removed_;

	bool is_same(FIELD field, char *val) {
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
	Record table_[MAX_RECORD_SIZE];
	int index_;
	void init() {
		index_ = 0;
	}
	Record* add(const char* name, const char* number, const char* birthday, const char* email, const char* memo) {
		Record* target = &table_[index_++];
		target->removed_ = false;
		target->set(name, number, birthday, email, memo);
		return target;
	}
};

DB table;
Hash<Record> hashes[FIELD::MAX];

void InitDB()
{
	table.init();
	for (register int field = 0; field < FIELD::MAX; field++) hashes[field].init();
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	Record *record = table.add(name, number, birthday, email, memo);
	for (register int field = 0; field < FIELD::MAX; field++) {
		Hash<Record>::Node *node = hashes[field].insert(record->field_[field], record);
		record->link_[field] = node;
	}
}

int Delete(FIELD field, char* str)
{
	int deletedCount = 0;
	Hash<Record>::key_t key = Hash<Record>::hash(str);
	Hash<Record>::Node* node = hashes[field].tables_[key];
	while (node) {
		Record *record = node->data_;
		node = node->next_;
		if (record->removed_) continue;
		if (record->is_same(field, str) == false) continue;
		record->removed_ = true;
		deletedCount++;
	}
	return deletedCount;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int changedCount = 0;
	Hash<Record>::key_t key = Hash<Record>::hash(str);
	Hash<Record>::Node* node = hashes[field].tables_[key];
	while (node) {
		Record *record = node->data_;
		node = node->next_;
		if (record->removed_) continue;
		if (record->is_same(field, str) == false) continue;
		str::copy(record->field_[changefield], changestr);
		if (record->link_[changefield]->prev_) {
			record->link_[changefield]->prev_->next_ = record->link_[changefield]->next_;
		}
		if (record->link_[changefield]->next_) {
			record->link_[changefield]->next_->prev_ = record->link_[changefield]->prev_;
		}
		hashes[changefield].insert(changestr, record);
		changedCount++;
	}
	return changedCount;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	result.count = 0;

	Hash<Record>::key_t key = Hash<Record>::hash(str);
	Hash<Record>::Node* node = hashes[field].tables_[key];
	while (node) {
		Record *record = node->data_;
		node = node->next_;
		if (record->removed_) continue;
		if (record->is_same(field, str) == false) continue;
		result.count++;
		if (result.count == 1)
			str::copy(result.str, record->field_[ret_field]);
	}

	return result;
}