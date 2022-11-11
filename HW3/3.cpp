#include <iostream>
#include <vector>
#include <map>
#include<math.h>
#include<algorithm>
#include<queue>

using namespace std;
struct Point {
    int x;
    int y;
};

Point getTargetPoint(Point sourcePoint, int shift, int direction) {
    int endPosX = sourcePoint.x;
    int endPosY = sourcePoint.y;
    if(direction == 1) endPosX -= shift;
    if(direction == 2) endPosY -= shift;
    if(direction == 3) endPosX += shift;
    if(direction == 4) endPosY += shift;
    
    Point targetPoint = {endPosX, endPosY};
    return targetPoint;
}

bool solve(vector< vector<int> > &minMoves, int rowpos,int colpos, int rows, int columns,int shift,int direction) {
    /*
        direction:
            1 - left
            2 - top
            3 - right
            4 - bottom
    */
   Point sourcePoint = {rowpos,colpos};
   Point targetPoint = getTargetPoint(sourcePoint,shift,direction);
   int endPosX = targetPoint.x;
   int endPosY = targetPoint.y;


    if((endPosX >= 0 && endPosX < rows) && (endPosY >= 0 && endPosY < columns)) {
        if((minMoves[rowpos][colpos]+1) < minMoves[endPosX][endPosY]) {
            minMoves[endPosX][endPosY] = minMoves[rowpos][colpos] + 1;
            return true;
        }
    }
    return false;
}
int main() {
    int n,m;
    cin>>n>>m;

    vector< vector<int> > grid(n, vector<int>(m,0));
    vector< vector<int> > minMoves(n, vector<int>(m,1e9));
    queue<Point> coordinates;

    for(int i=0;i<n;i++) {
        for(int j = 0; j < m ; j++) {
            char cellValue;
            cin>>cellValue;
            grid[i][j] = (cellValue - '0');
        }
    }

    // initialisation
    minMoves[0][0] = 0;
    Point startPoint = {0,0};
    coordinates.push(startPoint);

    while(!coordinates.empty()) {
        Point currentCoord = coordinates.front();
        coordinates.pop();
        int coordX = currentCoord.x;
        int coordY = currentCoord.y;
        int shift = grid[coordX][coordY];
        for(int direction = 1; shift!=0 && (direction <= 4); direction++) {
            if(solve(minMoves,coordX,coordY,n,m,shift,direction)) {
                Point sourcePoint = {coordX,coordY};
                Point targetPoint = getTargetPoint(sourcePoint,shift,direction);
                coordinates.push(targetPoint);
            }
        }
    }
    int res = ((minMoves[n-1][m-1] == 1e9) ? -1 : minMoves[n-1][m-1]);
    cout<<res<<endl;
    
    return 0;
}