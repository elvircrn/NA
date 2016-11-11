A = [1, -2, -2, -3; 3, -9, 0, -9; -1, 2, 4, 7; -3, -6, 26, 2];
B = [2, -1, 0; -1, 2, -1; 0, -1, 2];

// LU factorization
[L, U] = lu(A);

disp(L);
disp(U);

disp(L * U);

// nije pozitivno definitna!!!
// R = chol(A);
// disp (R);


R = chol(B);
disp(R);

disp (R * (R.'));


