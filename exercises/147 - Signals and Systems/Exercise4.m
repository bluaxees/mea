%Exercise 4

%Create a lower triangular white tile
W = tril(repmat(75,[1024,1024]));

%Rotate tile three times
R0 = W; 
R90 = rot90(R0);
R180 = rot90(R90);
R270 = rot90(R180);

%Combine the rotated tiles 
Diamond = [R90 R0;R180 R270];
imshow(Diamond,[]);