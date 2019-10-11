#include <iostream>
using namespace std;

typedef int BSTData;
typedef struct _bTreeNode {
    BSTData data;
    struct _bTreeNode * left;
    struct _bTreeNode * right;
} BTreeNode;

BTreeNode * MakeBTreeNode(void) {
    BTreeNode * nd = new BTreeNode;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}

BSTData GetData(BTreeNode * bt) {
    return bt->data;
}

void SetData(BTreeNode * bt, BSTData data) {
    bt->data = data;
}

BTreeNode * GetLeftSubTree(BTreeNode * bt) {
    return bt->left;
}

BTreeNode * GetRightSubTree(BTreeNode * bt) {
    return bt->right;
}

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub) {
    if(main->left != NULL) delete(main->left);
    main->left = sub;
}

void MakeRightSubTree(BTreeNode * main, BTreeNode * sub) {
    if(main->right != NULL) delete(main->right);
    main->right = sub;
}

BTreeNode * RemoveLeftSubTree(BTreeNode * bt) {
    BTreeNode * delNode = NULL;
    if(bt != NULL) {
        delNode = bt->left;
        bt->left = NULL;
    }
    return delNode;
}

BTreeNode * RemoveRigthSubTree(BTreeNode * bt) {
    BTreeNode * delNode = NULL;
    if(bt != NULL) {
        delNode = bt->right;
        bt->right = NULL;
    }
    return delNode;
}

void ChangeLeftSubTree(BTreeNode * main, BTreeNode * sub) { main->left = sub; }
void ChangeRightSubTree(BTreeNode * main, BTreeNode * sub) { main->right = sub; }

BTreeNode * RotateLL(BTreeNode * bst) {
    BTreeNode * pNode;
    BTreeNode * cNode;
    
    pNode = bst;
    cNode = GetLeftSubTree(pNode);
    
    ChangeLeftSubTree(pNode, GetRightSubTree(cNode));
    ChangeRightSubTree(cNode, pNode);
    return cNode;
}

BTreeNode * RotateRR(BTreeNode * bst) {
    BTreeNode * pNode;
    BTreeNode * cNode;
    
    pNode = bst;
    cNode = GetRightSubTree(pNode);
    
    ChangeRightSubTree(pNode, GetLeftSubTree(cNode));
    ChangeLeftSubTree(cNode, pNode);
    return cNode;
}

BTreeNode * RotateRL(BTreeNode * bst) {
    BTreeNode * pNode;
    BTreeNode * cNode;
    
    pNode = bst;
    cNode = GetRightSubTree(pNode);
    
    ChangeRightSubTree(pNode, RotateLL(cNode));
    return RotateRR(pNode);
}

BTreeNode * RotateLR(BTreeNode * bst) {
    BTreeNode * pNode;
    BTreeNode * cNode;
    
    pNode = bst;
    cNode = GetLeftSubTree(pNode);
    
    ChangeLeftSubTree(pNode, RotateRR(cNode));
    return RotateLL(pNode);
}

int GetHeight(BTreeNode * bst) {
    int leftH;
    int rightH;
    
    if(bst == NULL) return 0;
    
    leftH = GetHeight(GetLeftSubTree(bst));
    rightH = GetHeight(GetRightSubTree(bst));
    
    if(leftH > rightH) return leftH + 1;
    else return rightH + 1;
}

int GetHeightDiff(BTreeNode * bst) {
    int lsh;
    int rsh;
    
    if(bst == NULL) return 0;
    
    lsh = GetHeight(GetLeftSubTree(bst));
    rsh = GetHeight(GetRightSubTree(bst));
    
    return lsh - rsh;
}

BTreeNode * Rebalance(BTreeNode ** pRoot) {
    
    int hDiff = GetHeightDiff(*pRoot);
    
    if(hDiff > 1) {
        if(GetHeightDiff(GetLeftSubTree(*pRoot)) > 0)
            *pRoot = RotateLL(*pRoot);
        else
            *pRoot = RotateLR(*pRoot);
    }
    
    if(hDiff < -1) {
        if(GetHeightDiff(GetRightSubTree(*pRoot)) < 0)
            *pRoot = RotateRR(*pRoot);
        else
            *pRoot = RotateRL(*pRoot);
    }
    return *pRoot;
}

void BSTMakeAndInit(BTreeNode ** pRoot) {
    *pRoot = NULL;
}

void BSTInsert(BTreeNode ** pRoot, BSTData data) {
    
    BTreeNode * pNode = NULL;
    BTreeNode * cNode = *pRoot;
    BTreeNode * nNode = NULL;
    
    while(cNode != NULL) {
        if(data == GetData(cNode))
            return;
        
        pNode = cNode;
        
        if(GetData(cNode) > data)
            cNode = GetLeftSubTree(cNode);
        else
            cNode = GetRightSubTree(cNode);
    }
    
    nNode = MakeBTreeNode();
    SetData(nNode, data);
    
    if(pNode != NULL) {
        if(data < GetData(pNode))
            MakeLeftSubTree(pNode, nNode);
        else
            MakeRightSubTree(pNode, nNode);
    }
    else {
        *pRoot = nNode;
    }
    
    *pRoot = Rebalance(pRoot);
}

