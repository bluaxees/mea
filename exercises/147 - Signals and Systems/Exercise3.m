%Exercise 3

%Initialize 3x3 black and white tiles
B = repmat(1,[3,3]);
W = repmat(75,[3,3]);

%Create mini chessboard
M = [B W; W B];

%Create whole chessboard
C = repmat(M,[4,4]);
imshow(C,[]);