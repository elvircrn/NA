// Predavanje 3; Stranica 11

function [X] = lijevo(A, B)
    [n, ac] = size(A);
    [ac, m] = size(B);
    for k = 1:n
        for i = (k + 1):n
            mi = A(i, k) / A(k, k);
            for j = (k + 1):n
                A(i, j) = A(i, j) - mi * A(k, j);
            end
            for j = 1:m
                B(i, j) = B(i, j) - mi * B(k, j);
            end
        end
    end
    
    for k = 1:m
        for i = n:-1:1
            s = B(i, k)
            for j = (i + 1):n
                s = s - A(i, j) * X(j, k);
            end
            X(i, k) = s / A(i, i);
        end
    end
endfunction

AA = [2, 1, 3; 2, 6, 8; 6, 8, 18];
BB = [1; 3; 5];

AA = [2, 1, 3; 2, 6, 8; 6, 8, 18];
BB = [1; 3; 5];

[res] = lijevo(AA, BB);
disp(res);
disp(AA \ BB);
