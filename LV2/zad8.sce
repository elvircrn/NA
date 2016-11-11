M = [1, 0, 1; -1, -2, 0; 0, 1, -1];
disp(spec(M));

MM = M;

for i = 1:1000
    [Q, R] = qr(MM);
    MM = R * Q;
end


disp(MM);
