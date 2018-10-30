# Double Linked List 구현하기
## 기본내용
- 30분안에 해결하기
- 심화문제를 동시에 해결 할 수 있다면 가점

## 필수 구현 내용
- 2차원 좌표 (x, y)를 저장할 수 있는 Double Linked List 구현하기
- 아래 내용에 대한 API 제공하기
  - 검색(Find)
    - 좌표 x, y를 넣으면 해당 Node 반환
    - 반환된 Node는 Data 수정도 가능 (수정 시 실제 List상 Data도 변경 돼야함)
  - 제거(Remove)
    - 특정 좌표에 대한 Node 삭제 가능
  - 중간에 삽입(Insert)
    - 특정 좌표에 대한 Node 뒤에 삽입
  - 맨 뒤에 넣기(Push)
    - List의 맨 끝에 좌표 x, y 삽입
  - 처음부터 리스트 내용 출력하기(Print)
    - List의 맨 처음부터 맨 끝까지 출력하기
  - 마지막부터 리스트 내용 출력하기(ReversalPrint)
    - List의 맨 끝부터 맨 처음까지 출력하기

### Test Cases
```cpp
Node1 = Push(1, 1)
Print()                     => (1, 1)
ReversalPrint()             => (1, 1)
Node2 = Push(1, 2)
Print()                     => (1, 1), (1, 2)
ReversalPrint()             => (1, 2), (1, 1)
Node3 = Push(2, 2)
Print()                     => (1, 1), (1, 2), (2, 2)
ReversalPrint()             => (2, 2), (1, 2), (1, 1)
FoundNode2 = Find(1, 2)
PrintNode(FoundNode2)       => (1, 2)
FoundNode2->x = 9
FoundNode2->y = 9
FoundNode2 = Find(9, 9)
PrintNode(FoundNode2)       => (9, 9)
Print()                     => (1, 1), (9, 9), (2, 2)
ReversalPrint()             => (2, 2), (9, 9), (1, 1)
Node4 = Insert(Node2, 4, 1)
Print()                     => (1, 1), (9, 9), (4, 1), (2, 2)
ReversalPrint()             => (2, 2), (4, 1), (9, 9), (1, 1)
Remove(Node1)
Print()                     => (9, 9), (4, 1), (2, 2)
ReversalPrint()             => (2, 2), (4, 1), (9, 9)
Remove(Node3)
Print()                     => (9, 9), (4, 1)
ReversalPrint()             => (4, 1), (9, 9)
Remove(Node4)
Print()                     => (9, 9)
ReversalPrint()             => (9, 9)
Remove(FoundNode2)
Print()                     => 
ReversalPrint()             => 
```


## 심화 문제
- 중복된 좌표가 포함 될 수 있다.
- 위 내용을 응용하여 2차원 좌표와 3차원 좌표를 저장할 수 있는 Double Linked List 총 2개를 10분안에 구현할 필요가 있다.

### Test Cases