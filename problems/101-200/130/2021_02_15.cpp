/*
 * https://leetcode.com/problems/surrounded-regions/
 * time: O(nm), space: O(nm)
 * Runtime: 8 ms, faster than 99.40% of C++ online submissions
 * Memory Usage: 9.9 MB, less than 86.60% of C++ online submissions
*/

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int H = board.size();
        if (H == 0)
            return;
        int W = board[0].size();
        for (int h = 0; h < H; h ++) {
            this->bfsBoard(board, h, 0, H, W);
            this->bfsBoard(board, h, W - 1, H, W);
        }
        for (int w = 1; w < W - 1; w ++) {
            this->bfsBoard(board, 0, w, H, W);
            this->bfsBoard(board, H - 1, w, H, W);
        }
        for (int h = 0; h < H; h ++) {
            for (int w = 0; w < W; w ++) {
                if (board[h][w] == 'O')
                    board[h][w] = 'X';
                else if (board[h][w] == 'T')
                    board[h][w] = 'O';
            }
        }
    }
private:
    void bfsBoard(vector<vector<char>>& board, int h, int w, int H, int W) {
        if (h < 0 || h >= H || w < 0 || w >= W || board[h][w] != 'O')
            return;
        board[h][w] = 'T';
        this->bfsBoard(board, h - 1, w, H, W);
        this->bfsBoard(board, h, w - 1, H, W);
        this->bfsBoard(board, h + 1, w, H, W);
        this->bfsBoard(board, h, w + 1, H, W);
    }
};
