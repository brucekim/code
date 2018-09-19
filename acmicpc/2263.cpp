/*
link: https://www.acmicpc.net/problem/2263
inorder, postorder, preorder를 예제 하나 두고 비교해보았음
Postorder의 마지막부터 앞으로 노드를 순회하면서 어디에 들어가야 할지 따져봄
선택된 노드가 주임 노드이며, inorder 상에 index를 기준으로 왼쪽에 있는 노드들은 left subtree, 오른쪽에 있는 노드들은 right subtree이다.


                    1
            2           3
        4       5     6     7
    8                   9
Inorder     8   4   2   5   1   6   9   3   7
Postorder   8   4   5   2   9   6   7   3   1
Preorder    1   2   4   8   5   3   6   9   7
*/
