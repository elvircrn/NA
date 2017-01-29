// QR factorize
P = [1, 1, 1; 1, 2, 3; 1, 3, 6];

[Q, R] = qr (P);

disp(Q * R);
