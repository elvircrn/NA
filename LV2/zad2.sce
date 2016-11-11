A = [2, 1; -3, 1; -1, 1];
B = [-1; -2; 1];

X = A \ B;

disp(X);

err = abs (A * X - B);
disp (err);