BTreeNode * BSTSearch(BTreeNode *bst, BSTData target) {
    BTreeNode * cNode = bst;
    BSTData cd;
    
    while(cNode != NULL) {
        cd = GetData(cNode);
        
        if(target == cd)
            return cNode;
        else if(target < cd) cNode = GetLeftSubTree(cNode);
        else cNode = GetRightSubTree(cNode);
    }
    
    return NULL;
}

BTreeNode * BSTRemove(BTreeNode ** pRoot, BSTData target) {
    
    BTreeNode * pVRoot = MakeBTreeNode();
    
    BTreeNode * pNode = pVRoot;
    BTreeNode * cNode = *pRoot;
    BTreeNode * dNode;
    
    ChangeRightSubTree(pVRoot, *pRoot);
    
    // 삭제 대상을 저장할 노드 탐색
    while(cNode != NULL && GetData(cNode) != target) {
        pNode = cNode;
        if(target < GetData(cNode))
            cNode = GetLeftSubTree(cNode);
        else
            cNode = GetRightSubTree(cNode);
    }
    
    if(cNode == NULL)
        return NULL;
    
    // 삭제할 노드
    dNode = cNode;
    
    // 첫 번째 경우: 삭제할 노드가 단말 노드인 경우
    if(GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL) {
        if(GetLeftSubTree(pNode) == dNode)
            RemoveLeftSubTree(pNode);
        else
            RemoveRigthSubTree(pNode);
    }
    
    // 두 번째 경우: 하나의 자식 노드를 갖는 경우
    else if(GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL) {
        BTreeNode * dcNode;
        
        if(GetLeftSubTree(dNode) != NULL)
            dcNode = GetLeftSubTree(dNode);
        else
            dcNode = GetRightSubTree(dNode);
        
        if(GetLeftSubTree(pNode) == dNode)
            ChangeLeftSubTree(pNode, dcNode);
        else
            ChangeRightSubTree(pNode, dcNode);
    }
    
    // 세 번째 경우: 두 개의 자식 노드를 모두 갖는 경우
    else {
        
        BTreeNode * mNode = GetRightSubTree(dNode);
        BTreeNode * mpNode = dNode;
        int delData;
        
        // 삭제할 노드를 대체할 노드를 찾는다.
        while(GetLeftSubTree(mNode) != NULL) {
            mpNode = mNode;
            mNode = GetLeftSubTree(mNode);
        }
        
        // 대체할 노드에 저장된 값을 삭제할 노드에 대입한다.
        delData = GetData(dNode);
        SetData(dNode, GetData(mNode));
        
        if(GetLeftSubTree(mpNode) == mNode)
            ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
        else
            ChangeRightSubTree(mpNode, GetRightSubTree(mNode));
        
        dNode = mNode;
        SetData(dNode, delData);
    }
    
    if(GetRightSubTree(pVRoot) != *pRoot)
        *pRoot = GetRightSubTree(pVRoot);
    
    delete pVRoot;
    *pRoot = Rebalance(pRoot);
    return dNode;
}

typedef void VisitFuncPtr(BSTData data);

void InorderTraverse(BTreeNode * bt, VisitFuncPtr action)
{
    if(bt == NULL)
        return;

    InorderTraverse(bt->left, action);
    action(bt->data);
    InorderTraverse(bt->right, action);
}

void ShowIntData(int data) { cout << data << ' '; }
void BSTShowAll(BTreeNode * bst) { InorderTraverse(bst, ShowIntData);}



int main(void) {
    
    BTreeNode * avlRoot;
    BTreeNode * clNode;
    BTreeNode * crNode;
    BSTMakeAndInit(&avlRoot);
    
    BSTInsert(&avlRoot, 5);
    BSTInsert(&avlRoot, 2);
    BSTInsert(&avlRoot, 3);
    /*
    BSTInsert(&avlRoot, 4);
    BSTInsert(&avlRoot, 5);
    BSTInsert(&avlRoot, 6);
    BSTInsert(&avlRoot, 7);
    BSTInsert(&avlRoot, 8);
    BSTInsert(&avlRoot, 9);
    */
    
    cout << "루트 노드: " << GetData(avlRoot) << '\n';
    clNode = GetLeftSubTree(avlRoot);
    crNode = GetRightSubTree(avlRoot);
    cout << "왼쪽: " << GetData(clNode) << ", 오른쪽: " << GetData(crNode) << "\n";
    
    /*
    BSTShowAll(bstRoot); cout << '\n';
    sNode = BSTRemove(&bstRoot, 3);
    delete sNode;
    
    BSTShowAll(bstRoot); cout << '\n';
    sNode = BSTRemove(&bstRoot, 8);
    delete sNode;
    
    BSTShowAll(bstRoot); cout << '\n';
    sNode = BSTRemove(&bstRoot, 1);
    delete sNode;
    
    BSTShowAll(bstRoot); cout << '\n';
    sNode = BSTRemove(&bstRoot, 6);
    delete sNode;
    
    BSTShowAll(bstRoot); cout << '\n';
    */
    return 0;
}
