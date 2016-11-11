C = testmatrix('magi', 3);
disp(C);
D = inv(testmatrix('hilb', 3));
disp(D);

disp(det(C));
disp(rank(C));
disp(cond(C));
disp(cond(D));
