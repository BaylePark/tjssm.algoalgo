#define MAX_TABLE 204833       
#define MAX_DB 50000

typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;

struct DB {
	char name[20];
	char number[20];
	char birth[20];
	char email[20];
	char memo[20];
	bool isDeleted;
};

DB myDB[MAX_DB];
int dbIdx;

struct hashNode {
	char key[20];
	hashNode* next;
	hashNode* prev;
	DB* db;
	bool isDeleted;
	bool isChanged;
};

hashNode extraNode[MAX_TABLE];
int hashIdx;
hashNode myHash[MAX_TABLE];

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool myCompare(char* str, char* str2) {
	//return strcmp(str,str2) == 0;
	int idx = 0;
	while (str[idx]) {
		if (str2[idx] != str[idx]) {
			return false;
		}
		idx++;
	}
	if (str2[idx] != '\0') return false;
	return true;
}

void myCopy(char* str, char* str2) {
	//strcpy(str2, str);
	//return;
	int idx = 0;
	while (str[idx]) {
		str2[idx] = str[idx];
		idx++;
	}
	str2[idx] = '\0';
}
unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

void InitDB()
{	
	for (int i = 0; i < MAX_TABLE; i++) {
		myHash[i].db = 0;
		myHash[i].next = 0;
		myHash[i].prev = 0;
		myHash[i].isDeleted = false;
		myHash[i].isChanged = false;
	}
	dbIdx = 0;
	hashIdx = 0;
}

void insertHash(char* key, DB* cur);
void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	DB* cur = &myDB[dbIdx++];
	cur->isDeleted = false;
	myCopy(name, cur->name);
	myCopy(number, cur->number);
	myCopy(birthday, cur->birth);
	myCopy(email, cur->email);
	myCopy(memo, cur->memo);

	insertHash(name, cur);
	insertHash(number, cur);
	insertHash(birthday, cur);
	insertHash(email, cur);
	insertHash(memo, cur);
}

void insertHash(char* key, DB* cur) {
	unsigned long val = hash(key);
	if (!myHash[val].db) {
		myHash[val].db = cur;
		myCopy(key, myHash[val].key);
		myHash[val].next = 0;
	}
	else {
		hashNode** tmp = &myHash[val].next;
		while (*tmp) {
			tmp = &((*tmp)->next);
		}
		*tmp = &extraNode[hashIdx++];
		(*tmp)->db = cur;
		myCopy(key, (*tmp)->key);
		(*tmp)->next = 0;
	}

}

int Delete(FIELD field, char* str)
{
	int deleted = 0;
	unsigned long val = hash(str);
	hashNode* tmp = &myHash[val];
	while (tmp && tmp->db) {
		char* tmpStr1 = str;
		if (field == NAME) tmpStr1 = tmp->db->name;
		else if (field == NUMBER) tmpStr1 = tmp->db->number;
		else if (field == BIRTHDAY) tmpStr1 = tmp->db->birth;
		else if (field == EMAIL) tmpStr1 = tmp->db->email;
		else if (field == MEMO) tmpStr1 = tmp->db->memo;
		if (myCompare(str, tmp->key) && myCompare(str, tmpStr1)) {
			if (!tmp->db->isDeleted) {
				tmp->db->isDeleted = true;
				deleted++;
			}
		}
		tmp = tmp->next;
	}
	return deleted;
}

void changedHash(char* str) {
	unsigned long val = hash(str);
	hashNode* tmp = &myHash[val];
	while (tmp && tmp->db) {
		if (myCompare(str, tmp->key) && !tmp->isChanged) {
			tmp->isChanged = true;
		}
		tmp = tmp->next;
	}
}
int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int changed = 0;
	unsigned long val = hash(str);
	hashNode* tmp = &myHash[val];
	while (tmp && tmp->db) {
		char* tmpStr1 = str;
		if (field == NAME) tmpStr1 = tmp->db->name;
		else if (field == NUMBER) tmpStr1 = tmp->db->number;
		else if (field == BIRTHDAY) tmpStr1 = tmp->db->birth;
		else if (field == EMAIL) tmpStr1 = tmp->db->email;
		else if (field == MEMO) tmpStr1 = tmp->db->memo;
		if (myCompare(str, tmp->key) && myCompare(str,tmpStr1)) {
			if (!tmp->db->isDeleted) {
				changed++;
				char* tmpStr = str;
				if (changefield == NAME) {
					myCopy(changestr, tmp->db->name);
					tmpStr = tmp->db->name;
				}
				else if (changefield == NUMBER) {
					myCopy(changestr, tmp->db->number);
					tmpStr = tmp->db->number;
				}
				else if (changefield == BIRTHDAY) {
					myCopy(changestr, tmp->db->birth);
					tmpStr = tmp->db->birth;
				}
				else if (changefield == EMAIL) {
					myCopy(changestr, tmp->db->email);
					tmpStr = tmp->db->email;
				}
				else if (changefield == MEMO) {
					myCopy(changestr, tmp->db->memo);
					tmpStr = tmp->db->memo;
				}
				insertHash(changestr, tmp->db);
				changedHash(tmpStr);
			}
		}
		tmp = tmp->next;
	}
	return changed;
}


RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	result.count = 0;
	unsigned long val = hash(str);
	hashNode* tmp = &myHash[val];
	while (tmp && tmp->db) {
		char* tmpStr1 = str;
		if (field == NAME) tmpStr1 = tmp->db->name;
		else if (field == NUMBER) tmpStr1 = tmp->db->number;
		else if (field == BIRTHDAY) tmpStr1 = tmp->db->birth;
		else if (field == EMAIL) tmpStr1 = tmp->db->email;
		else if (field == MEMO) tmpStr1 = tmp->db->memo;
		if (myCompare(str, tmp->key) && myCompare(str, tmpStr1)) {
			if (!tmp->db->isDeleted ) {
				result.count++;
				if (ret_field == NAME) {
					myCopy(tmp->db->name, result.str);
				}
				else if (ret_field == NUMBER) {
					myCopy( tmp->db->number, result.str);
				}
				else if (ret_field == BIRTHDAY) {
					myCopy(tmp->db->birth, result.str);
				}
				else if (ret_field == EMAIL) {
					myCopy( tmp->db->email, result.str);
				}
				else if (ret_field == MEMO) {
					myCopy(tmp->db->memo, result.str);
				}
			}
		}
		tmp = tmp->next;
	}

	return result;
}