// flood fill counting + flood fill changing + 双指针更新棋盘状态

// 单独用一个 flood fill 来转 0 -- 又需要一个额外的 visited

// Ps: flood fill 不可以递归更新 -- 可能会漏掉一些分支
// k=5
//  4
// 444
// 4 4

#include<bits/stdc++.h>
using namespace std;

int N,K;
int disappear;
int board[100][10], visited[100][10], visitedZero[100][10];

void toZeros(int x, int y, int color){
    if(x<0 || x>=N || y<0 || y>=10 || board[x][y]!=color || visitedZero[x][y]) return;
    visitedZero[x][y] = 1;
    board[x][y] = 0;    // flood fill turn to zeros
    toZeros(x+1,y,color);
    toZeros(x-1,y,color);
    toZeros(x,y+1,color);
    toZeros(x,y-1,color);
}

int dfs(int x, int y, int color){
    if(x<0 || x>=N || y<0 || y>=10 || board[x][y]!=color || visited[x][y]) return 0;

    visited[x][y] = 1;
    int count1 = dfs(x+1,y,color);
    int count2 = dfs(x-1,y,color);
    int count3 = dfs(x,y+1,color);
    int count4 = dfs(x,y-1,color);
    
    return 1 + count1+count2+count3+count4;    // 加起来才是整块的count
}

void resetVisited(){
    for(int i=0; i<N; i++){
        for(int j=0; j<10; j++){    // for block counting
            visited[i][j] = 0;
        }
    }
    for(int i=0; i<N; i++){     // for changing to 0
        for(int j=0; j<10; j++){
            visitedZero[i][j] = 0;
        }
    }
}

void updateBoard(){
    for(int c=0; c<10; c++){    // 10列
        for(int i=N-1; i>0; i--){   // 每列当成列表处理，删除空位 -- 双指针
            if(board[i][c] == 0){
                for(int j=i-1; j>=0; j--){
                    if(board[j][c] != 0){
                        board[i][c] = board[j][c];
                        board[j][c] = 0;
                        break;
                    }
                }
            }
        }
    }
}

int main(){
    freopen("mooyomooyo.in", "r", stdin);
    freopen("mooyomooyo.out", "w", stdout);

    cin>>N>>K;
    for(int i=0; i<N; i++){
        string line;
        cin>>line;
        for(int j=0; j<10; j++){
            board[i][j] = line[j]-'0';   
        }
    }
    
    while(true){
        disappear = 0;  // 标志是否有消除
        for(int i=0; i<N; i++){
            for(int j=0; j<10; j++){
                if(board[i][j] != 0){
                    if(dfs(i, j, board[i][j]) >= K){    // block counting >= K
                        disappear = 1;
                        toZeros(i, j, board[i][j]);     // flood fill turn board[i][j] to zero
                    }
                }
            }
        }
        if(!disappear) break;
        resetVisited();
        updateBoard();
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<10; j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
}